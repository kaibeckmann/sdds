#!/bin/bash

help_str="usage $0 <duration min> <sub|pub> <opp_nodes> <step> <start> <max> [lbud] [budget] [com] [read]"

if (($# < 6)); then
    echo $help_str
	exit
fi
host=(
    pi01
    pi02
    pi03
    pi04
    pi05
    pi06
    pi07
    pi08
    pi09
    pi10
    pi11
    pi12
    pi13
    pi14
    pi15
    pi16
    pi17
    pi18
    pi19
    pi20
    )

rm -rf eval_scalability

for (( i=0; i<${#host[@]}; i++ )); do
	echo "cleaning up on ${host[$i]}"
	ssh ${host[$i]} -l pi 'rm -f ~/sdds/sdds/test/performance_tests/scalability_*.log' 'rm -f ~/sdds/sdds/test/performance_tests/scalability/*.log'
done

mkdir eval_scalability
test_dur=$1

if [ "$2" = "pub" ]; then
    subs=$3
    step=$4
    max_pubs=${#host[@]- $subs}
    st=$5
    pubs=$6
    if [[ "$pubs" -gt "$max_pubs" ]]; then
        $pubs = $max_pubs
    fi

    for (( i=$st; i<$pubs; i=$i+$step )); do
        pis=$[$i+$subs]
        if (($pis > ${#host[@]})); then
            break
        fi 
        scalability/./test_scalability.sh $i 0 $subs $test_dur $7 $8 $9 $10
        dur=$[60*($test_dur+1)]
        file="eval_scalability/scalability_wireshark_"$i"_0_"$subs".pcapng"	
        tshark -i eth1 -f "port 23234 || port 23254" -a duration:$dur -w $file
    done
elif [ "$2" = "sub" ]; then
    pubs=$3
    step=$4
    max_subs=${#host[@]- $pubs}
    st=$5
    subs=$6
    if [[ "$subs" -gt "$max_subs" ]]; then
        $subs = $max_subs
    fi

    for (( i=$st; i<$subs; i=$i+$step )); do
        pis=$[$i+$pubs]
        if (($pis > ${#host[@]})); then
            break
        fi 
        scalability/./test_scalability.sh $pubs 0 $i $test_dur $7 $8 $9 $10
        dur=$[60*($test_dur+1)]
        file="eval_scalability/scalability_wireshark_"$pubs"_0_"$i".pcapng"	
        tshark -i eth1 -f "port 23234 || port 23254" -a duration:$dur -w $file
    done
else
    echo $help_str
	exit
fi

lbud=""
if [ "$4" = "lbud" ]; then
	lbud="_lbud_"$8"_"$9"_"$10
fi
scalability/./eval_scalability.sh
timestamp=$(date +%s)
eval_dir="eval_scalability_"$2"_"$pubs"_0_"$subs"_"$timestamp$lbud
echo cp -r eval_scalability $eval_dir
cp -r eval_scalability $eval_dir

exit
