#!/bin/bash
if [ "$#" -lt 6 ]; then
	echo "usage $0 <msg_count> <msg_size> <host> <host_ip> <echo> <echo_ip> [iface]"
	exit
fi

iface=eth0
if [ "$#" -gt 6 ]; then
    iface=$7
fi

msg_count=$1
msg_size=$2
host=$3
ip=$4
echo=$5
sub_ip=$6

sed s/{msg_count}/$msg_count/ template.xml | sed s/{msg_size}/$msg_size/ | sed s/{iface}/$iface/ | sed s/{ip}/$ip/ | sed s/{sub_ip}/$sub_ip/ > sdds.xml
