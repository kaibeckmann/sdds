#!/bin/bash
if [ "$#" -lt 2 ]; then
	echo "usage $0 <msg_count> <msg_size> [iface]"
	exit
fi

iface=eth0
if [ "$#" -gt 2 ]; then
    iface=$3
fi

ip=$(ip addr show dev $iface | sed -e's/^.*inet6 \(fe[^ ]*\)\/.*$/\1/;t;d')
sub_ip=$ip

msg_count=$1
msg_size=$2
sed s/{msg_count}/$msg_count/ template.xml | sed s/{msg_size}/$msg_size/ | sed s/{iface}/$iface/ | sed s/{ip}/$ip/ | sed s/{sub_ip}/$sub_ip/ > sdds.xml
