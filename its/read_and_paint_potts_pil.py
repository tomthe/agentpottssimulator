import Image
import ImageDraw
import xml.etree.ElementTree as ET

import re

im_width = 512
im_height = 512

sim_space_min = -4.0
sim_space_max = 5.0


def test_onefile():
	read_and_paint_one_timestep("45.xml")
	pass

def read_and_paint_one_timestep(filename):
	cells = read_data_from_one_timestep(filename)
	paint_one_timestep(cells,filename)


def paint_one_timestep(cells,filename):
	# create a canvas
	# paint every cell
	back = Image.new('RGBA', (im_width,im_height), (123,133,133,0))
	poly = Image.new('RGBA', (im_width,im_height))
	pdraw = ImageDraw.Draw(poly)

	for cell in cells:
		cell_im = convert_cell_coordinates(cell)
		print "cell: ", cell_im
		pdraw.polygon(cell_im,fill=(255,255,255,127),outline=(0,255,255,255))
		#pdraw.polygon([(128,128),(384,384),(128,384),(384,128)],
		#              fill=(255,255,255,127),outline=(255,255,255,255))
		back.paste(poly,mask=poly)
	#save and show image
	back.save(filename[:-3] + ".png")
	#back.show()


def paint_one_cell(cell,canvas):
	pass

def read_data_from_one_timestep(filename):
	tree = ET.parse(filename)
	root = tree.getroot()
	cells = []
	for cellxml in root.iter('points'):
		pointstring = cellxml.text
		cell_points = pointstring_to_positions(pointstring)
		cells.append(cell_points)
	return cells

def test_pointstring_to_positions():
	positions = pointstring_to_positions("{{1.600000, 1.100000, 0.000000}, {1.600000, 0.100000, 0.000000}, {2.500000, 0.100000, 0.000000}, {2.386227, 1.058769, 0.000000}}")
	#print positions

def pointstring_to_positions(cell_string):
	#what would be a nice way?
	#i will do it dirty...

	cell_string = cell_string.replace("{","")
	cell_string = cell_string.replace("}","")
	cells = cell_string.split(",")
	p0=[float(cells[0]),float(cells[1])]
	p1=[float(cells[2]),float(cells[3])]
	p2=[float(cells[4]),float(cells[5])]
	p3=[float(cells[6]),float(cells[7])]

	corners = [p0,p1,p2,p3]
	#print "corners: ",corners
	return corners


def sim_coord_2_paint_coord((x,y)):
	x = float(x - sim_space_min) / (sim_space_max - sim_space_min) * im_width
	y = float(y - sim_space_min) / (sim_space_max - sim_space_min) * im_height
	return (x,y)

def convert_cell_coordinates(cell):
	paint_coords = []
	for corner in cell:
		paint_coords.append(sim_coord_2_paint_coord(corner))
	return paint_coords

def read_and_paint_many_timesteps(start,stop):

	for i in xrange(start,stop):
		try:
			filename = str(i) + ".xml"
			read_and_paint_one_timestep(filename)
		except:
			print " no xml-file: ", filename
	pass




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

read_and_paint_many_timesteps(0,2500)