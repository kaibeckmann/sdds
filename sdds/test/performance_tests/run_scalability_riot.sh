#!/bin/bash

##############################################
# functions
##############################################

function create_experiment() {
    dur=$1
    nodes=$2
    node_list=$3

    params="submit -d "$dur" -l grenoble,m3,"$node_list
    echo experiment-cli $params
    exp=$(experiment-cli $params)
    id=$(echo $exp | python -c 'import json,sys;obj=json.load(sys.stdin);print obj["id"]')
    echo "experiment ID: "$id
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
st=$5
max=$6
node_list=$7
nodes=(${7//+/ })
lbud=$8

node_count=${#nodes[@]}
test_rounds=$(( ( ($max - $st) + 1) / $step ))
echo $test_rounds
experiment_duration=$(( $duration * ($test_rounds + 1)  ))
echo $experiment_duration

if (( $max+$opp+1 > $node_count )); then
    echo "ERROR: Not enough nodes in <node_list>"
    exit
fi

#cd scalability/riot_6lowpan_coord/
#BOARD=iotlab-m3 make clean clean2 all

#cd ../riot_scalability_pub/
#BOARD=iotlab-m3 make clean clean2 all

#cd ../riot_scalability_sub/
#BOARD=iotlab-m3 make clean clean2 all

#cd ../

create_experiment $experiment_duration $nodes $node_list

