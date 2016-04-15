#!/bin/bash
if [ "$#" -lt 2 ]; then
    echo "usage $0 <msg_size> <duration (min)>"
    exit
fi

msg_size=$1
dur=$2

sed s/{duration}/$dur/ template.xml | sed s/{msg_size}/$msg_size/ > sdds.xml
