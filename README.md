# innovaphone-sample-app

## Innovaphone development

Getting started:

First you will need to install Visual Studio (2019) and install [Innovaphone Store SDK](https://store.innovaphone.com/release/134768/download.htm) under the Software tab.

In order to develop apps for Innovaphone, you need to have a couple of applications/machines running:
  - App Platform
  - PBX

### Virtual device installation

The App Platform comes with 2 options, ARM or x86_64.<br />
I chose x86_64 for this development project, though ARM version might work. You can find the download to this on the Innovaphone Store under the App Platform tab.<br />
Along with the App Platform, you will be required to run PBX / IPVA (Innovaphone Virtual Appliance). The App Platform folder might contain the vm image, else it can be found under the Firmware tab in the innovaphone store.

Using [VMware Workstation 15 Player](https://www.vmware.com/uk/products/workstation-player/workstation-player-evaluation.html) or any virtual machine software, you will need to spin up both. Set the Network connection to be NAT to give both instances a local ip address.

Once both instances are running, copy down both IPs address as they will come in handy later on. <br />
Now try to login to the app platform to ensure that instance is working, username is generally `admin` and the password is either `ipapps` or `pwd`

### Useful links

SDK Documentation - http://sdk.innovaphone.com/doc/gettingstarted.htm <br />
AppStore Downloads - https://store.innovaphone.com/release/134768/download.htm
