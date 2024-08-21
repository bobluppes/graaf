#!/bin/bash

find . -regex '.*\.\(cpp\|h\|hpp\|tpp\|cc\|cxx\)' -exec clang-format-18 -style=file -i {} \;
