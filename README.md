# innovaphone-sample-app

## Innovaphone development

Getting started:

First you will need to install Visual Studio (2019) and install [Innovaphone Store SDK](https://store.innovaphone.com/release/134768/download.htm) under the Software tab.

In order to develop apps for Innovaphone, you need to have a couple of instances running, 1) App Platform. 2) PBX

### Virtual device installation

The App Platform comes with 2 options, ARM or x86_64. I choose x86_64 for this development project, though ARM version might work. You can find the download to this on the Innovaphone Store under the App Platform tab.
Along with the App Platform, you will be required to run PBX / IPVA (Innovaphone Virtual Appliance). The App Platform folder might contain the vm image, else it can be found under the Firmware tab in the innovaphone store.

Using [VMware Workstation 15 Player](https://www.vmware.com/uk/products/workstation-player/workstation-player-evaluation.html) or any virtual machine software, you will need to spin up both. Set the Network connection to be NAT to give both instances a local ip address.

### Useful links

SDK Documentation - http://sdk.innovaphone.com/doc/gettingstarted.htm
AppStore Downloads - https://store.innovaphone.com/release/134768/download.htm
