#!/bin/bash

if [ "$#" -lt 5 ]; then
    echo "test_latency_self usage: $0 <msg_count> <max_msg_size> <start_size> <iface> <ipv4|ipv6> [local]"
    exit
fi

count=$1
max_size=$2
start_size=$3
sub_ip="unnecessary"
iface=$4
inet=$5
loc=$6

cd ~/sdds/sdds/test/performance_tests/latency/linux_latency_self 

for (( size=$start_size; size<=$max_size; size=$size*2 )); do
    ./prepare_test.sh $count $size $sub_ip $iface $inet $loc
    ./generate.sh > /dev/null 2>&1
    make_log="make_"$count"_"$size".log"
    echo "make latency $count $size"
    make > /dev/null 2> $make_log
    echo "run latency $count $size"
    log="print_"$count"_"$size".log"
    ./linux_latency_self > $log 2>&1
    echo "clean"
    make clean >/dev/null 2>&1
done

echo "all done"

exit
