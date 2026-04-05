"use strict";

/**
 * Local check: LeetCode login + cookies only (no GitHub API).
 *
 * From repo root .github/scripts:
 *   npm run test:login
 *
 * Loads the first existing file among:
 *   ../../.env   (repo root)
 *   ../.env
 *   .env
 *
 * Required in .env or environment:
 *   LEETCODE_EMAIL, LEETCODE_PASSWORD
 *
 * Optional:
 *   LEETCODE_HEADLESS=0   — headed browser (often passes Cloudflare when headless fails)
 *   LC_LOGIN_DEBUG=1      — log page title/URL and write leetcode-login-debug.png on failure
 *   LC_LOGIN_KEYBOARD=1   — type email/password with real key events (if React ignores synthetic input)
 *   LC_WAIT_FOR_MANUAL_LOGIN=1 — do not auto-click Sign In; you complete Cloudflare + Sign In (needs LEETCODE_HEADLESS=0)
 */

const fs = require("fs");
const path = require("path");
const { getLeetCodeSessionCookies } = require("./leetcode-login.js");

function loadDotenv() {
  try {
    const envPath = [
      path.join(__dirname, "..", "..", ".env"),
      path.join(__dirname, "..", ".env"),
      path.join(__dirname, ".env"),
    ].find((p) => fs.existsSync(p));
    if (envPath) {
      require("dotenv").config({ path: envPath });
      console.error("Loaded env from", envPath);
    }
  } catch (e) {
    if (e.code === "MODULE_NOT_FOUND") {
      console.error(
        "Install dev deps: cd .github/scripts && npm install\n" +
          "(dotenv is required for test:login)",
      );
      process.exit(1);
    }
    throw e;
  }
}

loadDotenv();

const email = process.env.LEETCODE_EMAIL;
const password = process.env.LEETCODE_PASSWORD;

if (!email || !password) {
  console.error("Set LEETCODE_EMAIL and LEETCODE_PASSWORD (e.g. in repo root .env).");
  process.exit(1);
}

function parseHeadless() {
  const v = process.env.LEETCODE_HEADLESS;
  if (v === "0" || v === "false") return false;
  if (v === "shell") return "shell";
  return true;
}

const headlessMode = parseHeadless();
console.error(
  "Puppeteer headless:",
  headlessMode === false ? "OFF (you should see a Chrome window)" : String(headlessMode),
);

(async () => {
  const debug = process.env.LC_LOGIN_DEBUG === "1";
  const { csrf, session } = await getLeetCodeSessionCookies({
    email,
    password,
    headless: headlessMode,
    debug,
    manualCloudflare: process.env.LC_WAIT_FOR_MANUAL_LOGIN === "1",
  });
  console.log(
    "OK: got cookies (lengths only) csrftoken=%s LEETCODE_SESSION=%s",
    String(csrf.length),
    String(session.length),
  );
})().catch((err) => {
  console.error(err);
  process.exit(1);
});
