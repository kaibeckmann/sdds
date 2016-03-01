#!/bin/sh
dev=eth0
iface=
ip=$(ip addr show dev $dev | sed -e's/^.*inet6 \(fd[^ ]*\)\/.*$/\1/;t;d')
sed s/{ip}/$ip/ template.xml | sed s/{iface}/$iface/ > sdds.xml
