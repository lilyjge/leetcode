<#
.SYNOPSIS
  Refresh LeetCode GitHub Actions secrets (csrftoken + LEETCODE_SESSION) in one run.

.DESCRIPTION
  - Loads repo-root .env (KEY=value lines; # comments OK).
  - Sets GITHUB_TOKEN from GITHUB_TOKEN or LEETCODE_COOKIE_UPDATE_PAT.
  - Sets GITHUB_REPOSITORY from env or parses `git remote get-url origin`.
  - Runs `npm ci` under .github/scripts, opens headed Chrome, fills credentials.
  - With manual Cloudflare mode (default): complete Turnstile + Sign In in the browser; script polls for session.

.PARAMETER SkipManualWait
  Try fully automated login (usually fails on Cloudflare). Default: wait for you in the browser.

.PARAMETER RepoRoot
  Repository root (folder containing .github). Default: this script's directory.

.EXAMPLE
  .\refresh-leetcode-cookies.ps1

.EXAMPLE
  .\refresh-leetcode-cookies.ps1 -SkipManualWait
#>
[CmdletBinding()]
param(
  [switch] $SkipManualWait,
  [string] $RepoRoot = $PSScriptRoot
)

$ErrorActionPreference = "Stop"

function Import-DotEnv {
  param([string] $Path)
  if (-not (Test-Path -LiteralPath $Path)) { return }
  Get-Content -LiteralPath $Path | ForEach-Object {
    $line = $_.Trim()
    if ($line -match "^\s*#" -or $line -eq "") { return }
    if ($line -match "^([A-Za-z_][A-Za-z0-9_]*)=(.*)$") {
      $key = $Matches[1]
      $val = $Matches[2].Trim()
      if (
        ($val.StartsWith('"') -and $val.EndsWith('"')) -or
        ($val.StartsWith("'") -and $val.EndsWith("'"))
      ) {
        $val = $val.Substring(1, $val.Length - 2)
      }
      Set-Item -Path "Env:$key" -Value $val
    }
  }
}

function Resolve-GitHubRepository {
  param([string] $Root)
  Push-Location $Root
  try {
    $url = git remote get-url origin 2>$null
    if (-not $url) { return $null }
    if ($url -match "github\.com[/:]([^/]+)/([^/.]+?)(?:\.git)?\s*$") {
      return "$($Matches[1])/$($Matches[2])"
    }
  }
  finally {
    Pop-Location
  }
  return $null
}

$RepoRoot = (Resolve-Path -LiteralPath $RepoRoot).Path
# Windows PowerShell 5.1: Join-Path only accepts two arguments (use nested calls).
$ScriptsDir = Join-Path (Join-Path $RepoRoot ".github") "scripts"
$EnvFile = Join-Path $RepoRoot ".env"

if (-not (Test-Path -LiteralPath $ScriptsDir)) {
  Write-Error "Missing .github/scripts under: $RepoRoot"
}

Import-DotEnv -Path $EnvFile

if (-not $env:GITHUB_TOKEN -and $env:LEETCODE_COOKIE_UPDATE_PAT) {
  $env:GITHUB_TOKEN = $env:LEETCODE_COOKIE_UPDATE_PAT
}

if (-not $env:GITHUB_REPOSITORY) {
  $inferred = Resolve-GitHubRepository -Root $RepoRoot
  if ($inferred) {
    $env:GITHUB_REPOSITORY = $inferred
    Write-Host "Using GITHUB_REPOSITORY=$inferred (from git remote)."
  }
}

$required = @("GITHUB_TOKEN", "GITHUB_REPOSITORY", "LEETCODE_EMAIL", "LEETCODE_PASSWORD")
$missing = @(
  $required | Where-Object {
    $v = [Environment]::GetEnvironmentVariable($_)
    [string]::IsNullOrWhiteSpace($v)
  }
)
if ($missing.Count -gt 0) {
  Write-Error @"
Missing environment variables: $($missing -join ', ')

Set them in repo-root .env or before running, e.g.:
  GITHUB_TOKEN or LEETCODE_COOKIE_UPDATE_PAT  (PAT with permission to update Actions secrets)
  GITHUB_REPOSITORY  (optional if origin is github.com)
  LEETCODE_EMAIL
  LEETCODE_PASSWORD
"@
}

$env:LEETCODE_HEADLESS = "0"
if ($SkipManualWait) {
  Remove-Item Env:LC_WAIT_FOR_MANUAL_LOGIN -ErrorAction SilentlyContinue
}
else {
  $env:LC_WAIT_FOR_MANUAL_LOGIN = "1"
}

Write-Host ""
Write-Host "npm ci → .github/scripts" -ForegroundColor Cyan
Push-Location $ScriptsDir
try {
  npm ci
  if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

  Write-Host ""
  Write-Host "Starting cookie refresh (headed Chrome)…" -ForegroundColor Cyan
  if (-not $SkipManualWait) {
    Write-Host "When the window opens: complete Cloudflare, then Sign In." -ForegroundColor Yellow
  }
  node .\update-leetcode-cookies.js
  exit $LASTEXITCODE
}
finally {
  Pop-Location
}
