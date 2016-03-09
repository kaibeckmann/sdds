#!/bin/bash

if [ "$#" -lt 5 ]; then
    echo "usage $0 <msg_count> <max_msg_size> <step_size> <host> <echo> [iface]"
    exit
fi

count=$1
size=$2
step=$3
host=$4
echo=$5
iface="eth0"
if [ "$#" -gt 5 ]; then
    iface=$6
fi

cd ~/sdds/sdds/test/performance_tests/latency/linux_latency_host 
rm -f *.log

for (( i=$step; i<=$size; i=$i+$step )); do
    ./prepare_test.sh $count $i $host $echo $iface 
    ./generate.sh > /dev/null 2>&1
    make_log="make_"$host"_"$count"_"$i".log"
    echo "make latency $count $i"
    make > /dev/null 2> $make_log
    echo "run latency $count $i"
    ./linux_latency_host > /dev/null 2>&1
    echo "clean"
    make clean >/dev/null 2>&1
done

echo "all done"

exit
