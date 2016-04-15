#!/usr/bin/python

import os, glob, sys, csv
from os import path
import numpy as np
import matplotlib.pyplot as plt

def read_files(eval_dir):
    prev_dir = os.getcwd()
    os.chdir(eval_dir)
    eval_file = open("throughput.eval", "w")

    msg_count = 0
    logs = [] 
    logs.append([])
    logs.append([])
    logs.append([])
        
    for f in glob.glob("*.log"):
        split = f.split(".log")[0].split("_")
        count = len(split)
        duration = int(split[count-2])
        size = int(split[count-1])
        log = open(f, "rb")
        reader = csv.reader(log)
         
        row = reader.next()
        row = reader.next()
        
        logs[0].append(size)
        logs[1].append(int(row[0]))
        logs[2].append(float(row[1]))
        log.close()
    
    os.chdir(prev_dir)
    return logs, duration, eval_file

argc = len(sys.argv)

if argc < 2:
	print "usage: " + sys.argv[0] + " <eval_dir>"
	quit()

eval_dir = sys.argv[1]

raw_log, duration, eval_file = read_files(eval_dir)

sort_log = []
sort_log.append([])
sort_log.append([])
sort_log.append([])
sort_size = sorted(raw_log[0])

for size in sort_size:
    for i in range(0, len(raw_log[0])):
        if size == raw_log[0][i]:
            sort_log[0].append(raw_log[0][i])
            sort_log[1].append(raw_log[1][i])
            sort_log[2].append(raw_log[2][i])
            break

eval_line = "size  \t"+str(sort_log[0]).strip('[]').replace(",", "\t\t")
eval_file.write(eval_line+"\n")
print eval_line

#eval_line = "Byte  \t"+str(sort_log[1]).strip('[]').replace(",", "\t\t")
#eval_file.write(eval_line+"\n")
#print eval_line

eval_line = "Mbit/s\t"+str(sort_log[2]).strip('[]').replace(",", "\t\t")
eval_file.write(eval_line+"\n")
print eval_line

#plt.plot(sort_log[0], sort_log[1], '-o')
plt.plot(sort_log[0], sort_log[2], '-o')
#plt.legend(["Mbit/s"])

title = "Throughput Test: %d min, up to %d Bytes" % (duration, sort_log[0][len(sort_log[0])-1])

plt.ylabel("Throughput in Mbit/s")
plt.xlabel("Payload Data Size (Bytes)")
plt.xscale('log', basex=2)
plt.title(title)
plt.grid(True)
plt.show()

