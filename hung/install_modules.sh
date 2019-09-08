#!/bin/sh
set -x
make clean
make
lsmod
rmmod sys_hung
insmod sys_hung.ko
lsmod
