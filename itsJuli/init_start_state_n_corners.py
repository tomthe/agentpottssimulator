#!/usr/bin/env python
#
# Description:
#    Quick hack to create start states (0.xml) needed by the cellpotts abm
#	input: number of agents, number of agents per column

import re
import os
import sys
from math import pi, sin, cos
from random import random, uniform

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


acount, col, n_corners, ncelltypes  = map(int, sys.argv[1:])
print "input: ", acount, col, ncelltypes



if acount < 2:
    print >> sys.stderr, "Error: There must be at least 2 agents"
    sys.exit(1)
# Open file and write preamble
print "Writing to file %s ... " % outfile

do_stiff_edge=False
n_corners = 12
r = 0.60
spacing = r * 4.0
nix, niy = 2,2

f = open(outfile, "w")
f.write("<states>\n   <itno>0</itno>\n")
id = 0

for ix in xrange(nix):
    for iy in xrange(niy):
        id += 1
        celltype = uniform(0, ncelltypes)
        if do_stiff_edge and (ix==0 or ix==nix-1 or iy==0 or iy==niy-1):
            celltype = 2
            r = 1.4
        else:
            r=1.0
        x = ix * spacing
        y = iy * spacing
        if ix%2 == 0:
            y += spacing / 5
        # write agent values to file
        f.write("""
            <xagent>
            <name>cell2d4</name>
            <id>%d</id>
            <corners>{""" %(id))
        for icorner in xrange(n_corners):
            radianpos = 2 * pi / n_corners * icorner
            xp = r * cos(radianpos) + x
            yp = r * sin(radianpos) + y
            f.write("%.2f,%.2f" %(xp,yp))
            if icorner != (n_corners-1):
                f.write(",")
        f.write("""
            }</corners>
            <type>%d</type>
            <x>%.2f</x>
            <y>%.2f</y>
            <age>0</age>
            </xagent>
            """ % (celltype,x,y))

# End XML file and close
f.write("</states>\n")
f.close();
