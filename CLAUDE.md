# Comments

Only use comments to call out non-obvious rationale or design choices (e.g. why a particular approach was taken, a workaround for a specific limitation, or a subtle invariant) — not to restate what the code already makes clear. Prefer solutions that are self-documenting through clear names and proper abstraction instead of relying on comments to explain what the code does.

Never leak implementation details in documentation comments on public APIs. Document what a public API does and how to use it, not how it is implemented internally — internal details belong in the implementation, not in the public-facing doc comment.
