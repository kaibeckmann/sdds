#!/bin/bash

if [ "$#" -lt 1 ]; then
    echo "usage $0 <host> [tag]"
    exit
fi

host=$1
tag=$2

eval_dir="eval_throughput_"$tag"_"$(date +%s)
echo "mkdir $eval_dir"
mkdir $eval_dir
scp pi@$host:~/sdds/sdds/test/performance_tests/throughput_*.log $eval_dir	
