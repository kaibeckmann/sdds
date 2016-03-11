#!/bin/bash

if [ "$#" -lt 3 ]; then
    echo "usage $0 <duration (min)> <msg_size> <iface> [local]"
    exit
fi


duration=$1
msg_size=$2
iface=$3
sub_ip="unnecessary"
max_mbit="unnecessary"
loc=$5

echo "clean throughput sub $duration $msg_size"
cd ~/sdds/sdds/test/performance_tests/throughput/linux_throughput_sub
rm -f *.log
make clean > /dev/null 2>&1

echo "prepare throughput sub $duration $msg_size"
./prepare.sh $duration $msg_size $sub_ip $iface $max_mbit $loc

echo "make throughput sub $duration $msg_size"
make_log="make_"$duration"_"$msg_size".log"
./generate.sh > /dev/null 2> $make_log
make > /dev/null 2> $make_log

echo "run throughput sub $duration $msg_size"
log="print_"$duration"_"$msg_size".log"
./linux_throughput_sub > $log 2>&1

exit
