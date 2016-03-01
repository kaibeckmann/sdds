#!/bin/bash
cd linux_scalability_pub/
./prepare_test.sh
make clean
./generate.sh
make all
../../scripts/./end_test.sh linux_scalability_pub $1 &
./linux_scalability_pub 
make clean
exit
