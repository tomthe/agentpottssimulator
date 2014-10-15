#!/usr/bin/env python
# $Id: init_start_state.py 1613 2009-03-25 14:38:18Z lsc $
# 
# Copyright (c) 2009 STFC Rutherford Appleton Laboratory 
# Author: Lee-Shawn Chin 
# Date  : Nov 2009
#
# Description:
#    Quick hack to create start states (0.xml) needed by the ABM_EXP model
#
import re
import os
import sys
from math import pi
from random import random

outfile = "0.xml"
radius  = 2.0

# We expect 4 input arguments
if len(sys.argv) <= 2:
    print >> sys.stderr, "\nUsage: %s <width> <height> <agent_count>" % sys.argv[0]
    print >> sys.stderr, """More info:
    <width> and <height> will determine the size of simulation space in which
    agents will be randomly placed in.

    <agent_count> specifies the number of agents to initialise.
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
        <type>0</type>
    </xagent>
""" % (id, x1,y1,z,x2,y2,z,x3,y3,z,x4,y4,z,))

# End XML file and close
f.write("</states>\n")
f.close();

print "DONE"

