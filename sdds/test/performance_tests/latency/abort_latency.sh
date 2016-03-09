#!/bin/bash

if [ "$#" -lt 2 ]; then
    echo "usage $0 <self|echo|host> <host_name>"
    exit
fi

host_name=$2

if [ "$1" = "self"  ]; then
	ssh $host_name -l pi 'killall linux_latency_self'

elif [ "$1" = "echo" ]; then
	ssh $host_name -l pi 'killall linux_latency_echo'

elif [ "$1" = "host" ]; then
	ssh $host_name -l pi 'killall linux_latency_host'

fi
