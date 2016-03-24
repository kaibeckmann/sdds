#!/usr/bin/python
# vim: noet

import os, glob, sys
from os import path
import numpy as np
import matplotlib.pyplot as plt

class ScalabilitySample:
	def __init__(self, typ, host, pub, pubSub, sub, p_all, p_id, p_pub, p_sub, p_data, dur):
		self.typ = typ
		self.host = host
		self.pub = int(pub)
		self.pubSub = int(pubSub)
		self.sub = int(sub)
		self.p_all = p_all
		self.p_id = p_id
		self.p_pub = p_pub
		self.p_sub = p_sub
		self.p_data = p_data
		self.dur = dur
		
	def toString(self):
		return self.typ+"\t"+self.host+" (%d,"%self.pub+"%d,"%self.pubSub+"%d)\t"%self.sub+"D=%d\t"%self.p_data+"I=%d\t"%self.p_id+"P=%d\t"%self.p_pub+"S=%d\t"%self.p_sub+"all=%d\n"%self.p_all


class ScalabilityEval:
	def __init__(self):
		self.samples = []

	def add(self, sample):
		self.samples.append(sample)

	def getSamples_all(self, p, ps, s):
		val = []
		for sample in self.samples:
			if p == sample.pub and ps == sample.pubSub and s == sample.sub:
				val.append(sample.p_all)
		return val

	def getSamples_data(self, p, ps, s):
		val = []
		for sample in self.samples:
			if p == sample.pub and ps == sample.pubSub and s == sample.sub:
				val.append(sample.p_data)
		return val

	def getSamples_id(self, p, ps, s):
		val = []
		for sample in self.samples:
			if p == sample.pub and ps == sample.pubSub and s == sample.sub:
				val.append(sample.p_id)
		return val

	def getSamples_pub(self, p, ps, s):
		val = []
		for sample in self.samples:
			if p == sample.pub and ps == sample.pubSub and s == sample.sub:
				val.append(sample.p_pub)
		return val

	def getSamples_sub(self, p, ps, s):
		val = []
		for sample in self.samples:
			if p == sample.pub and ps == sample.pubSub and s == sample.sub:
				val.append(sample.p_sub)
		return val

	def getMsgCount_all(self, p, ps, s):
		count = 0
		for val in self.getSamples_all(p, ps, s):
			count += val
		return count

	def getMsgCount_data(self, p, ps, s):
		count = 0
		for val in self.getSamples_data(p, ps, s):
			count += val
		return count

	def getMsgCount_id(self, p, ps, s):
		count = 0
		for val in self.getSamples_id(p, ps, s):
			count += val
		return count

	def getMsgCount_pub(self, p, ps, s):
		count = 0
		for val in self.getSamples_pub(p, ps, s):
			count += val
		return count

	def getMsgCount_sub(self, p, ps, s):
		count = 0
		for val in self.getSamples_sub(p, ps, s):
			count += val
		return count

def plot_fix(p_fix, ps_fix, s_fix, scal_eval):
	eval_line = "Scalability "+scal_eval.samples[0].dur+" min\n\n\t"
	prev_dir = os.getcwd()
	os.chdir(eval_dir)
	eval_file = open("scalability.eval", "w")

	x = []
	for i in range(0, len(p_fix)):
		p = p_fix[i]
		ps = ps_fix[i]
		s = s_fix[i]
		eval_line = eval_line+"(%d,"%p+"%d,"%ps+"%d)\t"%s
		x.append(max(p,s))

	#print eval_line
	eval_file.write(eval_line+"\n")

	y = []
	for i in range(0, len(p_fix)):
		p = p_fix[i]
		ps = ps_fix[i]
		s = s_fix[i]
		y.append(scal_eval.getMsgCount_all(p,ps,s))

	plot_all = plt.plot(x, y, '-o')
	eval_line = "all\t"+str(y).strip('[]').replace(",", "\t")
	#print eval_line
	eval_file.write(eval_line+"\n")

	y = []
	for i in range(0, len(p_fix)):
		p = p_fix[i]
		ps = ps_fix[i]
		s = s_fix[i]
		for f in glob.glob("*.wslog"):
			split = f.split(".wslog")[0].split("_")
			count = len(split)
			sub = int(split[count-1])
			pubSub = int(split[count-2])
			pub = int(split[count-3])
			if pub == p and pubSub == ps and sub == s:
				y.append(sum(1 for line in open(f)))

	while len(x) > len(y):
		y.append(0)

	os.chdir(prev_dir)
	eval_line = "UDP\t"+str(y).strip('[]').replace(",", "\t")
	#print eval_line
	eval_file.write(eval_line+"\n")
	plot_ws = plt.plot(x, y, '->')

	y = []
	for i in range(0, len(p_fix)):
		p = p_fix[i]
		ps = ps_fix[i]
		s = s_fix[i]
		y.append(scal_eval.getMsgCount_id(p,ps,s))
		
	plot_id = plt.plot(x, y, '-o')
	eval_line = "id\t"+str(y).strip('[]').replace(",", "\t")
	#print eval_line
	eval_file.write(eval_line+"\n")

	y = []
	for i in range(0, len(p_fix)):
		p = p_fix[i]
		ps = ps_fix[i]
		s = s_fix[i]
		y.append(scal_eval.getMsgCount_data(p,ps,s))
		
	plot_data = plt.plot(x, y, '-o')
	eval_line = "data\t"+str(y).strip('[]').replace(",", "\t")
	#print eval_line
	eval_file.write(eval_line+"\n")

	y = []
	for i in range(0, len(p_fix)):
		p = p_fix[i]
		ps = ps_fix[i]
		s = s_fix[i]
		y.append(scal_eval.getMsgCount_pub(p,ps,s))
		
	plot_pub = plt.plot(x, y, '-o')
	eval_line = "pub\t"+str(y).strip('[]').replace(",", "\t")
	#print eval_line
	eval_file.write(eval_line+"\n")

	y = []
	for i in range(0, len(p_fix)):
		p = p_fix[i]
		ps = ps_fix[i]
		s = s_fix[i]
		y.append(scal_eval.getMsgCount_sub(p,ps,s))
		
	plot_sub = plt.plot(x, y, '-o')
	eval_line = "sub\t"+str(y).strip('[]').replace(",", "\t")
	#print eval_line
	eval_file.write(eval_line+"\n")
	plt.legend(["all", "UDP", "id", "data", "pub", "sub"])


