---
name: dependabot-merge-train
description: This skill should be used when the user asks to "merge the dependabot PRs", "clear the dependabot backlog", "process dependency PRs", "merge dependabot PRs one by one", or "run a dependabot merge train". Sequentially rebases, reviews, waits on CI for, and merges open dependabot pull requests one at a time so that combinations of dependency bumps never land untested together.
---

# Dependabot Merge Train

Merge every open dependabot pull request into the base branch one at a
time, each rebased onto the latest base branch and CI-verified in
isolation, so no untested combination of dependency bumps ever lands
together.

## Why one at a time

Two dependabot PRs can each pass CI individually against the current base
branch and still break the build once both are merged, because neither was
ever tested against the other's changes. Rebasing and re-running CI for
each PR immediately before merging it — using the base branch as it exists
*after* the previous PR merged — guarantees every merge commit was
actually validated before it landed, not just its source branch in
isolation.

## Workflow

Repeat this loop until no open dependabot PRs remain:

1. **List remaining PRs.**

   ```bash
   .claude/skills/dependabot-merge-train/scripts/list-dependabot-prs.sh [-R owner/repo]
   ```

   Pick the next one to process — default to the lowest PR number unless a
   later one is blocked on an earlier one's outcome.

2. **Bring it up to date with the base branch.** Check
   `gh pr view <PR> --json mergeStateStatus` first. If it is already
   `CLEAN`/`BEHIND`-free relative to the latest base branch (e.g. this is
   the first PR processed and nothing else has merged yet), skip straight
   to review. Otherwise request a rebase and block until dependabot
   delivers it:

   ```bash
   .claude/skills/dependabot-merge-train/scripts/rebase-and-wait.sh <PR> [-R owner/repo] [-i seconds] [-t seconds]
   ```

   This posts `@dependabot rebase` as a PR comment and polls the PR's head
   commit once a minute (configurable) until dependabot pushes the rebase,
   instead of the agent re-checking the PR on every turn. If dependabot
   closes the PR instead of rebasing (it does this when the update is no
   longer needed, e.g. a transitive bump that another merge already
   satisfied), treat it as resolved and move to the next PR.

3. **Review the diff.** Run `gh pr view <PR>` and `gh pr diff <PR>` and
   confirm:
   - The change is confined to manifest/lockfile files (or whatever
     dependabot normally touches in this repo) with no unrelated edits.
   - The version bump direction and release notes in the PR body look
     sane (no major-version jump hiding a breaking change unless that's
     genuinely intended).
   - There isn't an open compatibility concern called out in the PR body
     (dependabot surfaces compatibility scores/release notes there).

   If anything looks off, stop and flag it instead of proceeding — don't
   merge a PR whose contents haven't actually been read.

4. **Wait for CI**, using the `pr-ci-status` skill rather than polling
   manually:

   ```bash
   .claude/skills/pr-ci-status/scripts/wait-for-pr-checks.sh <PR> [-R owner/repo]
   ```

5. **If CI fails**, diagnose before giving up on the PR:
   - Pull the failing job logs (`gh run list --branch <headRefName>` then
     `gh run view <run-id> --log-failed`) to see whether the failure is
     caused by the dependency bump itself, an unrelated flake, or a
     preexisting issue on the base branch.
   - Transient/flaky failures: re-run with `gh run rerun <run-id> --failed`
     and wait again with the same script.
   - Genuine breakage caused by the bump: this is exactly the scenario the
     one-at-a-time process exists to catch. Do not merge. Leave a comment
     explaining the failure, skip this PR, and continue the train with the
     remaining ones — a human needs to decide how to resolve it (patch,
     pin, or close).
   - Failure unrelated to dependencies (base branch was already broken):
     fix the root cause first (outside this loop) before continuing the
     train, since every subsequent PR will inherit the same failure after
     being rebased.

6. **Merge**, once review and CI both pass:

   ```bash
   gh pr merge <PR> [-R owner/repo] --squash --delete-branch
   ```

   Match whatever merge method the repo actually uses if it differs from
   squash — check a couple of recently merged PRs
   (`gh pr list --state merged --limit 5`) if unsure.

7. **Continue the loop.** Go back to step 1 — the base branch has moved,
   so re-list remaining PRs and rebase the next one against the new head
   before reviewing it.

## Notes

- Never merge a PR with pending or failing required checks. If
  `wait-for-pr-checks.sh` times out, either re-invoke it with a longer
  `--timeout` or investigate why checks are stuck — don't fall back to
  merging without a completed CI run.
- Process strictly one PR at a time end-to-end (rebase → review → CI →
  merge) rather than kicking off rebases for several PRs up front; a PR
  rebased earlier goes stale the moment an earlier one in the train
  merges.
- If a PR gets closed or superseded mid-train (dependabot does this when a
  later bump supersedes an earlier one), just re-list and continue — don't
  treat it as a failure.
