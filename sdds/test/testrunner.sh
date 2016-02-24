#!/bin/bash

############################### FUNCTION SECTION ##############################
function fkt_error () {
    echo "$1: FAILED"
    echo ""
    echo "Some tests failed! See error.log for details."
    if [[ $1 == test_echo* ]]; then
        echo ""
        echo "Wait for closing of emulator."
        sleep 3
        killall qemu-system-x86_64 >/dev/null 2>&1
        echo "done."
    fi
    exit 1
}

function fkt_test () {
    if [[ $1 == test_echo* ]]; then
        # Start echo server
        cd echo_server
        make clean >/dev/null 2>&1
        make -j8 >/dev/null 2> ../error.log
        ./run.sh >/dev/null 2>&1 &
        ECHO_PID=$!
        # Start echo client
        cd ..
        cd $1
        make clean >/dev/null 2>&1
        make -j8 >/dev/null 2> ../error.log
        if [ $? -ne 0 ]; then
            fkt_error $1
        fi
        ./$1 2> ../error.log
        if [ $? -ne 0 ]; then
            fkt_error $1
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
    elif [[ $1 == test_* ]]; then # test without echo server
        cd $1
        make clean >/dev/null 2>&1
        make -j8 >/dev/null 2> ../error.log
        if [ $? -ne 0 ]; then
           fkt_error $1
       fi
        ./$1 2> ../error.log
        if [ $? -ne 0 ]; then
            fkt_error $1
        fi
        make clean >/dev/null 2>&1
        if [ $? -ne 0 ]; then
            echo "FAILED"
            exit 1
        fi
            cd ..
    else
        echo "parameter '$1' is no valid foldername"
    fi
}

##################################### BEGIN OF SCRIPT##########################

# Install rumprun
if [ ! -d $(pwd)/rumprun/rumprun ]; then
    cd rumprun
    ./install_rumprun.sh
    cd -
fi
export PATH="${PATH}:$(pwd)/rumprun/rumprun/rumprun/bin"

if (( $# > 0 )); then
    echo "Running selective sdds selftest"
    echo ""
    for BASENAME in "$@"; do
        fkt_test $BASENAME
    done

else

    echo "Running full sdds selftest"
    echo ""
    for test in ./test* ; do
        BASENAME=$(basename "$test")
        if [ -d "$BASENAME" ]; then
            fkt_test $BASENAME
        fi
    done

fi

echo ""
echo "All tests passed!"
