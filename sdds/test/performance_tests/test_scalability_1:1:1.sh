#!/bin/bash
pub=(
	pi01
    )

pub_sub=(
		pi03
	)

sub=(
	pi04
    )

for p in "${pub[@]}"
do
	ssh $p -l pi <<'ENDSSH'
	cd sdds/sdds/test/performance_tests/scalability
	./test_scalability_pub.sh $1  &
ENDSSH
done

for p in "${pub_sub[@]}"
do
	ssh $p -l pi <<'ENDSSH'
	cd sdds/sdds/test/performance_tests/scalability
	./test_scalability_pub_sub.sh $1 &
ENDSSH
done

for p in "${sub[@]}"
do
	ssh $p -l pi <<'ENDSSH'
	cd sdds/sdds/test/performance_tests/scalability
	./test_scalability_sub.sh $1 &
ENDSSH
done
