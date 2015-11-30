#!/bin/sh
rumpbake hw_generic test_linux.bin test_linux

rumprun qemu -i -M 128 -I if,vioif,-net tap,script=no,ifname=tap0 -W if,inet6,static,fe80:2::5054:ff:fe12:3456/64 -- test_linux.bin
rumprun qemu -i -M 10 -I if,vioif,-net tap,script=no,ifname=tap0 -W if,inet6,static,fe80:2::5054:ff:fe12:3456/64 -- test_linux.bin
