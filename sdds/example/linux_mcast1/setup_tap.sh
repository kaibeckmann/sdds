#!/bin/sh

tunctl -t tap0 -u $1
echo 1 > /proc/sys/net/ipv6/conf/all/forwarding
sysctl net.ipv6.conf.tap0.accept_dad=0
ifconfig tap0 up
ip -6 addr add fe80::10/64 dev tap0
ip -6 addr add fe80::20/64 dev tap0
