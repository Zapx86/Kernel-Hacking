#!/bin/sh
set -x
make clean
make
lsmod
rmmod sys_atomic
insmod sys_atomic.ko
lsmod
