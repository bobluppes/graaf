# Opening a PR
This pages describes the process of opening a pull-request from your fork into the main repo. Note that you can open a `Draft PR` if you are still working on your code. Before marking it as `Ready for review`, please consider the following checklist:

- [ ] PR contains a clear description of the changes
- [ ] Unit tests added (if implementing an `enhancement`)
- [ ] Documentation added when applicable (for instance on the public interface of new features)
- [ ] All tests pass
- [ ] Correct labels are added on the PR (see below)

Congrats, you are now ready to open your PR 🎉 The CI will automatically check the code formatting and the test coverage. See [development setup](development-setup.md) on how to check this locally.

## Changelog generation
Please put the correct labels on your PR to facilitate our automatic changelog generation. 

- **breaking-change**: A change which changes the public API
- **enhancement**: New feature
- **documentation**: Improvements or additions to documentation
- **tests**: Improvements to the (unit) tests
- **refactor**: A change which does not change any behavior
- **tooling**: Any changes to the build process, dev tools, or CI steps