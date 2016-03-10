#!/bin/bash

if [ "$#" -lt 4 ]; then
    echo "usage $0 <duration (min)> <msg_size> <sub_ip> <iface> [local]"
    exit
fi

duration=$1
msg_size=$2
sub_ip=$3
iface=$4

echo "clean throughput pub $duration $msg_size"
cd ~/sdds/sdds/test/performance_tests/throughput/linux_throughput_pub
rm -f *.log
make clean > /dev/null 2>&1

echo "prepare throughput pub $duration $msg_size"
./prepare.sh $duration $msg_size $sub_ip $iface $5

echo "make throughput pub $duration $msg_size"
make_log="make_"$duration"_"$msg_size".log"
make > /dev/null 2> $make_log

echo "run throughput pub $duration $msg_size"
log="print_"$duration"_"$msg_size".log"
./linux_throughput_pub > $log 2>&1 &

exit
