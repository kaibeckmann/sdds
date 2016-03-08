#!/bin/bash

if (($# < 1)); then
	echo "usage $0 <duration min> [lbud] [budget] [com] [read]"
	exit
fi

host=(
	pi06
	pi05
	pi04
	pi03
	pi02
	pi01
    )

rm -rf eval_scalability

for (( i=0; i<${#host[@]}; i++ )); do
	echo "cleaning up on ${host[$i]}"
	ssh ${host[$i]} -l pi 'rm -f ~/sdds/sdds/test/performance_tests/scalability_*.log' 'rm -f ~/sdds/sdds/test/performance_tests/scalability/*.log'
done

mkdir eval_scalability
test_dur=$1

subs=1
pubs=${#host[@]- $subs}
for (( i=1; i<$pubs; i++ )); do
	./test_scalability.sh $i 0 $subs $test_dur $2 $3 $4 $5
	dur=$[60*($test_dur+1)]
	file="eval_scalability/scalability_wireshark_"$i"_0_"$subs".pcapng"	
	tshark -i eth1 -f "port 23234 || port 23254" -a duration:$dur -w $file > /dev/null
done

lbud=""
if (($2 == "lbud")); then
	lbud="_lbud_"$3"_"$4"_"$5
fi
./eval_scalability.sh
timestamp=$(date +%s)
cp -r eval_scalability eval_scalability_$timestamp$lbud

exit
