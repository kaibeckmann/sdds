#!/bin/bash

echo "Running sdds selftest"
echo ""
for test in ./* ; do
    BASENAME=$(basename "$test")
    if [ -d "$test" -a "$BASENAME" != "topics" ]; then
        cd $BASENAME
        make clean >/dev/null 2>&1
        make >/dev/null 2> ../error.log
        if [ $? -ne 0 ]; then
            echo "$BASENAME: FAILED"
            echo ""
            echo "Some tests failed! See error.log for details."
            exit 1
        fi
        ./$BASENAME
        make clean >/dev/null 2>&1
        if [ $? -ne 0 ]; then
            echo "FAILED"
            exit 1
        fi
        cd ..
    fi
done
echo ""
echo "All tests passed!"
