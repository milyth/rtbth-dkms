# rtbth-ralink-3290-linux-dkms

This is a Linux kernel module for a Ralink RT3290 wireless device.
It enables [Bluez](http://www.bluez.org) software and driver support for RT3290.

This module has no official support by Mediatek. Support was discontinued.

## Dependencies

- Kernel headers
- DKMS
- Make and a C compiler

## Building and installing

```sh

export MOD_VER=4.1.1
export SOURCE=https://github.com/ry-diffusion/rtbth-ralink-3290-linux-dkms.git

sudo git clone ${SOURCE} /usr/src/rtbth-${MOD_VER} && \
sudo dkms add rtbth/${MOD_VER} && \
sudo dkms build rtbth/${MOD_VER} && \
sudo dkms install rtbth/${MOD_VER} && \
cd /usr/src/rtbth-${MOD_VER} && \
cd tools && \
sudo bash upgrade-firmware.sh && \
cd .. && \
sudo make install && \
sudo systemctl enable --now rtbth

```

## Usage

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
