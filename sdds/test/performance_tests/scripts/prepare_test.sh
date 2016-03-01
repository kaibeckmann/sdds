#!/bin/sh
iface=eth0
ip=$(ip addr show dev $iface | sed -e's/^.*inet6 \fd([^ ]*\)\/.*$/\1/;t;d')
sed s/{ip}/$ip/ template.xml | sed s/{iface}/$iface/ > sdds.xml
