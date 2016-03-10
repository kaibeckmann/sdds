#!/bin/bash

if [ "$#" -lt 5 ]; then
    echo "usage $0 <msg_count> <max_msg_size> <step_size> <host> <host_ip> [iface]"
    exit
fi

count=$1
size=$2
step=$3
host=$4
host_ip=$5
iface="eth0"
if [ "$#" -gt 5 ]; then
    iface=$6
fi

cd ~/sdds/sdds/test/performance_tests/latency/linux_latency_self 
rm -f *.log

for (( i=$step; i<=$size; i=$i+$step )); do
    ./prepare_test.sh $count $i $host $host_ip $host $host_ip $iface 
    ./generate.sh > /dev/null 2>&1
    make_log="make_"$host"_"$count"_"$i".log"
    echo "make latency $count $i"
    make > /dev/null 2> $make_log
    echo "run latency $count $i"
    log="print_"$host"_"$count"_"$size".log"
    ./linux_latency_self > $log 2>&1
    echo "clean"
    make clean >/dev/null 2>&1
done

echo "all done"

exit
