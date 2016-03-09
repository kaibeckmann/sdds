#!/bin/bash

if [ "$#" -lt 1 ]; then
    echo "usage $0 <host>"
    exit
fi

host=$1

eval_dir="eval_latency_self_"$(date +%s)
mkdir $eval_dir
scp pi@$host:~/sdds/sdds/test/performance_tests/latency_*.log $eval_dir	
