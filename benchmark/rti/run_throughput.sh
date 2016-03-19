#!/bin/bash
if [[ "$#" -lt  4 ]]; then
    echo "usage: $0 <duration (min)> <max_msg_size> <start_size> <mbps>"
    exit
fi

host=pi01
echo=pi02
duration=$1
max_msg_size=$2
start_size=$3
mbps=$4

echo "clean sub"
ssh $host -l pi 'killall throughput_sub' 
ssh $host -l pi 'rm -f *.log throughput_sub'
echo "clean pub"
ssh $echo -l pi 'killall throughput_pub'
ssh $echo -l pi ' rm -f *.log throughput_pub'

cd throughput

for (( size=$start_size; size<=$max_msg_size; size=$size*2 )); do
    echo "build project"
    sed s/{msg_size}/$size/ throughput.template > throughput.idl
    make clean all
    echo "deploy on sub"
    ssh $host -l pi 'rm -f throughput_sub'
    scp objs/armv6vfphLinux3.xgcc4.7.2/throughput_sub pi@$host:~/throughput_sub
    echo "deploy on pub"
    ssh $echo -l pi 'rm -f throughput_pub'
    scp objs/armv6vfphLinux3.xgcc4.7.2/throughput_pub pi@$echo:~/throughput_pub

    log="rti_throughput_"$duration"_"$size".log"
    ssh $echo -l pi './throughput_pub '$mbps' '$size' > rti_print_pub_'$duration'_'$size'.log' & 
    ssh $host -l pi './throughput_sub '$duration' '$log ' > rti_print_sub_'$duration'_'$size'.log'  

    ssh $echo -l pi 'killall throughput_pub'
done

cd ../
eval_dir="eval_rti_throughput_"$duration"_"$max_msg_size"_"$(date +%s)
echo "mkdir $eval_dir"
mkdir $eval_dir
scp pi@$host:~/rti_throughput_*.log $eval_dir
