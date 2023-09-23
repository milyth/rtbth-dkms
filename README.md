This is a Linux kernel module for a Ralink RT3290 wireless device.
It enables [Bluez](http://www.bluez.org) software and driver support for RT3290.

This module has no official support by Mediatek. Support was discontinued.

### Dependencies ### 
- Kernel headers
- DKMS
- Make and a C compiler

### Building and installing ###
```sh
sudo git clone https://github.com/milyth/rtbth-dkms.git /usr/src/rtbth-4.0.0
sudo dkms add rtbth/4.0.0
sudo dkms build rtbth/4.0.0
sudo dkms install rtbth/4.0.0
cd /usr/src/rtbth-4.0.0
sudo make install
sudo systemctl enable --now rtbth
``` 

### Usage ###

```sh
# Init
sudo modprobe rtbth
sudo rfkill unblock bluetooth
hcitool dev # check

# Switch off
sudo rfkill block bluetooth

# Switch on
sudo rfkill unblock bluetooth

# Shutdown
sudo pkill -2 rtbt
sudo rmmod rtbth
```


### Installation: ###

[Ubuntu and derivatives](https://launchpad.net/~blaze/+archive/ubuntu/rtbth-dkms)
