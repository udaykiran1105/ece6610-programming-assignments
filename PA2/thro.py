#!/usr/bin/python3
import nstrace
import sys

def dup_counter(filename):
   SEND_NODE = 1
   DEST_NODE = 2
   FLOW = 0
   count = 0
   thro=0
   COUNTS = {}
   INSTR = []
   nstrace.nsopen(filename)
   for x in xrange(1000):
       INSTR.append(0)

   while not nstrace.isEOF():
       if nstrace.isEvent():
           (event, time, sendnode, dest, packetname, size, dummy, flow, dummy, dummy, seqno, dummy) = nstrace.getEvent()
           #if (event == "r" and dest == DEST_NODE and size >= 1000 and flow == FLOW):
           #print dest, "= dest"
           if (event == "r" and packetname=="tcp" and dest ==DEST_NODE):
               
               if (seqno in COUNTS):
                   nstrace.skipline()
               else:
                   COUNTS[seqno] = 1
                   thro = thro + size
                   
                   for x in xrange(0,51):
                       for y in xrange(0,10):
                            if( time>float(x)+(float(y)/10.0) and time <= float(x)+(float(y+1)/10.0) ):
                                INSTR[(x*10)+y]= INSTR[(x*10)+y]+size
                                
       else:
           nstrace.skipline()
   print "Throughput is", thro
   for x in xrange(0,51):
       for y in xrange(0,10):
           print "\n ",count," Inst throughput between time  ", float(x)+(float(y)/10.0) , "and" , float(x)+(float(y+1)/10.0),"=", INSTR[(x*10)+y]        
           count+=1
dup_counter(sys.argv[1])


