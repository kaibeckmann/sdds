#!/bin/bash
if [ "$#" -lt 4 ]; then
	echo "usage $0 <msg_count> <msg_size> <host> <echo> [iface]"
	exit
fi

iface=eth0
if [ "$#" -gt 4 ]; then
    iface=$5
fi

msg_count=$1
msg_size=$2
host=$3
echo=$4

ip=$(host $host | sed -e's/^.*address \(fd[^ ]*\)/\1/;t;d')
sub_ip=$(host $echo | sed -e's/^.*address \(fd[^ ]*\)/\1/;t;d')

sed s/{msg_count}/$msg_count/ template.xml | sed s/{msg_size}/$msg_size/ | sed s/{iface}/$iface/ | sed s/{ip}/$ip/ | sed s/{sub_ip}/$sub_ip/ > sdds.xml
