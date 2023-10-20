---
sidebar_position: 2
---

# Alternative Installation Methods

## As a submodule

Graaf can also be installed as a submodule in your project

1. Go to your project directory `cd projectdir`
1. Add Graaf as submodule `git submodule add https://github.com/bobluppes/graaf.git`
1. Then add Graaf as include directory with CMake:

```CMake
   include_directories("graaf/include")
```
