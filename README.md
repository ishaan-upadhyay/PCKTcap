# PCKTcap
A MVP Wireshark clone - packet sniffing with libpcap and visualization in the browser. This was built for CSCD58, Computer Networks, at the University of Toronto.

# Pre-requisites

You can run `setup.sh` to install the necessary dependencies.

```bash
sudo ./setup.sh
```

This project has the following dependencies to build and run.

```bash
sudo apt-get install libpcap-dev g++ make gnupg curl
```

## MongoDB

We followed the official [MongoDB Community Edition Installation Guide](https://www.mongodb.com/docs/manual/tutorial/install-mongodb-on-ubuntu/).

We've included the following libraries within the repository itself (to keep things simple) - batteries included. See `dependencies` for included libraries.

- [nlohmann/json](https://github.com/nlohmann/json) - JSON for Modern C++, v. 3.11.3

# Building

Run `make` to build the project.

# Running

# Troubleshooting

### Running fails with `error while loading shared libraries: libbsoncxx.so._noabi: cannot open shared object file: no such file or directory`

You need to add the library path to your `LD_LIBRARY_PATH` environment variable.

```bash
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
```

Also, run `sudo ldconfig`. Remake the project and run it again.