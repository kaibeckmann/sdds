#!/bin/bash

if [ "$#" -lt 5 ]; then
    echo "run_latency usage: $0 <msg_count> <max_msg_size> <start_size> <self|echo> <ipv4|ipv6> [iface]"
    exit
fi

msg_count=$1
max_size=$2
start_size=$3
inet=$5
iface="eth0"
if [ "$#" -gt 5 ]; then
    iface=$6
fi

host="pi01"
host_ip="fd29:144d:4196:94:fa66:f718:3c78:cf16"
if [[ "$inet" = "ipv4" ]]; then
   host_ip="10.18.48.200"
fi
echo="pi02"
echo_ip="fd29:144d:4196:94:eaa3:66fb:72af:fcf7"
if [[ "$inet" = "ipv4" ]]; then
   echo_ip="10.18.48.201"
fi

if [ "$4" = "self"  ]; then
    latency/./abort_latency.sh "self" $host
    echo "cleaning up on $host"
	ssh $host -l pi 'rm -f ~/sdds/sdds/test/performance_tests/latency_*.log' 'rm -f ~/sdds/sdds/test/performance_tests/latency/*.log' 'rm -f  ~/sdds/sdds/test/performance_tests/latency/linux_latency_self/*.log'
    ssh $host -l pi 'bash -s' < latency/./test_latency_self.sh $msg_count $max_size $start_size $iface $inet 
elif [ "$4" = "echo" ]; then
    latency/./abort_latency.sh "host" $host
    echo "cleaning up on $host"
	ssh $host -l pi 'rm -f ~/sdds/sdds/test/performance_tests/latency_*.log' 'rm -f ~/sdds/sdds/test/performance_tests/latency/*.log' 'rm -f  ~/sdds/sdds/test/performance_tests/latency/linux_latency_host/*.log'

    latency/./abort_latency.sh "echo" $echo
    echo "cleaning up on $echo"
	ssh $echo -l pi 'rm -f ~/sdds/sdds/test/performance_tests/latency_*.log' 'rm -f ~/sdds/sdds/test/performance_tests/latency/*.log' 'rm -f  ~/sdds/sdds/test/performance_tests/latency/linux_latency_echo/*.log'
    
    for (( size=$start_size; size<=$max_size; size=$size*2 )); do
        ssh $echo -l pi 'bash -s' < latency/./test_latency_echo.sh $msg_count $size $host_ip $iface $inet
        ssh $host -l pi 'bash -s' < latency/./test_latency_host.sh $msg_count $size $echo_ip $iface $inet
        # echo server is runnung forever, abort
        latency/./abort_latency.sh "echo" $echo
        latency/./abort_latency.sh "host" $host
    done
fi

latency/./eval_latency.sh $host $4"_"$inet"_"$msg_count"_"$max_size"B"

exit
