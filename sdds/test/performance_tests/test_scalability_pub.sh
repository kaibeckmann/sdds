#!/bin/bash
#scripts/./end_test.sh `basename $1` $2 &
cd scalability/linux_scalability_pub/
./prepare_test.sh
make clean
./generate.sh
make all
./linux_scalability_pub 
exit
