#!/bin/bash

if [ "$#" -lt 5 ]; then
    echo "usage $0 <msg_count> <max_msg_size> <step_size> <echo> <host> [iface]"
    exit
fi

count=$1
size=$2
step=$3
echo=$4
host=$5
iface="eth0"
if [ "$#" -gt 5 ]; then
    iface=$6
fi

cd ~/sdds/sdds/test/performance_tests/latency/linux_latency_echo
rm -f *.log

for (( i=$step; i<=$size; i=$i+$step )); do
    ./prepare_test.sh $count $i $echo $host $iface 
    ./generate.sh > /dev/null 2>&1
    make_log="make_"$host"_"$count"_"$i".log"
    echo "make latency $count $i"
    make > /dev/null 2> $make_log
    echo "run latency $count $i"
    ./linux_latency_echo > /dev/null 2>&1
    echo "clean"
    make clean >/dev/null 2>&1
done

echo "all done"

exit
