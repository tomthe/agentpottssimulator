import Image
import ImageDraw
import xml.etree.ElementTree as ET

import re

im_width = 512
im_height = 512

sim_space_min_x = -0.0
sim_space_min_y = -0.0
sim_space_max_x = 3.0
sim_space_max_y = 3.0


def set_sim_space(cells):
	#print "---all cells", cells
	minx=cells[0][0][0]
	maxx=cells[0][0][0]
	miny=cells[0][0][1]
	maxy=cells[0][0][1]
	for cell in cells:
		#minx = min(cell)
		#print "cell: ", cell, "---", minx
		for coord in cell:
			if coord[0]<minx:
				minx = coord[0]
			elif coord[0]>maxx:
				maxx = coord[0]
			if coord[1]<miny:
				miny = coord[1]
			elif coord[1]>maxy:
				maxy = coord[1]
	global sim_space_min_x
	sim_space_min_x = minx
	global sim_space_min_y
	sim_space_min_y = miny
	global sim_space_max_x
	sim_space_max_x = maxx
	global sim_space_max_y
	sim_space_max_y = maxy



def test_onefile():
	read_and_paint_one_timestep("45.xml")
	pass

def read_and_paint_one_timestep(filename):
	cells, cell_types, signals_pos,types = read_data_from_one_timestep(filename)
	#set_sim_space(cells)
	paint_one_timestep(cells, cell_types, signals_pos,filename)

def get_color_from_cell_type(cell_type):
	if cell_type==0:
		color=(180,120,100)
	elif cell_type==1:
		color=(115,165,125)
	elif cell_type==2:
		color=(180,100,125)
	else:
		color=(255,255,255)
	return color


def paint_one_timestep(cells,cell_types,signals_pos,filename):
	# create a canvas
	# paint every cell
	back = Image.new('RGBA', (im_width,im_height), (123,133,133,0))
	#poly = Image.new('RGBA', (im_width,im_height))
	pdraw = ImageDraw.Draw(back)

	#draw a black background:
	pdraw.rectangle([(0,0),(im_width,im_height)],fill=(12,7,0))
	#draw a "reference"-rectangle:
	print sim_coord_2_paint_coord((0,0)),sim_coord_2_paint_coord((1.0,1.0))
	pdraw.rectangle([sim_coord_2_paint_coord((0,0)),sim_coord_2_paint_coord((1.0,1.0))],fill=(180,180,180))
	i=0
	for cell in cells:
		cell_im = convert_cell_coordinates(cell)
		#print "cell: ", cell_im
		color = get_color_from_cell_type(cell_types[i])
		pdraw.polygon(cell_im,fill=color,outline=(0,155,155,155))
		#pdraw.polygon([(128,128),(384,384),(128,384),(384,128)],
		#              fill=(255,255,255,127),outline=(255,255,255,255))
		#back.paste(poly,mask=poly)
		i+=1
	for signal in signals_pos:
		x,y = sim_coord_2_paint_coord(signal)
		r = 2
		pdraw.ellipse((x-r, y-r, x+r, y+r), fill=(211,211,255))

	pdraw.rectangle([sim_coord_2_paint_coord((0,0)),sim_coord_2_paint_coord((1.0,1.0))],fill=(180,180,180))
	#save and show image
	back.save(filename[:-3] + ".png")
	#back.show()


def paint_one_cell(cell,canvas):
	pass

def read_data_from_one_timestep(filename):
	tree = ET.parse(filename)
	root = tree.getroot()
	cells = []
	cell_types = []
	xlist=[]
	ylist=[]
	types=[0,0,0,0,0,0]
	for cellxml in root.iter('corners'):
		pointstring = cellxml.text
		cell_points = pointstring_to_positions(pointstring)
		cells.append(cell_points)
	for cellxml in root.iter('type'):
		cell_types.append(int(cellxml.text))
		if cellxml.text=='0':
			types[0] += 1
		elif cellxml.text=='1':
			types[1] += 1
		elif cellxml.text=='2':
			types[2] += 1
		elif cellxml.text=='3':
			types[3] += 1
	for cellxml in root.iter('x'):
		xlist.append(float(cellxml.text))
	for cellxml in root.iter('y'):
		ylist.append(float(cellxml.text))
	#print "inside,,,,, types: ", types
	signals_pos = zip(xlist,ylist)

	return cells, cell_types, signals_pos,types

