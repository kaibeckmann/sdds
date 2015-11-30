#!/bin/sh
rumpbake hw_generic test_rump.bin test_rump

rumprun qemu -i -M 18     -I if,vioif,'-net tap,script=no,ifname=tap0'     -W if,inet6,static,fe80:2::5054:ff:fe12:3456/64 -- test_rump.bin
