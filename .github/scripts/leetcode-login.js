"use strict";

const puppeteer = require("puppeteer");

const DEFAULT_LOGIN_URL = "https://leetcode.com/accounts/login/";

const USER_SELECTOR_CANDIDATES = [
  "#id_login",
  'input[name="login"]',
  'input[name="username"]',
  'input[type="email"]',
  'input[autocomplete="username"]',
];

const PASS_SELECTOR_CANDIDATES = [
  "#id_password",
  'input[name="password"]',
  'input[type="password"]',
];

/** Current LeetCode login CTA (see DOM: #signin_btn, data-cy="sign-in-btn"). */
const SIGN_IN_SELECTORS = ["#signin_btn", '[data-cy="sign-in-btn"]'];

function sleep(ms) {
  return new Promise((r) => setTimeout(r, ms));
}

async function waitForVisibleCredentialSelectors(page, timeoutMs) {
  await page.waitForFunction(
    (userSels, passSels) => {
      function pick(sels) {
        for (const sel of sels) {
          const el = document.querySelector(sel);
          if (!el) continue;
          const r = el.getBoundingClientRect();
          if (r.width > 0 && r.height > 0) return sel;
        }
        return null;
      }
      return !!(pick(userSels) && pick(passSels));
    },
    { timeout: timeoutMs },
    USER_SELECTOR_CANDIDATES,
    PASS_SELECTOR_CANDIDATES,
  );

  return page.evaluate(
    (userSels, passSels) => {
      function pick(sels) {
        for (const sel of sels) {
          const el = document.querySelector(sel);
          if (!el) continue;
          const r = el.getBoundingClientRect();
          if (r.width > 0 && r.height > 0) return sel;
        }
        return null;
      }
      return { userSel: pick(userSels), passSel: pick(passSels) };
    },
    USER_SELECTOR_CANDIDATES,
    PASS_SELECTOR_CANDIDATES,
  );
}

/**
 * React 17+ controlled inputs: must use the native prototype value setter, not `el.value =`.
 * @see https://github.com/facebook/react/issues/10135
 */
async function setInputValue(page, selector, value) {
  await page.waitForSelector(selector, { visible: true, timeout: 60000 });
  await page.click(selector, { clickCount: 3 });
  await page.evaluate(
    (sel, v) => {
      const el = document.querySelector(sel);
      if (!el) throw new Error(`Missing ${sel}`);
      const tag = el.tagName;
      const proto =
        tag === "TEXTAREA"
          ? window.HTMLTextAreaElement.prototype
          : window.HTMLInputElement.prototype;
      const desc = Object.getOwnPropertyDescriptor(proto, "value");
      if (!desc || !desc.set) throw new Error(`No native value setter for ${tag}`);
      desc.set.call(el, v);
      el.dispatchEvent(new Event("input", { bubbles: true }));
      el.dispatchEvent(new Event("change", { bubbles: true }));
    },
    selector,
    value,
  );
}

/** Fallback: real key events (some builds ignore synthetic Event only). */
async function typeLikeHuman(page, selector, text) {
  await page.waitForSelector(selector, { visible: true, timeout: 60000 });
  await page.click(selector, { clickCount: 3 });
  await page.keyboard.press("Backspace");
  await page.keyboard.type(text, { delay: 15 });
}

async function fillCredentials(page, userSel, passSel, email, password) {
  const useKeyboard = process.env.LC_LOGIN_KEYBOARD === "1";
  if (useKeyboard) {
    await typeLikeHuman(page, userSel, email);
    await typeLikeHuman(page, passSel, password);
    return;
  }
  await setInputValue(page, userSel, email);
  await setInputValue(page, passSel, password);
}

async function readLoginSurfaceErrors(page) {
  return page.evaluate(() => {
    const parts = [];
    const nodes = document.querySelectorAll(
      '[role="alert"], [data-cy="error"], .error__3Yqk, [class*="error"], .text-red, [class*="text-red"]',
    );
    for (const n of nodes) {
      const t = (n.textContent || "").replace(/\s+/g, " ").trim();
      if (t.length > 2 && t.length < 400) parts.push(t);
    }
    return [...new Set(parts)].slice(0, 5).join(" | ") || null;
  });
}

async function clickPrimarySignIn(page) {
  for (const sel of SIGN_IN_SELECTORS) {
    const h = await page.$(sel);
    if (!h) continue;
    try {
      const ok = await h.evaluate((el) => {
        const r = el.getBoundingClientRect();
        return r.width > 0 && r.height > 0;
      });
      if (ok) {
        await h.click();
        return true;
      }
    } finally {
      await h.dispose();
    }
  }
  return false;
}

