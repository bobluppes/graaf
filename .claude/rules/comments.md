# Comments

Keep comments to a minimum. Express intent through clear names and good abstractions, not prose.

Only write a comment to call out non-obvious rationale: why a particular approach was chosen, a workaround for a specific limitation, or a subtle invariant the code relies on.

Do not:

- Restate what the code already says.
- Describe what was *not* done, the state of the code before a change, or hypothetical situations that could go wrong. Comments describe the code as it is.
- Reference the change being made (e.g. "now uses X", "replaced Y", "fixed for Z"). That belongs in the commit message or PR description.

Keep every comment grounded in the implementation it sits next to.
