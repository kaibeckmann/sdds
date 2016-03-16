#!/bin/bash
host=(
    pi20
    pi19
    pi18
    pi17
    pi16
    pi15
    pi14
    pi13
    pi12
    pi11
    pi10
    pi09
    pi08
    pi07
	pi06
	pi05
	pi04
	pi03
	pi02
	pi01
    )

for pi in ${host[@]}; do
	echo "kill scalability test on $pi"
	ssh $pi -l pi "killall end_test.sh sleep linux_scalability_pub linux_scalability_sub"
done
exit
