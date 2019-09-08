#!/bin/sh
set -x
make clean
make
#lsmod
rmmod sys_dmadevice
insmod sys_dmadevice.ko
#lsmod
