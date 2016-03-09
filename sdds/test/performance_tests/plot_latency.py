import os, glob, sys, csv
from os import path
import numpy as np
import matplotlib.pyplot as plt

def read_files(eval_dir):
    prev_dir = os.getcwd()
    os.chdir(eval_dir)

    msg_count = 0
    logs = [] 
    #for f in glob.glob("*.log"):
    #    logs.append([])
    logs.append([])
    logs.append([])
        
    for f in glob.glob("*.log"):
        split = f.split(".log")[0].split("_")
        count = len(split)
        msg_count = int(split[count-2])
        size = int(split[count-1])
        log = open(f, "rb")
        reader = csv.reader(log)
         
        l = []
        for row in reader:
            for col in row:
                l.append(int(col))
        
        logs[0].append(size)
        logs[1].append(l)
        log.close()
    
    os.chdir(prev_dir)
    return logs, msg_count

argc = len(sys.argv)

if argc < 2:
	print "usage: " + sys.argv[0] + " <eval_dir>"
	quit()

eval_dir = sys.argv[1]

raw_log, msg_count = read_files(eval_dir)

sort_log = []
sort_size = sorted(raw_log[0])

for size in sort_size:
    for i in range(0, len(raw_log[0])):
        if size == raw_log[0][i]:
            sort_log.append(raw_log[1][i])
            break

mins = []
maxs = []
avrs = []

for log in sort_log:
    mi = min(log)
    ma = max(log)
    av = float(sum(log)) / msg_count
    mins.append(mi)
    maxs.append(ma)
    avrs.append(av)

print sort_size
print mins
print maxs
print avrs

plt.plot(sort_size, mins, '-o')
plt.plot(sort_size, maxs, '-o')
plt.plot(sort_size, avrs, '-o')
plt.legend(["min", "max", "avrg"])

title = "Latency Test: %d Messages, %d - %d Bytes" % (msg_count, sort_size[0], sort_size[len(sort_size)-1])

plt.ylabel("Latency in usec")
plt.xlabel("Message size in byte")
plt.title(title)
plt.grid(True)
plt.show()

