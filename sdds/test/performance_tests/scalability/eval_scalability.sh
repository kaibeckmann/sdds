#!/bin/bash
host=(
	pi06
	pi05
	pi04
	pi03
	pi02
	pi01
    )

mkdir ../eval_scalability
for (( i=0; i<${#host[@]}; i++ )); do
	echo "connect to ${host[$i]}"
	scp pi@${host[$i]}:~/sdds/sdds/test/performance_tests/scalability_*.log ../eval_scalability/.	
done

for file in ../eval_scalability/*.pcapng; do
	tshark -2 -r $file > "${file%.pcapng}.wslog"
done
