---
name: Algorithm Documentation Template
about: Template used for improving the documentation of existing algorithms.
title: "[DOCS]"
labels: documentation, good first issue, help wanted
assignees: ''

---

# Documentation [ALGORITHM_NAME]
The goal of this issue if the improve the documentation of an existing algorithm. This documentation should go into the algorithms section of our [docusaurus docs](https://bobluppes.github.io/graaf/docs/algorithms/intro).

More detail on how to build the documentation locally can be found on the [wiki](https://github.com/bobluppes/graaf/wiki/development-setup#documentation).

An existing documentation page exists, which should be extended. The page can be found under `docs/docs/algorithms/`.
OR
A new documentation page should be created under `docs/docs/algorithms`. Potentially, a new subdirectory should be created for the algorithm's category.

The corresponding algorithm is called `` and can be found under `include/graaflib/algorithm/`.

## Documentation Contents
The documentation entry should adhere to the following template:

```markdown
# [ALGORITHM_NAME]
- A short description of the algorithm, what does it do and in which use cases is it used.
- What are the limitations of the algorithm, does it work on both directed and undirected graphs? Does it consider edge weights, and if yes, does it support negative weights?
- Link to the wikipedia entry on the algorithm.

## Syntax
- A code block with the syntax of the algorithm. This should now include any javadoc comments.
- An explanation of the parameters (including template parameters) and the return type.

## (Optional) See also
- If there are similar algorithms, or we have a slightly different version of the same algorithm, you can link it here.
- If we have an example (found on the example page of the docs) which uses this algorithm, you can link it here.
```
