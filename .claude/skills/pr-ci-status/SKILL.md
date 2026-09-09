---
name: pr-ci-status
description: This skill should be used when the user asks to "check PR CI status", "wait for CI to pass", "wait for checks to finish", "poll PR checks", "is CI green yet", or when an agent itself needs to block until a pull request's GitHub Actions checks complete before continuing (e.g. before merging, before reporting a task done). Use it instead of manually re-running `gh pr checks` in a sleep loop.
---

# PR CI Status

Wait for a pull request's CI checks to finish without burning tokens on
repeated polling turns.

## Why this exists

The naive way an agent waits for CI is a loop: call `gh pr checks`, see
pending checks, sleep, call it again, repeat — each iteration costs a full
turn. This skill instead delegates the entire wait to a single deterministic
script invocation. The polling loop runs inside the `gh` CLI process itself
(via `gh pr checks --watch`), so the agent blocks on one tool call and only
resumes once the checks have actually finished.

## Usage

Run the bundled script instead of calling `gh pr checks` directly:

```bash
.claude/skills/pr-ci-status/scripts/wait-for-pr-checks.sh [PR] [-R owner/repo] [-i seconds] [-t seconds]
```

- `PR` — PR number, URL, or branch name. Omit it to use the PR associated
  with the current branch.
- `-R, --repo` — target a repo other than the current one.
- `-i, --interval` — poll interval in seconds, default `60` (i.e. check
  once a minute, matching how often CI status realistically changes).
- `-t, --timeout` — give up after this many seconds, default `3600`. Pick a
  shorter timeout for fast test suites, a longer one for slow pipelines.

The script exits when all checks complete (or the timeout is hit) and
prints the final check table. Exit codes:

| Code | Meaning |
| --- | --- |
| 0 | All checks passed |
| 1 | One or more checks failed |
| 124 | Timed out before checks finished |
| 127 | `gh` CLI is not installed |

## Workflow

1. Open or identify the PR whose checks need to be watched.
2. Invoke the script with an appropriate `--timeout` for the pipeline being
   watched (err on the side of a generous timeout — the script returns as
   soon as checks finish, it does not wait the full timeout on success).
3. Read the exit code and final check table from the single tool result to
   decide the next step (merge, fix failing checks, investigate a timeout).
4. Do not fall back to manually polling `gh pr checks` in a loop — if the
   script times out, either re-invoke it with a longer `--timeout` or
   investigate why checks are stuck, rather than polling turn-by-turn.
