#!/bin/bash

if [ "$#" -lt 5 ]; then
    echo "usage $0 <msg_count> <max_msg_size> <sub_ip> <iface> <ipv4|ipv6> [local]"
    exit
fi

count=$1
size=$2
sub_ip=$3
iface=$4
prot=$5
loc=$6

cd ~/sdds/sdds/test/performance_tests/latency/linux_latency_host 

echo "clean latency host $count $size"
make clean >/dev/null 2>&1
./prepare_test.sh $count $size $sub_ip $iface $prot $loc
./generate.sh > /dev/null 2>&1
make_log="make_"$count"_"$size".log"
echo "make latency host $count $size"
make > /dev/null 2> $make_log
echo "run latency host $count $size"
log="print_"$count"_"$size".log"
./linux_latency_host > $log 2>&1 

exit