def test_pointstring_to_positions():
	positions = pointstring_to_positions("{{1.600000, 1.100000, 0.000000}, {1.600000, 0.100000, 0.000000}, {2.500000, 0.100000, 0.000000}, {2.386227, 1.058769, 0.000000}}")
	#print positions

def pointstring_to_positions(cell_string):
	#what would be a nice way?
	#i will do it dirty...

	cell_string = cell_string.replace("{","")
	cell_string = cell_string.replace("}","")
	cells = cell_string.split(",")
	corners = []
	for i in xrange(0,len(cells),2):
		if(float(cells[i])!=0 and float(cells[i+1])!=0):
			corners.append([float(cells[i]),float(cells[i+1])])

	#print "corners: ",corners, ";  len(cells): ",len(cells),len(cells)/2
	return corners


def sim_coord_2_paint_coord((x,y)):
	x = float(x - sim_space_min_x) / (sim_space_max_x - sim_space_min_x) * im_width
	y = float(y - sim_space_min_y) / (sim_space_max_y - sim_space_min_y) * im_height
	return (x,y)

def convert_cell_coordinates(cell):
	paint_coords = []
	for corner in cell:
		paint_coords.append(sim_coord_2_paint_coord(corner))
	return paint_coords

def read_and_paint_many_timesteps(start,stop,step):
	#filename = str(start) + ".xml"
	#cells = read_data_from_one_timestep(filename)
	#set_sim_space(cells)
	types_over_time=[]
	for i in xrange(start,stop,step):
		try:
			filename = str(i) + ".xml"
			cells,cell_types,signals_pos,types = read_data_from_one_timestep(filename)
			#print "types: ", types
			types_over_time.append(types)
			set_sim_space(cells)
			read_and_paint_one_timestep(filename)
			print "painted file: ", filename
		except Exception, e:
			print " no xml-file: ", filename, str(e)

	plot_types_over_time(types_over_time)

def plot_types_over_time(types_over_time):
	import matplotlib.pyplot as plt
	#types_over_time: [[5,2,0,0],[5,3,0,0],[...]..]
	#needed: x1: [5,5,...] x2
	lenn = len(types_over_time)
	#print "types_over time: ", types_over_time,lenn
	types = zip(*types_over_time)
	#print "types: ", types

	x = range(lenn)
	with plt.xkcd():
		fig, axes = plt.subplots()
		axes.plot(x,types[0], 'r', label="stem-cells")
		axes.plot(x,types[1], 'b', label="differentiated")
		axes.plot(x,types[2], 'y')
		axes.set_xlabel('time step')
		axes.set_ylabel('number of cells')
		axes.set_title('cell_types over time');
		axes.legend(loc=0)

		fig.savefig("types.png",dpi=200)
		print "show..."
		#plt.show()






def just_code():
	read_data_from_xml_file(filename)

	back = Image.new('RGBA', (im_width,im_height), (255,0,0,0))
	poly = Image.new('RGBA', (im_width,im_height))
	pdraw = ImageDraw.Draw(poly)
	pdraw.polygon([(128,128),(384,384),(128,384),(384,128)],
	              fill=(255,255,255,127),outline=(255,255,255,255))
	back.paste(poly,mask=poly)
	back.show()



#test_pointstring_to_positions()
#test_draw()
#test_onefile()
import sys
start, stop, step  = map(int, sys.argv[1:])
read_and_paint_many_timesteps(start,stop,step)
