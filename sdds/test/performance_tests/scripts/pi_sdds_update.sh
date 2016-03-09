#!/bin/bash
host=(
	pi06
	pi05
	pi04
	pi03
	pi02
	pi01
    )

for pi in ${host[@]}; do
	echo "connect to $pi"
	ssh $pi -l pi "cd ~/sdds; git clean -fd; git pull upstream master;" &
done
exit
