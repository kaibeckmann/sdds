#!/bin/bash

if [ "$#" -lt 4 ]; then
    echo "usage $0 <duration (min)> <max_msg_size> <step_size> <max_mbit> [iface]"
    exit
fi

duration=$1
max_size=$2
step=$3
max_mbit=$4
iface="eth0"
if [ "$#" -gt 4 ]; then
    iface=$5
fi

sub="pi01"
sub_ip="fd29:144d:4196:94:fa66:f718:3c78:cf16"
pub="pi02"

throughput/./abort_throughput.sh "pub" $pub
echo "cleaning up on $pub"
ssh $pub -l pi 'rm -f ~/sdds/sdds/test/performance_tests/throughput_*.log' 'rm -f ~/sdds/sdds/test/performance_tests/throughput/*.log' 'rm -f  ~/sdds/sdds/test/performance_tests/throughput/linux_throughput_pub/*.log'

throughput/./abort_throughput.sh "sub" $sub
echo "cleaning up on $sub"
ssh $sub -l pi 'rm -f ~/sdds/sdds/test/performance_tests/throughput_*.log' 'rm -f ~/sdds/sdds/test/performance_tests/throughput/*.log' 'rm -f  ~/sdds/sdds/test/performance_tests/throughput/linux_throughput_sub/*.log'

# Always start with a message of 1 byte for better plot
if (( $step > 1 )); then
    ssh $pub -l pi 'bash -s' < throughput/./test_throughput_pub.sh $duration 1 $sub_ip $iface $max_mbit
    ssh $sub -l pi 'bash -s' < throughput/./test_throughput_sub.sh $duration 1 $iface
    # piblisher is running forever, abort
    throughput/./abort_throughput.sh "pub" $pub
fi

for (( size=$step; size<=$max_size; size=$size+$step )); do
    ssh $pub -l pi 'bash -s' < throughput/./test_throughput_pub.sh $duration $size $sub_ip $iface $max_mbit
    ssh $sub -l pi 'bash -s' < throughput/./test_throughput_sub.sh $duration $size $iface
    # piblisher is running forever, abort
    throughput/./abort_throughput.sh "pub" $pub
done

throughput/./eval_throughput.sh $sub $duration"min_"$max_size"B_"$max_mbit"mbits"

exit
