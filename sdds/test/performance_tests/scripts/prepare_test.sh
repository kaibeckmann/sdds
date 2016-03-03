#!/bin/sh
dev=eth0
iface=
ip=$(ip addr show dev $dev | sed -e's/^.*inet6 \(fd[^ ]*\)\/.*$/\1/;t;d')

com_open="<!--"
com_close="-->"

if [ "$1" = "lbud" ]; then
	com_open=""
	com_close=""

elif [ "$#" -gt 0 -a "$1" != "lbud" ]; then 
	echo "without latencyBudget: $0"
	echo "with latencyBudget:    $0 lbud [budget] [comm] [read]"
	exit
fi

sed s/{ip}/$ip/ template.xml | sed s/{iface}/$iface/ | sed s/"<!--"/$com_open/ | sed s/"-->"/$com_close/ | sed s/{lbud_dur}/$2/ | sed s/{lbud_com}/$3/ | sed s/{lbud_read}/$4/ > sdds.xml
