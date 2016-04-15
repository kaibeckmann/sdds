#!/bin/bash

##############################################
# functions
##############################################

function create_experiment() {
    dur=$1
    nodes=$2
    sniffer=${nodes[0]}
    coord=${nodes[1]}    
    node_list=${nodes[2]}

    for (( i=3; i<${#nodes[@]}; i++ ))
    do
        node_list=$node_list"+"${nodes[$i]}
    done

    params="submit -d "$dur" -l grenoble,m3,"$sniffer",,sniffer -l grenoble,m3,"$coord",riot_6lowpan_coord/bin/iotlab-m3/default.elf -l grenoble,m3,"$node_list
    echo experiment-cli $params
    exp=$(experiment-cli $params)
    id=$(echo $exp | python -c 'import json,sys;obj=json.load(sys.stdin);print obj["id"]')
    echo "experiment ID: "$id

    until [ "$state" == "Running" ]; do
        exp=$(experiment-cli get -i $id -s)
        state=$(echo $exp | python -c 'import json,sys;obj=json.load(sys.stdin);print obj["state"]')
        
        if [ "$state" == "Terminated" ]; then
            exit
        fi
        sleep 1
    done

    echo node-cli "-i" $id "-l" "grenoble,m3,"$sniffer"+"$coord "-sta"
    node-cli "-i" $id "-l" "grenoble,m3,"$sniffer"+"$coord "-sta"
    echo "Experiment is now running"
}

function run_testcase() {
    id=$1
    dur=$2
    pub=$3
    sub=$4
    mbit=$5
    size=$6

    cd riot_throughput_pub/
    ./prepare.sh $size $mbit 
    BOARD=iotlab-m3 make clean2 all
    if [ ! -f bin/iotlab-m3/default.elf ]; then
        echo "compiling riot_throughput_pub failed"
        exit
    fi

    cd ../riot_throughput_sub/
    ./prepare.sh $size $dur 
    BOARD=iotlab-m3 make clean2 all
    if [ ! -f bin/iotlab-m3/default.elf ]; then
        echo "compiling riot_throughput_pub failed"
        exit
    fi

    cd ../

    # flash publisher
    echo node-cli "-i "$id" -l grenoble,m3,"$pub" -up riot_throughput_pub/bin/iotlab-m3/default.elf"
    node-cli "-i" $id "-l" "grenoble,m3,"$pub "-up" "riot_throughput_pub/bin/iotlab-m3/default.elf"
    # flash subscriber
    echo node-cli "-i "$id" -l grenoble,m3,"$sub" -up riot_throughput_sub/bin/iotlab-m3/default.elf"
    node-cli "-i" $id "-l" "grenoble,m3,"$sub "-up" "riot_throughput_sub/bin/iotlab-m3/default.elf"

    echo node-cli "-i" $id "-l" "grenoble,m3,"$pub"+"$sub "-sta"
    node-cli "-i" $id "-l" "grenoble,m3,"$pub"+"$sub "-sta"
    sleep $dur"m"
    echo node-cli "-i" $id "-l" "grenoble,m3,"$pub"+"$sub "-sto"
    node-cli "-i" $id "-l" "grenoble,m3,"$pub"+"$sub "-sto"
}

#############################################
# MAIN
#############################################

if [ "$#" -lt 5 ]; then
    echo "usage $0 <duration (min)> <max_msg_size> <start_size> <max_mbit> <node_list>"
    exit
fi

duration=$1
max_size=$2
start_size=$3
max_mbit=$4
nodes=(${5//+/ })

node_count=${#nodes[@]}
test_rounds=0

for (( size=$start_size; size<=$max_size; size=$size*2 )); do
    if [[ "$size" -ge "1536" ]]; then
        size=1536
    fi

    test_rounds=$(($test_rounds + 1))
done

experiment_duration=$(( $duration * $test_rounds + 5 ))

if (( $node_count < 4 )); then
    echo "ERROR: Not enough nodes in <node_list>"
    exit
fi

cd throughput/riot_6lowpan_coord/
BOARD=iotlab-m3 make clean2 all
if [ ! -f bin/iotlab-m3/default.elf ]; then
    echo "compiling riot_6lowpan_coord failed"
    exit
fi

cd ../

create_experiment $experiment_duration $nodes

for (( size=$start_size; size<=$max_size; size=$size*2 )); do
    if [[ "$size" -ge "1536" ]]; then
        size=1536
    fi

    # nodes[0]:   sniffer
    # nodes[1]:   coord 
    run_testcase $id $duration ${nodes[2]} ${nodes[3]} $max_mbit $size
done
