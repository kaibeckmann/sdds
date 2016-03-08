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
	echo "reboot $pi"
	ssh $pi -l pi "sudo shutdown -r now" &
done
exit
