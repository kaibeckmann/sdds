#!/bin/sh
if [ "$#" -lt 2 ]; then 
	echo "without latencyBudget: $0 <log file> <pub1|pub2>"
	echo "with latencyBudget:    $0 <log file> <pub1|pub2> lbud [budget] [comm] [read]"
	echo "<log file> example:    \"..\\/scalability.log\""
	exit
fi

dev=eth0
iface=
ip=$(ip addr show dev $dev | sed -e's/^.*inet6 \(fd[^ ]*\)\/.*$/\1/;t;d')

lbud_com_open="<!--"
lbud_com_close="-->"

pub1_com_open="<!--"
pub1_com_close="-->"

pub2_com_open="<!--"
pub2_com_close="-->"

if [ "$3" = "lbud" ]; then
	lbud_com_open=""
	lbud_com_close=""
fi

if [ "$2" = "pub1" ]; then
	pub1_com_open=""
	pub1_com_close=""
fi

if [ "$2" = "pub2" ]; then
	pub2_com_open=""
	pub2_com_close=""
fi

sed s/{ip}/$ip/ template.xml | sed s/{iface}/$iface/ | sed s/{device}/$dev/ | sed s/"<!--lbud"/$lbud_com_open/ | sed s/"lbud-->"/$lbud_com_close/ | sed s/"<!--pub1"/$pub1_com_open/ | sed s/"pub1-->"/$pub1_com_close/ | sed s/"<!--pub2"/$pub2_com_open/ | sed s/"pub2-->"/$pub2_com_close/ | sed s/{log}/$1/ | sed s/{lbud_dur}/$4/ | sed s/{lbud_com}/$5/ | sed s/{lbud_read}/$6/ > sdds.xml
