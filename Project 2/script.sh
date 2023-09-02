#!/bin/bash
make
sudo insmod prmodule.ko
mjor=$(cat /proc/devices | grep iut_device | tr -dc '0-9')
sudo mknod /dev/iutnode c $mjor 0
sudo python3 test.py
sudo rm /dev/iutnode
sudo rmmod prmodule
make clean
