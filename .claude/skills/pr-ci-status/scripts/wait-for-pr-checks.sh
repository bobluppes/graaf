#!/usr/bin/env bash
# Blocks until a pull request's CI checks finish, polling at a fixed interval.
#
# This wraps `gh pr checks --watch`, which does its own polling loop inside
# the `gh` process. Running it as a single tool call lets the caller block on
# one deterministic command instead of repeatedly invoking `gh pr checks`
# (or sleeping and re-checking) itself, which burns tokens on every poll.
set -euo pipefail

usage() {
  cat <<'EOF'
Usage: wait-for-pr-checks.sh [PR] [-R owner/repo] [-i seconds] [-t seconds]

Blocks until all CI checks on a pull request finish, polling at a fixed
interval, then prints the final check table and exits with gh's status
code.

Arguments:
  PR              PR number, URL, or branch (default: current branch's PR)

Options:
  -R, --repo      owner/repo to check (passed through to gh)
  -i, --interval  Poll interval in seconds (default: 60)
  -t, --timeout   Give up after this many seconds (default: 3600)
  -h, --help      Show this help

Exit codes:
  0    all checks passed
  8    some checks are still pending (only possible without --watch; not
       expected here since this script always watches to completion)
  1    one or more checks failed
  124  timed out waiting for checks to finish
  127  the gh CLI is not installed
EOF
}

interval=60
timeout_sec=3600
repo=()
pr=()

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
      pr=("$1")
      shift
      ;;
  esac
done

if ! command -v gh >/dev/null 2>&1; then
  echo "error: gh CLI is not installed or not on PATH" >&2
  exit 127
fi

echo "Polling CI checks every ${interval}s (timeout ${timeout_sec}s)..." >&2

set +e
timeout "$timeout_sec" gh pr checks "${pr[@]}" "${repo[@]}" --watch --interval "$interval"
status=$?
set -e

if [[ $status -eq 124 ]]; then
  echo "RESULT: timed out after ${timeout_sec}s — checks did not finish in time" >&2
fi

exit "$status"