/**
 * Collect leetcode.com cookies; session may appear shortly after SPA navigation.
 * @returns {Promise<{ csrf: string, session: string, cookieNames: string[] }>}
 */
async function waitForAuthCookies(page, debug, maxWaitMs = 45000) {
  const deadline = Date.now() + maxWaitMs;
  let lastNames = [];

  while (Date.now() < deadline) {
    let cookies;
    try {
      cookies = await page.cookies(page.url(), "https://leetcode.com/");
    } catch {
      cookies = await page.cookies();
    }

    const csrf = cookies.find((c) => c.name === "csrftoken")?.value;
    const session = cookies.find((c) => c.name === "LEETCODE_SESSION")?.value;
    lastNames = [...new Set(cookies.map((c) => c.name))].sort();

    if (csrf && session) {
      return { csrf, session, cookieNames: lastNames };
    }

    await sleep(400);
  }

  const surfaceErr = await readLoginSurfaceErrors(page);

  if (debug) {
    const path = "leetcode-login-debug.png";
    await page.screenshot({ path, fullPage: true });
    console.error(`Wrote ${path}`);
    console.error("[leetcode-login debug] url=", page.url(), "cookieNames=", lastNames.join(", ") || "(none)");
    if (surfaceErr) console.error("[leetcode-login debug] page errors:", surfaceErr);
  }

  throw new Error(
    "Login did not produce LEETCODE_SESSION (csrftoken alone is not enough — you are still anonymous). " +
      `Cookie names: ${lastNames.join(", ") || "(none)"}.` +
      (surfaceErr ? ` Page message: ${surfaceErr}.` : "") +
      " Check password / CAPTCHA / 2FA. PowerShell: use $env:LEETCODE_HEADLESS='0' (not `set`). Try LC_LOGIN_KEYBOARD=1 if inputs are ignored.",
  );
}

/**
 * @param {{
 *   email: string,
 *   password: string,
 *   headless?: boolean | "shell",
 *   loginUrl?: string,
 *   debug?: boolean,
 *   manualCloudflare?: boolean,
 * }} opts
 * @returns {Promise<{ csrf: string, session: string }>}
 */
