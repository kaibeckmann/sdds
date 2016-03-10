#!/bin/bash

if [ "$#" -lt 2 ]; then
    echo "usage $0 <pub|sub> <host_name>"
    exit
fi

host_name=$2

if [ "$1" = "pub"  ]; then
    echo "kill throughput pub"
	ssh $host_name -l pi 'killall linux_throughput_pub'
    exit
elif [ "$1" = "sub" ]; then
    echo "kill throughput sub"
	ssh $host_name -l pi 'killall linux_throughput_sub'
    exit
else
    echo "usage $0 <pub|sub> <host_name>"
    exit
fi
