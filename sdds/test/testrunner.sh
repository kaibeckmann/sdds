#!/bin/bash

# Install rumprun
if [ ! -d $(pwd)/rumprun/rumprun ]; then
    cd rumprun
    ./install_rumprun.sh
    cd -
fi
export PATH="${PATH}:$(pwd)/rumprun/rumprun/rumprun/bin"

if (( $# > 0 )); then
    for BASENAME in "$@"; do
    if [[ $BASENAME == test_echo* ]]; then
        # Start echo server
        cd echo_server
        make clean >/dev/null 2>&1
        make -j8 >/dev/null 2> ../error.log
        ./run.sh >/dev/null 2>&1 &
        ECHO_PID=$!
        # Start echo client
        cd ..
        cd $BASENAME
        make clean >/dev/null 2>&1
        make -j8 >/dev/null 2> ../error.log
        if [ $? -ne 0 ]; then
            echo "$1: FAILED"
            echo ""
            echo "Some tests failed! See error.log for details."
            exit 1
        fi
        ./$BASENAME 2> ../error.log
        if [ $? -ne 0 ]; then
            echo "$1: FAILED"
            echo ""
            echo "Some tests failed! See error.log for details."
            exit 1
        fi
        make clean >/dev/null 2>&1
        if [ $? -ne 0 ]; then
            echo "FAILED"
            exit 1
        fi
        # Stop echo server
        cd ..
        cd echo_server
        killall qemu-system-x86_64 >/dev/null 2>&1
        make clean >/dev/null 2>&1
        cd ..

    else
        echo "parameter '$BASENAME' is no valid foldername"
    fi
done

else

    echo "Running sdds selftest"
    echo ""
    for test in ./* ; do
        BASENAME=$(basename "$test")
        if [ -d "$BASENAME" ]; then
            if [[ $BASENAME == test_echo* ]]; then
                # Start echo server
                cd echo_server
                make clean >/dev/null 2>&1
                make -j8 >/dev/null 2> ../error.log
                ./run.sh >/dev/null 2>&1 &
                ECHO_PID=$!
                # Start echo client
                cd ..
                cd $BASENAME
                make clean >/dev/null 2>&1
                make -j8 >/dev/null 2> ../error.log
                if [ $? -ne 0 ]; then
                    echo "$BASENAME: FAILED"
                    echo ""
                    echo "Some tests failed! See error.log for details."
                    exit 1
                fi
                ./$BASENAME 2> ../error.log
                if [ $? -ne 0 ]; then
                    echo "$BASENAME: FAILED"
                    echo ""
                    echo "Some tests failed! See error.log for details."
                    exit 1
                fi
                make clean >/dev/null 2>&1
                if [ $? -ne 0 ]; then
                    echo "FAILED"
                    exit 1
                fi
                # Stop echo server
                cd ..
                cd echo_server
                killall qemu-system-x86_64 >/dev/null 2>&1
                make clean >/dev/null 2>&1
                cd ..
            elif [[ $BASENAME == test_* ]]; then
                cd $BASENAME
                make clean >/dev/null 2>&1
                make -j8 >/dev/null 2> ../error.log
                if [ $? -ne 0 ]; then
                   echo "$BASENAME: FAILED"
                    echo ""
                    echo "Some tests failed! See error.log for details."
                    exit 1
                fi
                ./$BASENAME 2> ../error.log
                if [ $? -ne 0 ]; then
                    echo "$BASENAME: FAILED"
                    echo ""
                    echo "Some tests failed! See error.log for details."
                    exit 1
                fi
                make clean >/dev/null 2>&1
                if [ $? -ne 0 ]; then
                    echo "FAILED"
                    exit 1
                fi
                    cd ..
            fi
        fi
    done

fi #end of if script has parameters

echo ""
echo "All tests passed!"
