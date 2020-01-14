#!/bin/bash

if [ "$#" -lt 5 ]; then
    echo "usage $0 <duration (min)> <max_msg_size> <start_size> <max_mbit> <ipv4|ipv6> [iface|lbud]"
    exit
fi

duration=$1
max_size=$2
start_size=$3
max_mbit=$4
inet=$5
iface="eth0"
lbud=""
if [ "$#" -gt 5 ]; then
    if [[ "$6" = "lbud" ]]; then
        lbud=$6
    else
        iface=$6
    fi
fi

sub="pi01"
sub_ip="fd29:144d:4196:94:fa66:f718:3c78:cf16"
if [[ "$inet" = "ipv4" ]]; then
   sub_ip="10.18.48.200"
fi
pub="pi02"

throughput/./abort_throughput.sh "pub" $pub
echo "cleaning up on $pub"
ssh $pub -l pi 'rm -f ~/sdds/sdds/test/performance_tests/throughput_*.log' 'rm -f ~/sdds/sdds/test/performance_tests/throughput/*.log' 'rm -f  ~/sdds/sdds/test/performance_tests/throughput/linux_throughput_pub/*.log'

throughput/./abort_throughput.sh "sub" $sub
echo "cleaning up on $sub"
ssh $sub -l pi 'rm -f ~/sdds/sdds/test/performance_tests/throughput_*.log' 'rm -f ~/sdds/sdds/test/performance_tests/throughput/*.log' 'rm -f  ~/sdds/sdds/test/performance_tests/throughput/linux_throughput_sub/*.log'

for (( size=$start_size; size<=$max_size; size=$size*2 )); do
    if [[ "$size" -ge "65536" ]]; then
        size=65500
    fi
    ssh $pub -l pi 'bash -s' < throughput/./test_throughput_pub.sh $duration $size $sub_ip $iface $max_mbit $inet $lbud
    ssh $sub -l pi 'bash -s' < throughput/./test_throughput_sub.sh $duration $size $iface $max_mbit $inet $lbud
    # piblisher is running forever, abort
    throughput/./abort_throughput.sh "pub" $pub
done

throughput/./eval_throughput.sh $sub $inet"_"$duration"min_"$max_size"B_"$max_mbit"mbits_"$lbud


exit