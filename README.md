# LeetCode → GitHub sync

This repo uses [joshcai/leetcode-sync](https://github.com/joshcai/leetcode-sync) to push accepted LeetCode submissions here via GitHub Actions.

## Cloudflare (Turnstile) and CI

LeetCode’s email/password login includes a **Cloudflare “Verify you are human”** step. **Headless automation on GitHub-hosted runners cannot complete that challenge**, and the **Sign In** button stays disabled until you do.

So:

- **Scheduled / `workflow_dispatch` sync** (`.github/workflows/sync_leetcode.yml`) only reads **`LEETCODE_CSRF_TOKEN`** and **`LEETCODE_SESSION`** from repository secrets. It does **not** run Puppeteer on GitHub.
- When those cookies expire, **refresh them on your machine** (see below) or paste new values from the browser into **Settings → Secrets**.

## Workflow

**Sync LeetCode** runs `joshcai/leetcode-sync@v1.7` with `github.token` (**contents: write**). Triggers: **schedule** (Saturdays 08:00 UTC) and **workflow_dispatch**.

Repo **Settings → Actions → General → Workflow permissions** should allow **Read and write** if commits fail with permission errors.

## Secrets (repository → Settings → Secrets and variables → Actions)

| Secret | Purpose |
|--------|---------|
| `LEETCODE_CSRF_TOKEN` | `csrftoken` cookie (used by sync) |
| `LEETCODE_SESSION` | `LEETCODE_SESSION` cookie (used by sync) |
| `LEETCODE_COOKIE_UPDATE_PAT` | Only for **local** `update-leetcode-cookies.js` — classic PAT with `repo` (or fine-grained token that can update Actions secrets) |
| `LEETCODE_EMAIL` | LeetCode login email (local script) |
| `LEETCODE_PASSWORD` | LeetCode password (local script) |

## Refresh cookies locally (Cloudflare manual step)

### One command (recommended)

From the **repo root** in PowerShell:

```powershell
.\refresh-leetcode-cookies.ps1
```

If execution policy blocks scripts: `powershell -ExecutionPolicy Bypass -File .\refresh-leetcode-cookies.ps1`

Put in repo root **`.env`** (do not commit it): `LEETCODE_EMAIL`, `LEETCODE_PASSWORD`, and either `GITHUB_TOKEN` or `LEETCODE_COOKIE_UPDATE_PAT` (PAT that can update Actions secrets). `GITHUB_REPOSITORY` is optional if `git remote origin` is a `github.com` URL.

A Chrome window opens with email/password filled. **Complete the Cloudflare checkbox**, click **Sign In**, then wait; the script polls for `LEETCODE_SESSION` (default **10 minutes**; set `LC_MANUAL_LOGIN_TIMEOUT_MS` in `.env` if needed).

- **Automated attempt** (usually blocked by Cloudflare): `.\refresh-leetcode-cookies.ps1 -SkipManualWait`

### Manual steps (same as the script)

From `.github/scripts`:

```powershell
npm ci
$env:GITHUB_TOKEN = "<PAT with repo + secrets write>"
$env:GITHUB_REPOSITORY = "your-username/your-repo"
$env:LEETCODE_HEADLESS = "0"
$env:LC_WAIT_FOR_MANUAL_LOGIN = "1"
$env:LEETCODE_EMAIL = "your-email"
$env:LEETCODE_PASSWORD = "your-password"
node update-leetcode-cookies.js
```

### Local login test only (no GitHub API)

```powershell
cd .github/scripts
npm install
$env:LEETCODE_HEADLESS = "0"
$env:LC_WAIT_FOR_MANUAL_LOGIN = "1"
npm run test:login
```

Use **`$env:…` in PowerShell**, not `set` (which does not propagate to `npm`).

Optional: `LC_LOGIN_DEBUG=1` writes `leetcode-login-debug.png` on failure; `LC_LOGIN_KEYBOARD=1` types keys instead of synthetic input.

### Paste from the browser

Log in manually at [leetcode.com](https://leetcode.com), open DevTools → **Application** → **Cookies**, copy `csrftoken` and `LEETCODE_SESSION`, then create/update the two secrets on GitHub.
