# python routines for processing tracefiles.

# interface functions:
# nsopen(filename)
# isEvent(): Boolean for is the line just read in a 12-item trace line
# isVar(): the other option
# isEOF(): no more input
# getEvent(): returns tuple of 12 vars of the appropriate types, then gets new line
# getVar(): returns tuple of 7 vars of the appropriate types, then gets new line

# skipline(): reads in the next line

import sys
import re

theLine = None
theFile = None
splitLine = None
isOpen = False
linenum = 0

# regular expressions can be used to check for specific trace-line formats, but they are slow, and are disabled by default

numre = r"-?[0-9]+"
floatre = numre + r"(\.[0-9]+)?"
dotpairre = numre + r"\." + numre
stringre = r"\S+"
space = r'\s+'

event_re = r"\A[rd+-]" + space + floatre + space + numre + space + numre + space + stringre + space + numre + space + r"\S{7}" + space + numre + space +  dotpairre + space + dotpairre + space + numre + space + numre + "$"

var_re   = r"\A" + floatre + space + numre + space + numre + space + numre + space + numre + space + stringre + space + floatre + "\s*$"

CHECK_RE = True

def nsopen(filename):
	global theFile, isOpen
	# print ("opening file ", filename)
	# print ("version is ", sys.version_info[0])
	try:
		theFile = open(filename, 'r')	# throws exception on failure
	except FileNotFoundError:
		print("file not found:", filename)
		exit(0)
	isOpen = True	
	getline()
	# theFile = open(filename, "r", encoding = "utf-8")	# throws exception on failure

def getline():
	global theLine, theFile, splitLine, isOpen, linenum
	if (not isOpen): raise Exception("no file open!")
	if theLine == "": return	# readline returns "" only at EOF
	theLine = theFile.readline()
	linenum += 1
	if theLine == "": return		# is this needed?
	splitLine = theLine.split()

def skipline():
	getline()

def isEOF():
	global theLine
	return theLine == ""

def isEvent():
	global splitLine, theLine, linenum, CHECK_RE
	if CHECK_RE and len(splitLine) == 12:
		if re.match(event_re, theLine): return True
		else:
			return False
			raise Exception("event line " + str(linenum) + " does not match regular expression: \"" + theLine + '"')
	return len(splitLine) == 12

def isVar():
	global splitLine, theLine, linenum, CHECK_RE
	if CHECK_RE and len(splitLine) == 7:
		if re.match(var_re, theLine): return True
		else:
			return False
			raise Exception("vartrace line " + str(linenum) + " does not match regular expression: \"" + theLine + '"')
	return len(splitLine) == 7

# action:str, time:float, source_node, dest_node, proto:str, size, flags:str, 
def getEvent():
	global splitLine
	tuple = (
		splitLine[0],			# "r", "d", "+", "-"
		float(splitLine[1]),		# time
		int(splitLine[2]),		# sending node
		int(splitLine[3]),		# dest node
		splitLine[4],			# protocol
		int(splitLine[5]),		# size
		splitLine[6],			# flags
		int(splitLine[7]),		# flow ID
		pair(splitLine[8]),		# source (node flowid)
		pair(splitLine[9]),		# dest (node flowid)
		int(splitLine[10]),		# seq #
		int(splitLine[11])		# packet ID
		)
	getline()
	return tuple
	
# pair() takes a string of the form "n.m" and converts it to a tuple (n m)
def pair(str):
	list = str.split(".")
	return (int(list[0]), int(list[1]))

# time, source_node, source flowid, dest_node, dest_flowid, varname, value(float)
# double, int, int, int, int, string, double
def getVar():
	global splitLine
	tuple = (
		float(splitLine[0]),		# time
		int(splitLine[1]),		# source node
		int(splitLine[2]),		# source flowid
		int(splitLine[3]),		# dest node
		int(splitLine[4]),		# dest flowid
		splitLine[5],			# name of traced var
		float(splitLine[6])		# value
		)
	getline()
	return tuple
	

	

