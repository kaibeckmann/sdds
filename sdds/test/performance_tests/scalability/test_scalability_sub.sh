#!/bin/bash
cd linux_scalability_sub/
./prepare_test.sh
make clean
./generate.sh
make all
../../scripts/./end_test.sh linux_scalability_sub $1 &
./linux_scalability_sub 
make clean
exit
