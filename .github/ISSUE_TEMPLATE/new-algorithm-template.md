---
name: New Algorithm Template
about: Template used for new algorithms in the Graaf library.
title: "[ALGO]"
labels: enhancement
assignees: ''

---

# [ALGORITHM_NAME]
A short description of what the algorithm does and it's common use cases.

## Syntax
The algorithm should have the following syntax:

```c++
template <typename V, typename E, graph_type T>
[[nodiscard]] return_type your_algorithm_name(const graph<V, E, T>& graph);
```

This should live in the `graaf::algorithm` namespace under `include/graaflib/algorithm`.

## Definition of Done
This issue is done when:

- [ ] The algorithm is implemented
- [ ] The new function has a javadoc-style comment explaining the interface
- [ ] Appropriate tests are added under `test/graaflib/algorithm`
- [ ] A test coverage of at least 95% is reached
- [ ] A documentation entry is added under `docs/docs/algorithms` under the appropriate category
  - Just adding a short description and the algorithm syntax here is fine
  - See the [wiki](https://github.com/bobluppes/graaf/wiki/development-setup#documentation) on how to build the documentation locally
- [ ] The algorithm is added to the list of algorithms in `README.md`
