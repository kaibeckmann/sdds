#!/bin/bash

if [ "$#" -lt 5 ]; then
    echo "usage $0 <duration (min)> <msg_size> <sub_ip> <iface> <max_mbit> [local]"
    exit
fi

duration=$1
msg_size=$2
sub_ip=$3
iface=$4
max_mbit=$5
loc=$6

echo "clean throughput pub $duration $msg_size"
cd ~/sdds/sdds/test/performance_tests/throughput/linux_throughput_pub
rm -f *.log
make clean > /dev/null 2>&1

echo "prepare throughput pub $duration $msg_size"
./prepare.sh $duration $msg_size $sub_ip $iface $max_mbit $loc

echo "make throughput pub $duration $msg_size"
make_log="make_"$duration"_"$msg_size".log"
./generate.sh > /dev/null 2> $make_log
make > /dev/null 2> $make_log

echo "run throughput pub $duration $msg_size"
log="print_"$duration"_"$msg_size".log"
./linux_throughput_pub > $log 2>&1 &

exit
