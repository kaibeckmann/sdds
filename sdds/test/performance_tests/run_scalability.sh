
#!/bin/bash

if (($# < 1)); then
	echo "usage $0 <duration min>"
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

for (( i=1; i<5; i++ )); do
	./test_scalability.sh $i 1 1 $test_dur
	dur=$[60*($test_dur+1)]
	file="eval_scalability/scalability_wireshark_"$i"_1_1.pcapng"	
	tshark -i eth1 -f "port 23234 || port 23254" -a duration:$dur -w $file
done

#./test_scalability.sh 2 1 2 $test_dur
#dur=$[60*$test_dur]
#tshark -i eth1 -f "port 23234 || port 23254" -a duration:$dur -w eval_scalability/scalability_wireshark_2_1_2.pcapng

#./test_scalability.sh 2 2 2 $test_dur
#dur=$[60*$test_dur]
#tshark -i eth1 -f "port 23234 || port 23254" -a duration:$dur -w eval_scalability/scalability_wireshark_2_2_2.pcapng

exit