def plot_iterate(typ, p, ps, s, scal_eval):
	x = []
	y = []
	if typ >= 3:
		plot_fix(p, ps, s, scal_eval)
		return	
	if typ == 0:
		nodes = p+1
		eval_line = "Scalability "+scal_eval.samples[0].dur+" min (x, %d, "%ps+"%d)\n"%s
	if typ == 1:
		nodes = ps+1
		eval_line = "Scalability "+scal_eval.samples[0].dur+" min (%d, x, "%p+"%d)\n"%s
	if typ == 2:
		nodes = s+1
		eval_line = "Scalability "+scal_eval.samples[0].dur+" min (%d, "%p+"%d, x)\n"%ps

	prev_dir = os.getcwd()
	os.chdir(eval_dir)
	eval_file = open("scalability.eval", "w")

	#print eval_line
	eval_file.write(eval_line+"\n")
	for i in xrange(1, nodes):
		x.append(i)
		if typ == 0:
			p = i
		if typ == 1:
			ps = i
		if typ == 2:
			s = i
		y.append(scal_eval.getMsgCount_all(p,ps,s))

	plot_all = plt.plot(x, y, '-o')
	eval_line =  "\t"+str(x).strip('[]').replace(",", "\t")
	#print eval_line
	eval_file.write(eval_line+"\n")
	eval_line = "all\t"+str(y).strip('[]').replace(",", "\t")
	#print eval_line
	eval_file.write(eval_line+"\n")

	x = []
	y = []
	for i in xrange(1, nodes):
		x.append(i)
		if typ == 0:
			p = i
		if typ == 1:
			ps = i
		if typ == 2:
			s = i
		for f in glob.glob("*.wslog"):
			split = f.split(".wslog")[0].split("_")
			count = len(split)
			sub = int(split[count-1])
			pubSub = int(split[count-2])
			pub = int(split[count-3])
			if pub == p and pubSub == ps and sub == s:
				y.append(sum(1 for line in open(f)))
		if len(x) > len(y):
			y.append(0)


	os.chdir(prev_dir)
	plot_ws = plt.plot(x, y, '->')
	eval_line = "UDP\t"+str(y).strip('[]').replace(",", "\t")
	#print eval_line
	eval_file.write(eval_line+"\n")

	x = []
	y = []
	for i in xrange(1, nodes):
		x.append(i)
		if typ == 0:
			p = i
		if typ == 1:
			ps = i
		if typ == 2:
			s = i
		y.append(scal_eval.getMsgCount_id(p,ps,s))

	plot_id = plt.plot(x, y, '-o')
	eval_line = "id\t"+str(y).strip('[]').replace(",", "\t")
	#print eval_line
	eval_file.write(eval_line+"\n")

	x = []
	y = []
	for i in xrange(1, nodes):
		x.append(i)
		if typ == 0:
			p = i
		if typ == 1:
			ps = i
		if typ == 2:
			s = i
		y.append(scal_eval.getMsgCount_data(p,ps,s))

	plot_data = plt.plot(x, y, '-o')
	eval_line = "data\t"+str(y).strip('[]').replace(",", "\t")
	#print eval_line
	eval_file.write(eval_line+"\n")

	x = []
	y = []
	for i in xrange(1, nodes):
		x.append(i)
		if typ == 0:
			p = i
		if typ == 1:
			ps = i
		if typ == 2:
			s = i
		y.append(scal_eval.getMsgCount_pub(p,ps,s))

	plot_pub = plt.plot(x, y, '-o')
	eval_line = "pub\t"+str(y).strip('[]').replace(",", "\t")
	#print eval_line
	eval_file.write(eval_line+"\n")

	x = []
	y = []
	for i in xrange(1, nodes):
		x.append(i)
		if typ == 0:
			p = i
		if typ == 1:
			ps = i
		if typ == 2:
			s = i
		y.append(scal_eval.getMsgCount_sub(p,ps,s))

	plot_sub = plt.plot(x, y, '-o')
	eval_line = "sub\t"+str(y).strip('[]').replace(",", "\t")
	#print eval_line
	eval_file.write(eval_line+"\n")
	plt.legend(["all", "UDP", "id", "data", "pub", "sub"])

