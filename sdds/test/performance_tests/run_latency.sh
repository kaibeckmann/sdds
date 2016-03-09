#!/bin/bash

if [ "$#" -lt 3 ]; then
    echo "usage $0 <msg_count> <max_msg_size> <step_size> <self|echo> [iface]"
    exit
fi

host="pi01"
host_ip="fd29:144d:4196:94:fa66:f718:3c78:cf16"
echo="pi02"
echo_ip="d29:144d:4196:94:eaa3:66fb:72af:fcf7"

if [ "$4" = "self"  ]; then
    echo "cleaning up on $host"
	ssh $host -l pi 'rm -f ~/sdds/sdds/test/performance_tests/latency_*.log' 'rm -f ~/sdds/sdds/test/performance_tests/latency/*.log'
    ssh $host -l pi 'bash -s' < latency/./test_latency_self.sh $1 $2 $3 $host $host_ip $5
    
    latency/./eval_latency.sh
elif [ "$4" = "echo" ]; then
    echo "cleaning up on $host"
	ssh $host -l pi 'rm -f ~/sdds/sdds/test/performance_tests/latency_*.log' 'rm -f ~/sdds/sdds/test/performance_tests/latency/*.log'
    echo "cleaning up on $echo"
	ssh $echo -l pi 'rm -f ~/sdds/sdds/test/performance_tests/latency_*.log' 'rm -f ~/sdds/sdds/test/performance_tests/latency/*.log'
    
    ssh $host -l pi 'bash -s' < latency/./test_latency_host.sh $1 $2 $3 $host $host_ip $echo $echo_ip $5 &
    ssh $echo -l pi 'bash -s' < latency/./test_latency_echo.sh $1 $2 $3 $echo $echo_ip $host $host_ip $5 &
fi

exit
