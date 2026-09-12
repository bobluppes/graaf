# Development Setup
This page describes the minimal development setup to facilitate contributing to the project. This document assumes you are working on a Linux system, specific instructions might differ depending on your OS.

To compile the project locally:

```bash
# 1) Clone the repository - clone your own fork if you want to contribute
git clone git@github.com:bobluppes/graaf.git
mkdir -p graaf/build && cd graaf/build

# 2) Build the project
cmake ..
cmake --build .

# Run the tests to ensure everything is working correctly
ctest
```

## Formatting
All source files are formatted according to the predefined `clang-format` `Google` style. In the CI this is enforced by checking the source files with `clang-format` version 15 using the provided `.clang-format` file.

### Format locally
It is advised to format your changes locally before pushing.

#### Requirements
- `clang-format` version 15

```bash
# At project root
clang-format -style=file -i **/*.cpp **/*.h **/*.tpp
```

#### Integration with VSCode
On VSCode you can install the extension `xaver.clang-format`. With the following [settings](https://code.visualstudio.com/docs/getstarted/settings#_settings-json-file), your IDE can then be configured to use `clang-format` on saving a file:

```json
"clang-format.executable": "clang-format"
"clang-format.assumeFilename": ".clang-format"

"editor.defaultFormatter": "xaver.clang-format"
"editor.formatOnSave": true
```

## Coverage
[Codecov](https://app.codecov.io/github/bobluppes/graaf) is used to track the coverage of the unit tests. The target coverage is set to 90% but going for full coverage is highly encouraged. When opening a PR, `codecov-bot` will automatically comment the coverage report. Pushing to the feature branch will update the coverage comment.

It is possible to generate a coverage report locally. This requires `lcov` to be installed and to have [this](https://github.com/bilke/cmake-modules/blob/master/CodeCoverage.cmake) CMake plugin present under `cmake-modules`.

```bash
apt-get install lcov -y

# At project root
git clone https://github.com/bilke/cmake-modules.git
```

Now we can pass the `ENABLE_COVERAGE=True` flag to CMake in order to generate the coverage target.

```bash
mkdir build && cd build

cmake .. -DENABLE_COVERAGE=True

# Generate the coverage report
make ctest_coverage
```

## Documentation
We are using Docusaurus for the public documentation of the library. This documentation is recorded in markdown files, which are compiled to a static website using Docusaurus. It is possible to build this locally and serve it using a development server:

```bash
cd docs

# Build the documentation
yarn

# Start the development server
yarn start

# Generate a production build and perform basic verification
yarn build
```