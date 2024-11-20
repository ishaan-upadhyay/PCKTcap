# PCKTcap
A MVP Wireshark clone - packet sniffing with libpcap and visualization in the browser.

# Pre-requisites

This project has the following dependencies to build and run.

```bash
sudo apt-get install libpcap-dev g++ make
```

We've included the following libraries within the repository itself (to keep things simple) - batteries included. See `dependencies` for included libraries.

- [nlohmann/json](https://github.com/nlohmann/json) - JSON for Modern C++, v. 3.11.3

## Development

To get started with development, you'll need the following tools:
```bash


- `pre-commit` - for code formatting and linting; see `.pre-commit-config.yaml` for configuration. Install with `pip install pre-commit` and run `pre-commit install` in the repository.

# Building

Run `make` to build the project.

# Running