#!/bin/bash
cd ~/sdds/sdds/test/performance_tests/scalability/linux_scalability_sub/
echo -e "preparing sub test @$2"
./prepare_test.sh $3 $4 $5 $6
make clean >/dev/null 2>&1
./generate.sh >/dev/null 2>&1
echo "building sub test @$2"
make all >/dev/null 2> ../sub_make_error.log
../../scripts/./end_test.sh linux_scalability_sub $1 &
echo "running sub test @$2"
./linux_scalability_sub >/dev/null 2> ../sub.log
echo "sub test @$2 completed"
echo "cleaning up sub test $2"
make clean >/dev/null 2>&1
echo "done @$2"
exit
