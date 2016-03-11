#!/bin/bash

if [ "$#" -lt 6 ]; then
    echo "usage $0 <msg_count> <msg_size> <echo> <echo_ip> <host> <host_ip> [iface]"
    exit
fi

count=$1
size=$2
echo=$3
sub_ip=$4
host=$5
ip=$6
iface="eth0"
if [ "$#" -gt 6 ]; then
    iface=$7
fi

cd ~/sdds/sdds/test/performance_tests/latency/linux_latency_echo

echo "clean latency echo $count $size"
make clean >/dev/null 2>&1
./prepare_test.sh $count $size $echo $sub_ip $host $ip $iface 
./generate.sh > /dev/null 2>&1
make_log="make_"$host"_"$count"_"$size".log"
echo "make latency echo $count $size"
make > /dev/null 2> $make_log
echo "run latency echo $count $size"
log="print_"$host"_"$count"_"$size".log"
./linux_latency_echo > $log 2>&1 &

exit
