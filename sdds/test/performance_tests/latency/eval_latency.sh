#!/bin/bash

if [ "$#" -lt 1 ]; then
    echo "usage $0 <host> [self|echo]"
    exit
fi

host=$1
name=$2

eval_dir="eval_latency_"$name"_"$(date +%s)
echo "mkdir $eval_dir"
mkdir $eval_dir
scp pi@$host:~/sdds/sdds/test/performance_tests/latency_*.log $eval_dir	
