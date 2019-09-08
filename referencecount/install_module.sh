#!/bin/sh
set -x
make clean
make
lsmod
rmmod sys_referencecount
insmod sys_referencecount.ko
lsmod
