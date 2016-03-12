#!/bin/bash
if [ "$#" -lt 6 ]; then
    echo "usage $0 <duration (min)> <msg_size> <sub_ip> <iface> <max_mbit> <ipv4|ipv6> [local]"
    exit
fi

duration=$1
msg_size=$2
sub_ip=$3
dev=$4
max_mbit=$5

pre="fd"
iface=""
if [ "$7" == "local" ]; then
    pre="fe"
    iface=$dev
fi

inet="inet6"
prot="AF_INET6"
if [ "$6" == "ipv4" ]; then
    inet="inet"
    prot="AF_INET"
    pre=""
fi

ip=$(ip addr show dev $dev | sed -e's/^.*'$inet' \('$pre'[^ ]*\)\/.*$/\1/;t;d')

sed s/{iface}/$iface/ template.xml | sed s/{dev}/$dev/ | sed s/{prot}/$prot/  | sed s/{ip}/$ip/ | sed s/{duration}/$duration/ | sed s/{max_mbit}/$max_mbit/ | sed s/{msg_size}/$msg_size/ | sed s/{sub_ip}/$sub_ip/ > sdds.xml
