#!/bin/bash
if [ "$#" -lt 2 ]; then
    echo "usage $0 <msg_count> <msg_size>"
    exit
fi

msg_count=$1
msg_size=$2

sed s/{msg_count}/$msg_count/ template.xml | sed s/{msg_size}/$msg_size/ > sdds.xml

