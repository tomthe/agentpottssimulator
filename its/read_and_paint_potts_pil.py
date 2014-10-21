import Image
import ImageDraw
import xml.etree.ElementTree as ET

import re

i_width = 512
i_height = 512




def test_onefile():

	pass

def paint_one_timestep(cells):
	# create a canvas
	# paint every cell
	#
	pass

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
	print positions

def pointstring_to_positions(cell_string):
	#what would be a nice way?
	#i will do it dirty...

	cell_string = cell_string.replace("{","")
	cell_string = cell_string.replace("}","")
	cells = cell_string.split(",")
	p0=[float(cells[0]),float(cells[1])]
	p1=[float(cells[3]),float(cells[4])]
	p2=[float(cells[6]),float(cells[7])]
	p3=[float(cells[8]),float(cells[9])]

	corners = [p0,p1,p2,p3]
	return corners


def sim_coord_2_paint_coord(x,y):
	pass

def read_and_paint_many_timesteps(start,stop):
	pass




def just_code():
	read_data_from_xml_file(filename)

	back = Image.new('RGBA', (im_width,im_height), (255,0,0,0))
	poly = Image.new('RGBA', (512,512))
	pdraw = ImageDraw.Draw(poly)
	pdraw.polygon([(128,128),(384,384),(128,384),(384,128)],
	              fill=(255,255,255,127),outline=(255,255,255,255))
	back.paste(poly,mask=poly)
	back.show()



test_pointstring_to_positions()