# PCKTcap
A MVP Wireshark clone written in C++ - packet sniffing with libpcap and visualization in the browser. This was built for CSCD58, Computer Networks, at the University of Toronto.

With some simplifying assumptions being made (Ethernet II frames, 1500 byte MTU, DNS information only from UDP packets, etc.,), we can capture Ethernet, IPv4, TCP, UDP, ARP, ICMP and DNS header information. The packets are stored in a MongoDB database, and the web UI was built using Next.js.

# Pre-requisites

**Note:** It is recommended to use the provided VM which is fully set up for this project, since the setup can be tedious. Please run `git pull` in the `~/PCKTcap` directory in the VM to ensure you have the latest version of the project. *The VM has been tested on University of Toronto lab machines.*

The VM is available from the link in our submission and is intended to be used with VirtualBox. It is an updated version of the VM provided by Professor Marcelo Ponce for Assignment 3. For graders, if any issues arise, please refer to the fixes provided in the appendix of the assignment first to see if they apply to the VM. Other bugs are discussed at the end of this README.

**The VM will NOT run on Windows if Hyper-V Virtualization is enabled**, as MongoDB > 5.0 requires the AVX instruction set, which is not compatible with Hyper-V. 

To enable AVX pass-through in VirtualBox, go to settings for the VM, enable expert mode, check System > Processor, and enable PAE/NX, the VM is confirmed to work with these settings on the lab machines.

---

Separately, you can run `setup.sh` to install the necessary dependencies. *This script has not been rigorously tested.*

```bash
sudo ./setup.sh
```

This project has the following dependencies to build and run.

```bash
sudo apt-get install libpcap-dev g++ make gnupg curl cmake
```

## MongoDB

We followed the official [MongoDB Community Edition Installation Guide](https://www.mongodb.com/docs/manual/tutorial/install-mongodb-on-ubuntu/), plus the MongoDB C++ driver [installation guide](https://www.mongodb.com/docs/languages/cpp/cpp-driver/current/get-started/download-and-install/).

We assume a plain MongoDB installation accessible at the default port (`27017`) with no authentication. The project currently will not work with authentication enabled. 

To check the MongoDB port number, run `sudo systemctl start mongod`, then `mongosh` and `db.getMongo()`. The URL returned will be formatted as `mongodb://<IP>:<PORT>`. To use a different port, edit `capture/main.cc` and change the `DB_URL` constant. 

## WebUI

To install node.js, run the following commands.

```bash
# installs nvm (Node Version Manager)
curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.40.0/install.sh | bash

# download and install Node.js (you may need to restart the terminal)
nvm install 22
```

Run the following to install the necessary dependencies for the web UI.

```bash
cd pcktcap
npm install
```

# Building

Run `make` from the root of the repository to build the project.

# Running

Run `./PCKTcap -h` to see the available options. 

PCKTcap requires root privileges to run when actually capturing packets, so you will need to run it with `sudo`. It can be stopped using `Ctrl+C`.

Once done, you can navigate to `http://localhost:3000` in the browser to view it, and previous captures. To view the captures, you will need to run the web server, as done below.

```bash
cd pcktcap
npm run dev
```
If you are using the VM provided with the release, use `ifconfig` to check the IP address of the `eth0` interface. Visit `http://<IP>:3000` on the host machine to view the captures.

# Troubleshooting

### Running fails with `error while loading shared libraries: libbsoncxx.so._noabi: cannot open shared object file: no such file or directory`

You need to add the library path to your `LD_LIBRARY_PATH` environment variable.

```bash
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
```

Also, run `sudo ldconfig`. Remake the project and run it again.

### Running `./PCKTcap` or accessing the web UI fails with `Error: connect ECONNREFUSED 127.0.0.1:27017` or other databse-related errors

The `mongod` service is likely down. Check with `sudo systemctl status mongod`. If it is down, start it with `sudo systemctl start mongod`. 

Restart the capture/web server after starting the `mongod` service.

### Accessing the web UI results in an error bubble in the bottom left corner, but the UI is still accessible

This is likely due to an extension interfering with the rendering of the UI. Try reopening the web UI in an incognito window or disabling extensions.

This will not affect the functionality of the web UI, it is simply an internal issue which is handled gracefully.

### Importing the VM results in NS_ERROR_INVALID_ARG (or other errors)

Make sure to remove any existing VMs based on the Mininet VM provided for Assignment 3 from the VirtualBox UI. This is likely due to some sort of conflict with an existing VM (the import was tested and worked on a fresh VirtualBox with the UofT lab machines).

### Starting the VM results in an error due to network adapter names

If the issue relates to the Network Adapter not being found (since, on Linux the Host-Only Adaptor, it defaults to `vbnoxnet0` which is distinct from Windows), open the VM in the UI. Click on the `(Host-Only Adapter, <name>)`, temporarily switch the `Attached to:` field to a non-Host-Only Adapter, then switch it back to `Host-Only Adapter`. This should resolve the issue.