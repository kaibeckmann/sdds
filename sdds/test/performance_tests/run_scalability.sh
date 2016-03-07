#!/bin/bash
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
#	ssh ${host[$i]} -l pi 'rm -f ~/sdds/sdds/test/performance_tests/scalability_*.log' 'rm -f ~/sdds/sdds/test/performance_tests/scalability/*.log'
done

mkdir eval_scalability
test_dur=10
./test_scalability.sh 1 1 1 $test_dur
dur=$[60*$test_dur]
wireshark -i eth1 -f "port 23234 || port 23254" -a duration:$dur -w eval_scalability/scalability_wireshark_1_1_1.pcapng -k &
sleep $dur

./test_scalability.sh 2 1 2 $test_dur
dur=$[60*$test_dur]
wireshark -i eth1 -f "port 23234 || port 23254" -a duration:$dur -w eval_scalability/scalability_wireshark_2_1_2.pcapng -k &
sleep $dur

./test_scalability.sh 2 2 2 $test_dur
dur=$[60*$test_dur]
wireshark -i eth1 -f "port 23234 || port 23254" -a duration:$dur -w eval_scalability/scalability_wireshark_2_2_2.pcapng -k &
sleep $dur

killall wireshark
exit
