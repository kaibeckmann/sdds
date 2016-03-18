#!/usr/bin/python
import csv
import numpy as np
import sys

name = 'Bus.csv'

if len(sys.argv) == 2:
    name = str(sys.argv[1])

time_dict = {}

time = 0;
samples = 0;

with open(name, 'rb') as csvfile:
    bistScopeReader = csv.DictReader(csvfile, delimiter=',', quoting=csv.QUOTE_NONE)
    for row in bistScopeReader:
        if row['Bus'] == '0' and row['Time'] != '5':
            time += int(row['Time'])
            samples += 1

avr_time = time / samples
print "%d ns"%avr_time 
