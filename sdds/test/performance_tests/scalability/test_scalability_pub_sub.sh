#!/bin/bash
cd ~/sdds/sdds/test/performance_tests/scalability/linux_scalability_pub_sub/
echo -e "preparing pub_sub test @$2"
./prepare_test.sh
make clean >/dev/null 2>&1
./generate.sh >/dev/null 2>&1
echo "building pub_sub test @$2"
make all >/dev/null 2> ../pub_sub_make_error.log
../../scripts/./end_test.sh linux_scalability_pub_sub $1 &
echo "running pub_sub test @$2"
./linux_scalability_pub_sub >/dev/null 2> ../pub_sub.log
echo "pub_sub test @$2 completed"
echo "cleaning up pub_sub test $2"
make clean >/dev/null 2>&1
echo "done @$2"
exit
