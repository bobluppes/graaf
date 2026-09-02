# CMake integration check

`consumer/` is a minimal standalone CMake project that consumes Graaf via
`FetchContent`, the same way a real downstream project would. It exists to
catch regressions in Graaf's own `CMakeLists.txt` that only surface when
Graaf is built as a subproject rather than top-level (see #310/#312).

Run it locally from the repo root:

```bash
cmake -B /tmp/graaf-consumer-build -S test/cmake_integration/consumer -DGRAAF_SOURCE_DIR="$(pwd)"
cmake --build /tmp/graaf-consumer-build
cmake --install /tmp/graaf-consumer-build --prefix /tmp/graaf-consumer-install
```

This should succeed, and `/tmp/graaf-consumer-install/lib/pkgconfig/graaf.pc`
should **not** exist (pkgconfig generation is only meant for a top-level
Graaf build).
