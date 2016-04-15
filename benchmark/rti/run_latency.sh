#!/bin/bash
if [[ "$#" -lt  3 ]]; then
    echo "usage: $0 <msg_count> <max_msg_size> <start_size>"
    exit
fi

host=pi01
echo=pi02
msg_count=$1
max_msg_size=$2
start_size=$3

echo "clean host"
ssh $host -l pi 'killall latency_host' 
ssh $host -l pi 'rm -f *.log latency_host'
echo "clean echo"
ssh $echo -l pi 'killall latency_echo'
ssh $echo -l pi ' rm -f *.log latency_echo'

cd latency

for (( size=$start_size; size<=$max_msg_size; size=$size*2 )); do
    if [[ "$size" -ge "65536" ]]; then
        size=63000
    fi
    echo "build project"
    sed s/{msg_size}/$size/ latency.template > latency.idl
    make clean all
    echo "deploy on host"
    ssh $host -l pi 'rm -f latency_host'
    scp objs/armv6vfphLinux3.xgcc4.7.2/latency_host pi@$host:~/latency_host
    echo "deploy on echo"
    ssh $echo -l pi 'rm -f latency_echo'
    scp objs/armv6vfphLinux3.xgcc4.7.2/latency_echo pi@$echo:~/latency_echo

    log="rti_latency_"$msg_count"_"$size".log"
    ssh $echo -l pi './latency_echo > rti_print_echo_'$msg_count'_'$size'.log' & 
    ssh $host -l pi './latency_host '$msg_count' '$size' '$log' > rti_print_host_'$msg_count'_'$size'.log'  

    ssh $echo -l pi 'killall latency_echo'
done

cd ../
eval_dir="eval_rti_latency_"$msg_count"_"$max_msg_size"_"$(date +%s)
echo "mkdir $eval_dir"
mkdir $eval_dir
scp pi@$host:~/rti_latency_*.log $eval_dir
