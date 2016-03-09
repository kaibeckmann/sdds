#!/bin/bash

if [ "$#" -lt 3 ]; then
    echo "usage $0 <msg_count> <max_msg_size> <step_size> [self] [iface]"
    exit
fi

host="pi01"
echoPi=$host

if [ "$4" = "self"  ]; then
    echo "cleaning up on $host"
	ssh $host -l pi 'rm -f ~/sdds/sdds/test/performance_tests/latency_*.log' 'rm -f ~/sdds/sdds/test/performance_tests/latency/*.log'
    ssh $host -l pi 'bash -s' < latency/./test_latency_self.sh $1 $2 $3 $host $5
    
    eval_dir="eval_latency_self_"$(date +%s)
    mkdir $eval_dir
	scp pi@$host:~/sdds/sdds/test/performance_tests/latency_*.log $eval_dir	
fi

exit
