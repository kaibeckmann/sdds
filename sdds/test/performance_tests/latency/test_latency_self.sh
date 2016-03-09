#!/bin/bash

if [ "$#" -lt 3 ]; then
    echo "usage $0 <msg_count> <max_msg_size> <step_size> [iface]"
    exit
fi

host="pi06"

count=$1
size=$2
step=$3
iface="eth0"
if [ "$#" -gt 3 ]; then
    iface=$4
fi

cd linux_latency_self 
rm -f *.log

for (( i=$step; i<=$size; i=$i+$step )); do
    ./prepare_test.sh $count $i $iface 
    ./generate.sh > /dev/null 2>&1
    make_log="make_"$host"_"$count"_"$i".log"
    echo "make latency $count $i"
    make > /dev/null 2> $make_log
    latency_log="latency_self_"$host"_"$count"_"$i".log"
    echo "run latency $count $i"
    ./linux_latency_self > /dev/null 2>&1
    echo "clean"
    make clean >/dev/null 2>&1
done

echo "all done"

exit
