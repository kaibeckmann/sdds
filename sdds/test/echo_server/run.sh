#!/bin/sh
rumprun-bake hw_virtio echo_server.bin echo_server

#rumprun qemu -i -M 256     -I if,vioif,'-net vde,sock=/var/run/vde2/tap0.ctl'     -W if,inet6,auto -- echo_server.bin
rumprun qemu -i -M 256     -I if,vioif,'-net vde,sock=/var/run/vde2/tap0.ctl'     -W if,inet6,static,fe80::5054:0ff:fe62:bf16/64 -- echo_server.bin
