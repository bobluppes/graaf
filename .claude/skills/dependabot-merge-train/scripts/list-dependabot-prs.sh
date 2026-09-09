#!/usr/bin/env bash
# List open dependabot pull requests, oldest (lowest PR number) first.
set -euo pipefail

usage() {
  cat <<'EOF'
Usage: list-dependabot-prs.sh [-R owner/repo]

Lists open pull requests authored by dependabot, oldest first, printing
number, merge state, branch, and title as tab-separated columns. Use the
PR numbers as the processing order for a sequential dependabot merge
train: rebase, review, wait for CI, merge, then move to the next one.

Options:
  -R, --repo   owner/repo to query (passed through to gh)
  -h, --help   Show this help
EOF
}

repo=()
while [[ $# -gt 0 ]]; do
  case "$1" in
    -R|--repo)
      repo=(-R "$2")
      shift 2
      ;;
    -h|--help)
      usage
      exit 0
      ;;
    *)
      echo "unknown argument: $1" >&2
      usage
      exit 2
      ;;
  esac
done

if ! command -v gh >/dev/null 2>&1; then
  echo "error: gh CLI is not installed or not on PATH" >&2
  exit 127
fi

gh pr list --state open --author app/dependabot "${repo[@]}" \
  --json number,title,headRefName,mergeStateStatus,updatedAt \
  --jq 'sort_by(.number) | .[] | [(.number|tostring), .mergeStateStatus, .headRefName, .title] | @tsv'
