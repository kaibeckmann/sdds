#!/bin/bash
if [ "$#" -lt 2 ]; then
    echo "usage $0 <msg_size> <max_mbit>"
    exit
fi

msg_size=$1
max_mbit=$2

sed s/{max_mbit}/$max_mbit/ template.xml | sed s/{msg_size}/$msg_size/ > sdds.xml
