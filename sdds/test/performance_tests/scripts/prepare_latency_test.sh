#!/bin/bash
if [ "$#" -lt 5 ]; then
    echo "usage $0 <msg_count> <msg_size> <sub_ip> <iface> <ipv4|ipv6> [local]"
    exit
fi

msg_count=$1
msg_size=$2
sub_ip=$3
dev=$4

pre="fd"
iface=""
if [ "$6" == "local" ]; then
    pre="fe"
    iface=$dev
fi

inet="inet6"
prot="AF_INET6"
if [ "$5" == "ipv4" ]; then
    inet="inet"
    prot="AF_INET"
    pre=""
fi

ip=$(ip addr show dev $dev | sed -e's/^.*'$inet' \('$pre'[^ ]*\)\/.*$/\1/;t;d')

sed s/{iface}/$iface/ template.xml | sed s/{dev}/$dev/ | sed s/{prot}/$prot/  | sed s/{ip}/$ip/ | sed s/{msg_count}/$msg_count/ | sed s/{msg_size}/$msg_size/ | sed s/{sub_ip}/$sub_ip/ > sdds.xml

