#!/bin/bash

##############################################
# functions
##############################################

function create_experiment() {
    dur=$1
    nodes=$2
    routers=$3
    sniffer=${nodes[0]}
    coord=${nodes[1]}    
    node_list=${nodes[2]}
    router_list=${routers[0]}

    for (( i=3; i<${#nodes[@]}; i++ ))
    do
        node_list=$node_list"+"${nodes[$i]}
    done


    params="submit -d "$dur" -l grenoble,m3,"$sniffer",,sniffer -l grenoble,m3,"$coord",riot_6lowpan_coord/bin/iotlab-m3/default.elf -l grenoble,m3,"$node_list
    if [ -z "$routers" ]; then
        echo "router conf not set";
    else 
        for (( i=1; i<${#routers[@]}; i++ ))
        do
            router_list=$router_list"+"${routers[$i]}
        done
        echo "router conf set: '$router_list'";
        params=$params" -l grenoble,m3,"$router_list",riot_6lowpan_router/bin/iotlab-m3/default.elf "
    fi
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
    count=$5
    size=$6

    echo node-cli "-i" $id "-l" "grenoble,m3,"$pub"+"$sub "-sta"
    node-cli "-i" $id "-l" "grenoble,m3,"$pub"+"$sub "-sta"
    sleep $dur"m"
    echo node-cli "-i" $id "-l" "grenoble,m3,"$pub"+"$sub "-sto"
    node-cli "-i" $id "-l" "grenoble,m3,"$pub"+"$sub "-sto"
 
}

function prepare_testcase() {
    id=$1
    dur=$2
    pub=$3
    sub=$4
    count=$5
    size=$6

    cd riot_latency_echo/
    ./prepare.sh $count $size 
    BOARD=iotlab-m3 make clean2 all
    if [ ! -f bin/iotlab-m3/default.elf ]; then
        echo "compiling riot_latency_echo failed"
        exit
    fi

    cd ../riot_latency_host/
    ./prepare.sh $count $size 
    BOARD=iotlab-m3 make clean2 all
    if [ ! -f bin/iotlab-m3/default.elf ]; then
        echo "compiling riot_latency_host failed"
        exit
    fi

    cd ../

    # flash echo
    echo node-cli "-i "$id" -l grenoble,m3,"$pub" -up riot_latency_echo/bin/iotlab-m3/default.elf"
    node-cli "-i" $id "-l" "grenoble,m3,"$pub "-up" "riot_latency_echo/bin/iotlab-m3/default.elf"
    # flash host
    echo node-cli "-i "$id" -l grenoble,m3,"$sub" -up riot_latency_host/bin/iotlab-m3/default.elf"
    node-cli "-i" $id "-l" "grenoble,m3,"$sub "-up" "riot_latency_host/bin/iotlab-m3/default.elf"

    echo node-cli "-i" $id "-l" "grenoble,m3,"$pub"+"$sub "-sto"
    node-cli "-i" $id "-l" "grenoble,m3,"$pub"+"$sub "-sto"
    
#    echo node-cli "-i" $id "-l" "grenoble,m3,"$pub"+"$sub "-sta"
#    node-cli "-i" $id "-l" "grenoble,m3,"$pub"+"$sub "-sta"
#    sleep $dur"m"
#    echo node-cli "-i" $id "-l" "grenoble,m3,"$pub"+"$sub "-sto"
#    node-cli "-i" $id "-l" "grenoble,m3,"$pub"+"$sub "-sto"
}

#############################################
# MAIN
#############################################

if [ "$#" -lt 6 ]; then
    echo "usage $0 <duration (min)> <repititions> <max_msg_size> <start_size> <msg_count> <node_list> [router_list]"
    exit
fi

duration=$1
repitions=$2
max_size=$3
start_size=$4
msg_count=$5
nodes=(${6//+/ })
routers=(${7//+/ })

node_count=${#nodes[@]}
router_count=${#routers[@]}
test_rounds=0

for (( size=$start_size; size<=$max_size; size=$size*2 )); do
    if [[ "$size" -ge "1536" ]]; then
        size=1536
    fi

    test_rounds=$(($test_rounds + 1))
done

experiment_duration=$(( $duration * $test_rounds * $repitions + 5 ))

if (( $node_count < 4 )); then
    echo "ERROR: Not enough nodes in <node_list>"
    exit
fi

cd latency/riot_6lowpan_coord/
BOARD=iotlab-m3 make clean2 all
if [ ! -f bin/iotlab-m3/default.elf ]; then
    echo "compiling riot_6lowpan_coord failed"
    exit
fi

cd latency/riot_6lowpan_router/
BOARD=iotlab-m3 make clean2 all
if [ ! -f bin/iotlab-m3/default.elf ]; then
    echo "compiling riot_6lowpan_coord failed"
    exit
fi

cd ../

create_experiment $experiment_duration $nodes $routers

for (( size=$start_size; size<=$max_size; size=$size*2 )); do
    if [[ "$size" -ge "1536" ]]; then
        size=1536
    fi

    # set up testcase 
    echo "prepare testcase "$repitions
    prepare_testcase $id $duration ${nodes[2]} ${nodes[3]} $msg_count $size
    # nodes[0]:   sniffer
    # nodes[1]:   coord 
    for i in $(seq $repitions); do
        echo "run testcase"
        run_testcase $id $duration ${nodes[2]} ${nodes[3]} $msg_count $size
    done
done
