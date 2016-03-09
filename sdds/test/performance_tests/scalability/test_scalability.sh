#!/bin/bash
host=(
	pi06
	pi05
	pi04
	pi03
	pi02
	pi01
    )

if (($# < 4)); then
	echo "usage: $0 <number of pubs> <number of pub_subs> <number of subs> <duration (min)> [lbud] [budget] [com] [read]"
	exit
fi

pis=$[$1+$2+$3]
if (($pis > ${#host[@]})); then
	echo "ERROR: Yor are trying to instatiate $pis Pis, but there are only ${#host[@]} Pis available"
	exit
fi

cd scalability

pub_start=0;
pub_end=$1
for (( i=$pub_start; i<$pub_end; i++ )); do
	echo "connect to ${host[$i]}"
	pub_log="\"..\\/..\\/scalability_$4_pub_${host[$i]}_$1_$2_$3.log\""
	ssh ${host[$i]} -l pi 'bash -s' < test_scalability_pub.sh $4 ${host[$i]} $pub_log $5 $6 $7 $8 &
done

pub_sub_start=$pub_end;
pub_sub_end=$pub_end+$2
for (( i=$pub_sub_start; i<$pub_sub_end; i++ )); do
	echo "connect to ${host[$i]}"
	pub_sub_log="\"..\\/..\\/scalability_$4_pubSub_${host[$i]}_$1_$2_$3.log\""
	ssh ${host[$i]} -l pi 'bash -s' < test_scalability_pub_sub.sh $4 ${host[$i]} $pub_sub_log $5 $6 $7 $8 &
done

sub_start=$pub_sub_end;
sub_end=$pub_sub_end+$3
for (( i=$sub_start; i<$sub_end; i++ )); do
	echo "connect to ${host[$i]}"
	sub_log="\"..\\/..\\/scalability_$4_sub_${host[$i]}_$1_$2_$3.log\""
	ssh ${host[$i]} -l pi 'bash -s' < test_scalability_sub.sh $4 ${host[$i]} $sub_log $5 $6 $7 $8 &
done
exit
