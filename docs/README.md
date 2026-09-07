# Website

This website is built using [mdBook](https://rust-lang.github.io/mdBook/), a command line tool to create books with Markdown.

### Installation

```
$ cargo install mdbook
```

### Local Development

```
$ mdbook serve
```

This command starts a local development server and opens up a browser window. Most changes are reflected live without having to restart the server.

### Build

```
$ mdbook build
```

This command generates static content into the `book` directory and can be served using any static contents hosting service.