def plot_iterate_pub(p, ps, s, scal_eval):
	plot_iterate(0, p, ps, s, scal_eval)

def plot_iterate_pubSub(p, ps, s, scal_eval):
	plot_iterate(1, p, ps, s, scal_eval)

def plot_iterate_sub(p, ps, s, scal_eval):
	plot_iterate(2, p, ps, s, scal_eval)

def process_log():
	prev_dir = os.getcwd()
	os.chdir(eval_dir)
	scal_eval = ScalabilityEval()

	for f in glob.glob("*.log"):
		split = f.split(".log")[0].split("_")
		count = len(split)
		sub = split[count-1]
		pubSub = split[count-2]
		pub = split[count-3]
		host = split[count-4]
		typ = split[count-5]
		dur = split[count-6]
		log = open(f, 'r')
		log_str = log.read()
		p_all = (len(log_str.split("D"))-1)
		p_id = (len(log_str.split("I"))-1)
		p_pub = (len(log_str.split("P"))-1)
		p_sub = (len(log_str.split("S"))-1)
		p_data = p_all - p_id - p_pub - p_sub
		scal = ScalabilitySample(typ, host, pub, pubSub, sub, p_all, p_id, p_pub, p_sub, p_data, dur)
		scal_eval.add(scal)
		log.close()

	os.chdir(prev_dir)
	return scal_eval	



argc = len(sys.argv)

if argc < 6 or (sys.argv[2] != "pub" and sys.argv[2] != "pubSub" and sys.argv[2] != "sub" and sys.argv[2] != "fix"):
	print "usage: " + sys.argv[0] + " <eval_dir> <pub|pubSub|sub|fix> <x> <y> <z> [lbud]"
	print "example: "+ sys.argv[0] + " eval_scalability pub 4 1 1 \t\t--- iterate over pub ((1-4), 1, 1)"
	print "example: "+ sys.argv[0] + " eval_scalability pubSub 1 3 1 \t--- iterate over pubSub (1, (1-3), 1)"
	print "example: "+ sys.argv[0] + " eval_scalability sub 1 1 6 \t\t--- iterate over sub ((1, 1, (1-6))"
	quit()

eval_dir = sys.argv[1]

scal_eval = process_log()

typ = 3
p = int(sys.argv[3])
ps = int(sys.argv[4])
s = int(sys.argv[5])
lbud = ""
title = "Scalability "+scal_eval.samples[0].dur+" min "
if sys.argv[2] == "pub":
	typ = 0
	plt.xlabel('Publisher')
	title = title+"(x, %d"%ps+", %d"%s+") "
if sys.argv[2] == "pubSub":
	typ = 1 
	plt.xlabel('PubSub')
	title = title+"(%d"%p+", x, %d"%s+") "
if sys.argv[2] == "sub":
	typ = 2
	plt.xlabel('Subscriber')
	title = title+"(%d"%p+", %d"%ps+", x) "
if sys.argv[2] == "fix":
	typ = 3
	plt.xlabel('nodes')
if argc > 6 and sys.argv[6] == 'lbud':
	lbud = "with latency budget"

if typ == 3:
	p_fix = []
	ps_fix = []
	s_fix = []
	for i in range(3,argc, 3):
		if i+2 >= argc:
			break;
		p = int(sys.argv[i])
		ps = int(sys.argv[i+1])
		s = int(sys.argv[i+2])
		title = title+"(%d"%p+",%d"%ps+",%d) "%s
		p_fix.append(p)
		ps_fix.append(ps)	
		s_fix.append(s)
	plot_iterate(typ, p_fix, ps_fix, s_fix, scal_eval)
else:
	plot_iterate(typ, p, ps, s, scal_eval)

plt.ylabel("Messages")
plt.title(title+lbud)
plt.grid(True)
plt.show()

