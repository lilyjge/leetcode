"use strict";

const fs = require("fs");
const sodium = require("libsodium-wrappers");
const { getLeetCodeSessionCookies } = require("./leetcode-login.js");

const email = process.env.LEETCODE_EMAIL;
const password = process.env.LEETCODE_PASSWORD;
const token = process.env.GITHUB_TOKEN;
const repoSlug = process.env.GITHUB_REPOSITORY;

function requireEnv(name, value) {
  if (!value || String(value).trim() === "") {
    console.error(`Missing required environment variable: ${name}`);
    process.exit(1);
  }
}

requireEnv("LEETCODE_EMAIL", email);
requireEnv("LEETCODE_PASSWORD", password);
requireEnv("GITHUB_TOKEN", token);
requireEnv("GITHUB_REPOSITORY", repoSlug);

const [owner, repo] = repoSlug.split("/");
if (!owner || !repo) {
  console.error("GITHUB_REPOSITORY must be owner/repo");
  process.exit(1);
}

async function githubJson(url, options = {}) {
  const res = await fetch(url, {
    ...options,
    headers: {
      Accept: "application/vnd.github+json",
      Authorization: `Bearer ${token}`,
      "X-GitHub-Api-Version": "2022-11-28",
      ...(options.headers || {}),
    },
  });
  const text = await res.text();
  if (!res.ok) {
    throw new Error(`${options.method || "GET"} ${url} -> ${res.status}: ${text}`);
  }
  return text ? JSON.parse(text) : {};
}

async function getRepoPublicKey() {
  return githubJson(
    `https://api.github.com/repos/${owner}/${repo}/actions/secrets/public-key`,
  );
}

async function putRepoSecret(secretName, secretValue, keyId, encryptedValue) {
  await githubJson(
    `https://api.github.com/repos/${owner}/${repo}/actions/secrets/${secretName}`,
    {
      method: "PUT",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({
        encrypted_value: encryptedValue,
        key_id: keyId,
      }),
    },
  );
}

function encryptSecret(plain, publicKeyB64) {
  const binkey = sodium.from_base64(publicKeyB64, sodium.base64_variants.ORIGINAL);
  const binsec = sodium.from_string(plain);
  const encBytes = sodium.crypto_box_seal(binsec, binkey);
  return sodium.to_base64(encBytes, sodium.base64_variants.ORIGINAL);
}

/** Same-run handoff to the next job (secrets.* is frozen for the whole run). */
function writeStepOutputs(csrf, session) {
  const outFile = process.env.GITHUB_OUTPUT;
  if (!outFile) return;

  console.log(`::add-mask::${csrf}`);
  console.log(`::add-mask::${session}`);

  const esc = (name, value) => {
    const delim = `LCC_${name}_${process.pid}_${Date.now()}`;
    fs.appendFileSync(outFile, `${name}<<${delim}\n${value}\n${delim}\n`, "utf8");
  };
  esc("csrf", csrf);
  esc("session", session);
}

function parseHeadless() {
  const v = process.env.LEETCODE_HEADLESS;
  if (v === "0" || v === "false") return false;
  if (v === "shell") return "shell";
  return true;
}

(async () => {
  await sodium.ready;
  const { key_id: keyId, key: publicKeyB64 } = await getRepoPublicKey();

  const debug =
    process.env.LC_LOGIN_DEBUG === "1" || process.env.RUNNER_DEBUG === "1";

  const { csrf, session } = await getLeetCodeSessionCookies({
    email,
    password,
    headless: parseHeadless(),
    debug,
    manualCloudflare: process.env.LC_WAIT_FOR_MANUAL_LOGIN === "1",
  });

  await putRepoSecret(
    "LEETCODE_CSRF_TOKEN",
    csrf,
    keyId,
    encryptSecret(csrf, publicKeyB64),
  );
  await putRepoSecret(
    "LEETCODE_SESSION",
    session,
    keyId,
    encryptSecret(session, publicKeyB64),
  );

  writeStepOutputs(csrf, session);

  console.log("Updated repository secrets LEETCODE_CSRF_TOKEN and LEETCODE_SESSION.");
})().catch((err) => {
  console.error(err);
  process.exit(1);
});
