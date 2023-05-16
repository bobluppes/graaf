# Contributing to Graaf
Thank you for considering contributing to Graaf! We welcome any contributions that help improve the library. To ensure a smooth collaboration process, please take a moment to review the guidelines below.

## Ways to Contribute
- **Bug reports**: If you encounter a bug or unexpected behavior while using Graaf, please open a new issue on our [issue tracker](https://github.com/bobluppes/graaf/issues). Include a clear description of the problem, steps to reproduce it, and any relevant details.
- **Feature requests**: If you have a feature idea or enhancement suggestion for Graaf, we encourage you to submit a new issue on the [issue tracker](https://github.com/bobluppes/graaf/issues). Describe the desired functionality and provide any relevant context that could help us understand the request.
- **Pull requests**: If you have implemented a bug fix, added a new feature, or made any other improvements to Graaf, feel free to submit a pull request. Please ensure that your code follows our coding conventions and include tests and documentation when applicable.

## Development Setup
To set up a local development environment for Graaf, follow these steps:

```bash
# 1) Clone the repository
git clone git@github.com:bobluppes/graaf.git
mkdir -p graaf/build && cd graaf/build

# 2) Build the project
cmake ..
cmake --build .

# Run the tests to ensure everything is working correctly
ctest
```

You can commit your changes and push them to your forked repository. Before opening a PR, please consider the following checklist:

- [ ] Tests added
- [ ] Documentation added when applicable
- [ ] All tests pass
- [ ] PR contains a clear description of the changes

Congrats, you are now ready to open your PR 🎉

## Code Style
We follow a specific code style to maintain consistency throughout the library. Please ensure that your code adheres to the following guidelines:

- Use a consistent indentation style (e.g., tabs or spaces).
- Follow descriptive and meaningful variable, function, and class names.
- Add appropriate comments to explain complex code sections or algorithms.
- Keep lines of code within a reasonable length (e.g., 80-120 characters).
- Follow existing naming conventions and code patterns.

## Code of Conduct
Please note that we have a Code of Conduct in place to ensure a respectful and inclusive community environment. By participating in the Graaf project, you agree to abide by its terms. Instances of abusive, harassing, or otherwise unacceptable behavior should be reported to the project maintainers.

Thank you for your interest in contributing to Graaf! Your contributions are greatly appreciated and help make the library better for everyone.