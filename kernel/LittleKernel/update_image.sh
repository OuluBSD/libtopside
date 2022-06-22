#!/bin/bash

sudo cp ../../share/kernel/floppy.img ~/.floppy.img
sudo losetup /dev/loop0 ~/.floppy.img
sudo mount /dev/loop0 /mnt
sudo cp "${1}" /mnt/kernel
sudo umount /dev/loop0
sudo losetup -d /dev/loop0 
