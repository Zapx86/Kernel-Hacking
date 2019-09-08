#!/bin/sh
set -x
make clean
make
lsmod
rmmod sys_mutex
insmod sys_mutex.ko
lsmod
