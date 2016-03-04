#!/bin/sh
dev=eth0
iface=
ip=$(ip addr show dev $dev | sed -e's/^.*inet6 \(fd[^ ]*\)\/.*$/\1/;t;d')

com_open="<!--"
com_close="-->"

if [ "$2" = "lbud" ]; then
	com_open=""
	com_close=""

elif [ "$#" -eq 0 ]; then 
	echo "without latencyBudget: $0 <log file>"
	echo "with latencyBudget:    $0 <log file> lbud [budget] [comm] [read]"
	echo "<log file> example:    \"..\\/scalability.log\""
	exit
fi

sed s/{ip}/$ip/ template.xml | sed s/{iface}/$iface/ | sed s/"<!--"/$com_open/ | sed s/"-->"/$com_close/ | sed s/{log}/$1/ | sed s/{lbud_dur}/$3/ | sed s/{lbud_com}/$4/ | sed s/{lbud_read}/$5/ > sdds.xml
