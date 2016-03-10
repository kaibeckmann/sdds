#!/bin/bash
if [ "$#" -lt 5 ]; then
	echo "usage $0 <duration (min)> <msg_size> <sub_ip> <iface> <max_mbit> [local]"
	exit
fi

duration=$1
msg_size=$2
sub_ip=$3
dev=$4
max_mbit=$5
pre="fd"
iface=""

if [ "$6" == "local" ]; then
    pre="fe"
    iface=$dev
fi

ip=$(ip addr show dev $dev | sed -e's/^.*inet6 \('$pre'[^ ]*\)\/.*$/\1/;t;d')

sed s/{iface}/$iface/ template.xml | sed s/{dev}/$dev/ |  sed s/{ip}/$ip/ | sed s/{duration}/$duration/ | sed s/{max_mbit}/$max_mbit/ | sed s/{msg_size}/$msg_size/ | sed s/{sub_ip}/$sub_ip/ > sdds.xml
