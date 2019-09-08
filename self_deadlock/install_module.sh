#!/bin/sh
set -x
# WARNING: this script doesn't check for errors, so you have to enhance it in case any of the commands
# below fail.
# lsmod
make
rmmod sys_selfdeadlock
insmod sys_selfdeadlock.ko
# lsmod
