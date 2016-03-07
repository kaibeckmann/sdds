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

def plot_iterate(typ, p, ps, s, scal_eval):
	x = []
	y = []
	if typ == 0:
		nodes = p+1
	if typ == 1:
		nodes = ps+1
	if typ == 2:
		nodes = s+1
	for i in xrange(1, nodes):
		x.append(i)
		if typ == 0:
			p = i
		if typ == 1:
			ps = i
		if typ == 2:
			s = i
		y.append(scal_eval.getMsgCount_all(p,ps,s))

	plt.plot(x, y)

	x = []
	y = []
	os.chdir("eval_scalability/")
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


	os.chdir("..")
	plt.plot(x, y)

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

	plt.plot(x, y)

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

	plt.plot(x, y)

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

	plt.plot(x, y)

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

	plt.plot(x, y)

def plot_iterate_pub(p, ps, s, scal_eval):
	plot_iterate(0, p, ps, s, scal_eval)

def plot_iterate_pubSub(p, ps, s, scal_eval):
	plot_iterate(1, p, ps, s, scal_eval)

def plot_iterate_sub(p, ps, s, scal_eval):
	plot_iterate(2, p, ps, s, scal_eval)

def process_log():
	os.chdir("eval_scalability/")
	eval_file = open("scalability.eval", "w")
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
		eval_file.write(scal.toString());	
		log.close()
	eval_file.close()
	os.chdir("..")
	return scal_eval	



argc = len(sys.argv)

if argc < 5 or (sys.argv[1] != "pub" and sys.argv[1] != "pubSub" and sys.argv[1] != "sub"):
	print "usage: " + sys.argv[0] + " pub|pubSub|sub x y z [lbud]"
	print "example: "+ sys.argv[0] + " pub 4 1 1 \t\t--- iterate over pub ((1-4), 1, 1)"
	print "example: "+ sys.argv[0] + " pubSub 1 3 1 \t--- iterate over pubSub (1, (1-3), 1)"
	print "example: "+ sys.argv[0] + " sub 1 1 6 \t\t--- iterate over sub ((1, 1, (1-6))"
	quit()

typ = 0
p = int(sys.argv[2])
ps = int(sys.argv[3])
s = int(sys.argv[4])
lbud = ""
title = "Scalability "
if sys.argv[1] == "pub":
	typ = 0
	plt.xlabel('Publisher')
	title = title+"(x, %d"%ps+", %d"%s+") "
if sys.argv[1] == "pubSub":
	typ = 1 
	plt.xlabel('PubSub')
	title = title+"(%d"%p+", x, %d"%s+") "
if sys.argv[1] == "sub":
	typ = 2
	plt.xlabel('Subscriber')
	title = title+"(%d"%p+", %d"%ps+", x) "
if argc > 5 and sys.argv[5] == 'lbud':
	lbud = "with latency budget"

scal_eval = process_log()

plot_iterate(typ, p, ps, s, scal_eval)

plt.ylabel("Messages")
plt.title(title+lbud)
plt.grid(True)
plt.show()

