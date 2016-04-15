#!/bin/bash
min=60
endTime=$[$2*$min]

sleep $endTime
killall $1