async function getLeetCodeSessionCookies(opts) {
  const {
    email,
    password,
    headless = true,
    loginUrl = DEFAULT_LOGIN_URL,
    debug = false,
    manualCloudflare = false,
  } = opts;

  const browser = await puppeteer.launch({
    headless,
    args: [
      "--no-sandbox",
      "--disable-setuid-sandbox",
      "--disable-dev-shm-usage",
      "--disable-blink-features=AutomationControlled",
    ],
  });

  try {
    const page = await browser.newPage();
    await page.setViewport({ width: 1280, height: 800 });
    await page.setUserAgent(
      "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/131.0.0.0 Safari/537.36",
    );
    await page.setExtraHTTPHeaders({
      "Accept-Language": "en-US,en;q=0.9",
    });
    await page.evaluateOnNewDocument(() => {
      Object.defineProperty(navigator, "webdriver", { get: () => undefined });
    });

    await page.goto(loginUrl, {
      waitUntil: "domcontentloaded",
      timeout: 90000,
    });

    // SPA / Cloudflare: wait until visible credential fields exist.
    let userSel;
    let passSel;
    try {
      ({ userSel, passSel } = await waitForVisibleCredentialSelectors(page, 90000));
    } catch {
      userSel = null;
      passSel = null;
    }

    if (debug) {
      const info = await page.evaluate(() => ({
        title: document.title,
        href: location.href,
        hasPwd: !!document.querySelector('input[type="password"]'),
        hasIdLogin: !!document.querySelector("#id_login"),
      }));
      console.error("[leetcode-login debug]", info);
    }

    if (!passSel || !userSel) {
      if (debug) {
        const path = "leetcode-login-debug.png";
        await page.screenshot({ path, fullPage: true });
        console.error(`Wrote ${path}`);
      }
      throw new Error(
        "Login form not found (selectors outdated, Cloudflare challenge, or geo block). " +
          "Try local: npm run test:login with LEETCODE_HEADLESS=0 in .env",
      );
    }

    await fillCredentials(page, userSel, passSel, email, password);

    await sleep(500);

    if (manualCloudflare) {
      if (headless !== false) {
        throw new Error(
          "LeetCode uses Cloudflare “Verify you are human” — automation cannot click it. " +
            "Use a visible browser: LEETCODE_HEADLESS=0 and LC_WAIT_FOR_MANUAL_LOGIN=1, " +
            "complete the checkbox in the window, then click Sign In.",
        );
      }
      const ms = Number(process.env.LC_MANUAL_LOGIN_TIMEOUT_MS || 600000);
      console.error(
        "\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n" +
          "  Cloudflare step: in the Chrome window, complete “Verify you are human”,\n" +
          "  then click Sign In. Waiting for LEETCODE_SESSION (up to " +
          Math.max(1, Math.round(ms / 60000)) +
          " min)…\n" +
          "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n",
      );
      const { csrf, session } = await waitForAuthCookies(page, debug, ms);
      return { csrf, session };
    }

    const loginPost = page
      .waitForResponse(
        (res) => {
          if (res.request().method() !== "POST") return false;
          const u = res.url();
          return (
            u.includes("leetcode.com") &&
            (u.includes("/login") ||
              u.includes("/signin") ||
              u.includes("graphql") ||
              u.includes("/accounts/"))
          );
        },
        { timeout: 90000 },
      )
      .catch(() => null);

    await Promise.all([
      loginPost,
      page
        .waitForNavigation({ waitUntil: "networkidle2", timeout: 90000 })
        .catch(() => null),
      (async () => {
        if (await clickPrimarySignIn(page)) return;

        const clicked = await page.evaluate(() => {
          function visible(el) {
            if (!el) return false;
            const r = el.getBoundingClientRect();
            return r.width > 0 && r.height > 0;
          }
          function tryClick(el) {
            if (!visible(el)) return false;
            el.click();
            return true;
          }

          const pwd = document.querySelector(
            "#id_password, input[name=\"password\"], input[type=\"password\"]",
          );
          if (!pwd) return false;

          const form = pwd.closest("form");
          const tryList = [];
          const seen = new Set();

          function add(el) {
            if (el && !seen.has(el)) {
              seen.add(el);
              tryList.push(el);
            }
          }

          for (const sel of ["#signin_btn", '[data-cy="sign-in-btn"]']) {
            add(document.querySelector(sel));
          }

          if (form) {
            form.querySelectorAll('button[type="submit"], input[type="submit"]').forEach(add);
            for (const b of form.querySelectorAll("button")) {
              const t = (b.getAttribute("type") || "").toLowerCase();
              if (t === "button") continue;
              add(b);
            }
            for (const b of form.querySelectorAll("button")) {
              const text = (b.textContent || "").replace(/\s+/g, " ").trim().toLowerCase();
              if (
                text === "sign in" ||
                text === "log in" ||
                text === "login" ||
                text.includes("sign in") ||
                text.includes("log in")
              ) {
                add(b);
              }
            }
          }

          document
            .querySelectorAll('button[type="submit"], input[type="submit"]')
            .forEach(add);

          for (const b of document.querySelectorAll(
            "button, [role=\"button\"], a[role=\"button\"]",
          )) {
            const text = (b.textContent || "").replace(/\s+/g, " ").trim().toLowerCase();
            if (
              text === "sign in" ||
              text === "log in" ||
              text === "login" ||
              /^sign in\b/.test(text) ||
              /^log in\b/.test(text)
            ) {
              add(b);
            }
          }

          for (const el of tryList) {
            if (tryClick(el)) return true;
          }
          return false;
        });

        if (!clicked) {
          await page.focus(passSel);
          await page.keyboard.press("Enter");
        }
      })(),
    ]);

    const postRes = await loginPost;
    if (debug && postRes) {
      console.error(
        "[leetcode-login debug] POST",
        postRes.status(),
        postRes.url().slice(0, 120),
      );
    }

    if (!postRes && debug) {
      console.error("[leetcode-login debug] No matching login POST response observed (SPA may use different URL).");
    }

    const sessionQuick = (await page.cookies("https://leetcode.com/")).find(
      (c) => c.name === "LEETCODE_SESSION",
    );
    if (!sessionQuick) {
      await page.goto("https://leetcode.com/", {
        waitUntil: "domcontentloaded",
        timeout: 60000,
      });
      await sleep(1500);
    }

    const { csrf, session } = await waitForAuthCookies(page, debug);
    return { csrf, session };
  } finally {
    await browser.close();
  }
}

module.exports = { getLeetCodeSessionCookies, DEFAULT_LOGIN_URL };
