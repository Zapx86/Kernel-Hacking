#!/bin/sh
set -x
make clean
make
lsmod
rmmod sys_sgdebugging
insmod sys_sgdebugging.ko
lsmod
