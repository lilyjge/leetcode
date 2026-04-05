# LeetCode → GitHub sync

This repo uses [joshcai/leetcode-sync](https://github.com/joshcai/leetcode-sync) to push accepted LeetCode submissions here via GitHub Actions.

## Workflow

The **Sync LeetCode** workflow (`.github/workflows/sync_leetcode.yml`) has two jobs:

1. **`update_cookies`** — Logs into LeetCode with Puppeteer, updates the repository secrets `LEETCODE_CSRF_TOKEN` and `LEETCODE_SESSION`, and passes fresh cookie values to the next job via **job outputs** (with log masking).  
   *Why outputs?* In one workflow run, GitHub does not re-read `${{ secrets.* }}` after those secrets are updated by the API, so the sync job cannot rely on the new values from the secrets context in the same run.

2. **`sync`** — Runs `leetcode-sync` using the outputs from job 1 and pushes commits with `github.token` (needs **contents: write**).

Triggers: **schedule** (Saturdays 08:00 UTC) and **workflow_dispatch**.

## Secrets (repository → Settings → Secrets and variables → Actions)

| Secret | Used by |
|--------|---------|
| `LEETCODE_COOKIE_UPDATE_PAT` | Cookie job — PAT that can **update Actions secrets** for this repo (classic: `repo`; fine-grained: permissions that include repository secrets). `github.token` cannot do this. |
| `LEETCODE_EMAIL` | Cookie job — LeetCode login email |
| `LEETCODE_PASSWORD` | Cookie job — LeetCode password |
| `LEETCODE_CSRF_TOKEN` | Updated each run for reference / tooling; the sync job uses **job outputs**, not this context, in the same run |
| `LEETCODE_SESSION` | Same as above |

## Local script

Cookie refresh logic lives in `.github/scripts/update-leetcode-cookies.js` (libsodium encryption for the GitHub Secrets API). Install with `npm ci` in that directory if you run it locally (set `GITHUB_TOKEN`, `GITHUB_REPOSITORY`, `LEETCODE_EMAIL`, `LEETCODE_PASSWORD`).
