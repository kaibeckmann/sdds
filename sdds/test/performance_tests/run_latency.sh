#!/bin/bash

if [ "$#" -lt 3 ]; then
    echo "usage $0 <msg_count> <max_msg_size> <step_size> [self] [iface]"
    exit
fi

cd latency

if [ "$4" = "self"  ]; then
    ./test_latency_self.sh $1 $2 $3 $5
fi

exit
