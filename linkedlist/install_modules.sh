#!/bin/sh
set -x
make clean
make
lsmod
rmmod sys_linkedlist
insmod sys_linkedlist.ko
lsmod
