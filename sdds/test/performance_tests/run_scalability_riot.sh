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

function start_logging() {
    file=$1

    for n in $nodes; do
        host="m3-"$n
        echo "netcat "$host" 20000 &> "$host"_"$file
        netcat $host 20000 &> $host"_"$file &  
    done
}

function run_testcase() {
    id=$1
    dur=$2
    pub_list=$3
    pub_count=$4
    sub_list=$5
    sub_count=$6
    log_file="riot_scalability_"$pub_count"_0_"$sub_count".log"

    # flash publisher
    echo node-cli "-i "$id" -l grenoble,m3,"$pub_list" -up riot_scalability_pub/bin/iotlab-m3/default.elf"
    node-cli "-i" $id "-l" "grenoble,m3,"$pub_list "-up" "riot_scalability_pub/bin/iotlab-m3/default.elf"
    # flash subscriber
    echo node-cli "-i "$id" -l grenoble,m3,"$sub_list" -up riot_scalability_sub/bin/iotlab-m3/default.elf"
    node-cli "-i" $id "-l" "grenoble,m3,"$sub_list "-up" "riot_scalability_sub/bin/iotlab-m3/default.elf"

    #serial_aggregator &> $log_file&
    #sa_pid=$(echo $!)
    #echo serial_aggregator PID: $sa_pid
    echo node-cli "-i" $id "-l" "grenoble,m3,"$pub_list"+"$sub_list "-sta"
    node-cli "-i" $id "-l" "grenoble,m3,"$pub_list"+"$sub_list "-sta"
    sleep $dur"m"
    echo node-cli "-i" $id "-l" "grenoble,m3,"$pub_list"+"$sub_list "-sto"
    node-cli "-i" $id "-l" "grenoble,m3,"$pub_list"+"$sub_list "-sto"
    #kill -KILL $sa_pid
}

#############################################
# MAIN
#############################################

help_str="usage: "$0" <duration min> <sub|pub> <opp_nodes> <step> <start> <max> <node_list> [lbud]" 

if [ "$#" -lt 7 ]; then
    echo $help_str
    exit
fi

duration=$1
mode=$2
opp=$3
step=$4
sta=$5
max=$6
nodes=(${7//+/ })
lbud=$8

node_count=${#nodes[@]}
test_rounds=$(( ( ($max - $sta) + 1) / $step ))
experiment_duration=$(( $duration * $test_rounds + 5 ))

if (( $max+$opp+2 > $node_count )); then
    echo "ERROR: Not enough nodes in <node_list>"
    exit
fi

cd scalability/riot_6lowpan_coord/
BOARD=iotlab-m3 make clean2 all
if [ ! -f bin/iotlab-m3/default.elf ]; then
    echo "compiling riot_6lowpan_coord failed"
    exit
fi

cd ../riot_scalability_pub/
BOARD=iotlab-m3 make clean2 all
if [ ! -f bin/iotlab-m3/default.elf ]; then
    echo "compiling riot_scalability_pub failed"
    exit
fi

cd ../riot_scalability_sub/
BOARD=iotlab-m3 make clean2 all
if [ ! -f bin/iotlab-m3/default.elf ]; then
    echo "compiling riot_scalability_pub failed"
    exit
fi

cd ../

create_experiment $experiment_duration $nodes

for (( size=$sta; size<=$max; size=$size+$step )); do    
    # nodes[0]:   sniffer
    # nodes[1]:   coord 
    offset=2
    opp_list=${nodes[$offset]}
    for (( i=1; i<$opp; i++ )); do
        opp_list=$opp_list"+"${nodes[$offset+$i]}
    done

    offset=$offset+$opp
    node_list=${nodes[$offset]}
    for (( i=1; i<$size; i++ )); do
        node_list=$node_list"+"${nodes[$offset+$i]}
    done

    if [ "$mode" == "pub" ]; then
        echo "run_testcase "$id" "$duration" "$node_list" "$size" "$opp_list" "$opp
        run_testcase $id $duration $opp_list $opp $node_list $size
    else 
        echo "run_testcase "$id" "$duration" "$opp_list" "$opp" "$node_list" "$size
        run_testcase $id $duration $opp_list $opp $node_list $size
    fi
done
