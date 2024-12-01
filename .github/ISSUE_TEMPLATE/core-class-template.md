---
name: Core Class Template
about: Template used for new core classes in the Graaf library.
title: "[CORE]"
labels: enhancement
assignees: ''

---

# [CLASS_NAME]
A short description of what the class does and it's common use cases.

## Syntax
An initial idea for the (public) interface of the new class is as follows:<br>
_(note that this is not set in store and merely serves as a starting point)_

```c++
class my_class {
  public:
    //...
}
```

This class should live in the `graaf` namespace under `include/graaflib/`.

## Definition of Done
This issue is done when:

- [ ] The new class is implemented
- [ ] The new class has a javadoc-style comment for the entire class and for the public methods
- [ ] Appropriate tests are added under `test/graaflib/algorithm`
  - [ ] A test coverage of at least 95% is reached
