#!/bin/bash

if [ "$#" -lt 6 ]; then
    echo "usage $0 <msg_count> <msg_size> <host> <host_ip> <echo> <echo_ip> [iface]"
    exit
fi

count=$1
size=$2
host=$3
ip=$4
echo=$5
sub_ip=$6
iface="eth0"
if [ "$#" -gt 6 ]; then
    iface=$7
fi

cd ~/sdds/sdds/test/performance_tests/latency/linux_latency_host 

echo "clean latency host $count $size"
make clean >/dev/null 2>&1
./prepare_test.sh $count $size $host $ip $echo $sub_ip $iface 
./generate.sh > /dev/null 2>&1
make_log="make_"$host"_"$count"_"$size".log"
echo "make latency host $count $size"
make > /dev/null 2> $make_log
echo "run latency host $count $size"
log="print_"$host"_"$count"_"$size".log"
./linux_latency_host > $log 2>&1 

exit
