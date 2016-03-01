#!/bin/bash
cd linux_scalability_pub_sub/
./prepare_test.sh
make clean
./generate.sh
make all
../../scripts/./end_test.sh linux_scalability_pub_sub $1 &
./linux_scalability_pub_sub
make clean
exit
