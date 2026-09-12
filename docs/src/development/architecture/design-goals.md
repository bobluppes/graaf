# Design Goals[design-goals.md](design-goals.md)
The project follows the following architectural design goals:

- All business logic is completely decouples from the core graph classes. As such business logic is implemented as free functions.
- New algorithm implementations should build on top of existing algorithms (such as `breadth_first_traverse`) rather than reimplementing similar logic.