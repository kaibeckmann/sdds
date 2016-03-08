#!/bin/bash
cd ~/sdds/sdds/test/performance_tests/scalability/linux_scalability_pub/
echo -e "preparing pub test @$2"
./prepare_test.sh $3 pub2 $4 $5 $6 $7
make clean >/dev/null 2>&1
./generate.sh >/dev/null 2>&1
echo "building pub test @$2"
make all >/dev/null 2> ../pub_make_error.log
../../scripts/./end_test.sh linux_scalability_pub $1 &
echo "running pub test @$2"
./linux_scalability_pub >/dev/null 2> ../pub.log
echo "pub test @$2 completed"
echo "cleaning up pub test $2"
make clean >/dev/null 2>&1
rm -rf sdds.xml
echo "done @$2"
exit
