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
	echo "reboot $pi"
	ssh $pi -l pi "sudo shutdown -r now" &
done
exit
