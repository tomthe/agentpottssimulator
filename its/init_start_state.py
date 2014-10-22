#!/usr/bin/env python
#
# Description:
#    Quick hack to create start states (0.xml) needed by the cellpotts abm
#	input: number of agents, number of agents per column

import re
import os
import sys
from math import pi
from random import random

outfile = "0.xml"
radius  = 2.0

# We expect 4 input arguments
if len(sys.argv) <= 2:
    print >> sys.stderr, "\nUsage: %s <agent_count> <n_columns>" % sys.argv[0]
    print >> sys.stderr, """ pleas add 2 integer numbers as arguments.
    More info:
    input: <agent_count> number of agents, <n_columns> number of agents per column
    """ 
    sys.exit(1)


acount, ida  = map(int, sys.argv[1:])


if acount < 2:
    print >> sys.stderr, "Error: There must be at least 2 agents"
    sys.exit(1)
# Open file and write preamble
print "Writing to file %s ... " % outfile,
f = open(outfile, "w")
f.write("<states>\n   <itno>0</itno>\n")
z=0.0
# write out agent data
for id in xrange(0,acount):
    celltype= id%2
    ida=id % 4
    x1 = x2 = 0.5 + ida * 1.1
    x3 = x4 = 1.5 + ida * 1.0
    y1 = y4 = 1.1 + id / 4
    y2 = y3 = 0.1 + id / 4
    # write agent values to file
    f.write("""
    <xagent>
        <name>cell2d4</name>
        <id>%d</id>
        <points>{{%.2f,%.2f,%.2f},{%.2f,%.2f,%.2f},{%.2f,%.2f,%.2f},{%.2f,%.2f,%.2f}}</points>
        <type>%d</type>
    </xagent>
""" % (id, x1,y1,z,x2,y2,z,x3,y3,z,x4,y4,z,celltype))

# End XML file and close
f.write("</states>\n")
f.close();

print "DONE"

