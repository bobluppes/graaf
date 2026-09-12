# Getting a Copy of Graaf
If you want to get a copy for development purposes, simply fork it [here](https://github.com/bobluppes/graaf/fork). In case you are looking to install Graaf on your project, please take a look at the [README](https://github.com/bobluppes/graaf/blob/main/README.md).

## Cloning Your Fork
After [forking](https://github.com/bobluppes/graaf/fork) the repository, you can clone it locally as you would any other repo:

```bash
git clone git@github.com:your-user-name/graaf.git
```

This will clone the repository at your current directory under `./graaf`, which would already be enough to start making changes and open a pull request.

However, at some point you might want to sync changes from the upstream repository into your feature branch (for instance when a critical bug has been patched and your feature relies on the fix). By default your clone is set up to your forked repository on Github, you can verify this by:

```bash
$ git remote -v
origin	git@github.com:your-user-name/graaf.git (fetch)
origin	git@github.com:your-user-name/graaf.git (push)
```

To track and sync changes from the upstream, we add a new remote:

```bash
git remote add upstream git@github.com:bobluppes/graaf.git
```

Now, we can merge changes from the upstream like so:

```bash
git fetch upstream
git merge upstream/main
```

---
For more details on this process see Github's [official guide](https://docs.github.com/en/get-started/quickstart/fork-a-repo) on forking a repo.