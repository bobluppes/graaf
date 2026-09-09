#!/usr/bin/env bash
# Ask dependabot to rebase a PR onto the current base branch, then block
# until it pushes the new commit (or the timeout elapses), polling at a
# fixed interval instead of re-checking the PR on every agent turn.
set -euo pipefail

usage() {
  cat <<'EOF'
Usage: rebase-and-wait.sh PR [-R owner/repo] [-i seconds] [-t seconds]

Comments "@dependabot rebase" on PR, then polls its head commit until it
changes, printing the new SHA once the rebase lands.

Arguments:
  PR              PR number

Options:
  -R, --repo      owner/repo (passed through to gh)
  -i, --interval  Poll interval in seconds (default: 60)
  -t, --timeout   Give up after this many seconds (default: 900)
  -h, --help      Show this help

Exit codes:
  0    dependabot pushed a new commit
  124  timed out waiting for the rebase
  127  the gh CLI is not installed
EOF
}

interval=60
timeout_sec=900
repo=()
pr=""

while [[ $# -gt 0 ]]; do
  case "$1" in
    -R|--repo)
      repo=(-R "$2")
      shift 2
      ;;
    -i|--interval)
      interval="$2"
      shift 2
      ;;
    -t|--timeout)
      timeout_sec="$2"
      shift 2
      ;;
    -h|--help)
      usage
      exit 0
      ;;
    *)
      pr="$1"
      shift
      ;;
  esac
done

if [[ -z "$pr" ]]; then
  echo "error: PR number is required" >&2
  usage
  exit 2
fi

if ! command -v gh >/dev/null 2>&1; then
  echo "error: gh CLI is not installed or not on PATH" >&2
  exit 127
fi

before_sha=$(gh pr view "$pr" "${repo[@]}" --json headRefOid -q .headRefOid)
gh pr comment "$pr" "${repo[@]}" --body "@dependabot rebase" >/dev/null

echo "Requested rebase on PR #${pr} (head was ${before_sha}); polling every ${interval}s (timeout ${timeout_sec}s)..." >&2

elapsed=0
while (( elapsed < timeout_sec )); do
  sleep "$interval"
  elapsed=$((elapsed + interval))
  current_sha=$(gh pr view "$pr" "${repo[@]}" --json headRefOid -q .headRefOid)
  if [[ "$current_sha" != "$before_sha" ]]; then
    echo "RESULT: rebased, new head ${current_sha}"
    exit 0
  fi
done

echo "RESULT: timed out after ${timeout_sec}s waiting for dependabot to rebase PR #${pr}" >&2
exit 124
