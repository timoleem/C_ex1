from __future__ import division
import pandas as pd
from heapq import heappush, heappop, heapify
import os

def process_coordinates(df):

	coo_first = df[df["Circuit Board"] == "Gate number"].index.values
	coo_last = df[df["Circuit Board"] == "Netlist 1"].index.values -1

	c = df[(df.index.values > coo_first) \
					& (df.index.values < coo_last)]
	c.columns = ['point', 'xcor', 'ycor']	

	cor_list = []

	for i in c.index.values:
		p = c['point'][i]
		x = c['xcor'][i]
		y = c['ycor'][i]
		cor_list.append((p, x, y))

	return cor_list


def import_circuit(file):

	if not os.path.exists(file):
		print('no')	
	else: 
		df = pd.read_excel(file, sheet_name='Sheet1')
		gate = {}

		if file == 'circuit_board_1.xlsx':
			dimension = df[df["Circuit Board"] == "Dimensions"]['X42 – 1']
		else: 
			dimension = df[df["Circuit Board"] == "Dimensions"]['X42 – 2']
		
		x, y = dimension.item().split(" x ")

		coordinates = process_coordinates(df)

		index = df.index.values

		nl1_first = df[df["Circuit Board"] == "Netlist 1"].index.values + 1
		nl1_last = df[df["Circuit Board"] == "Netlist 2"].index.values -1

		nl2_first = df[df["Circuit Board"] == "Netlist 2"].index.values + 1
		nl2_last = df[df["Circuit Board"] == "Netlist 3"].index.values -1

		nl3_first = df[df["Circuit Board"] == "Netlist 3"].index.values + 1
		nl3_last = index[-1]

		netlist1 = df[(df.index.values > nl1_first) \
					& (df.index.values < nl1_last)].drop('Unnamed: 2', 1)
		netlist1.columns = ['first', 'second']
		netlist2 = df[(df.index.values > nl2_first) \
					& (df.index.values < nl2_last)].drop('Unnamed: 2', 1)
		netlist2.columns = ['first', 'second']
		netlist3 = df[(df.index.values > nl3_first) \
					& (df.index.values < nl3_last)].drop('Unnamed: 2', 1)
		netlist3.columns = ['first', 'second']

	return int(x), int(y), coordinates, netlist1, netlist2, netlist3

def distance_priority(links, coordinates):

	cor = {}
	for c in coordinates:
		cor[c[0]] = (c[1], c[2])

	priority = []
	for index, row in links.iterrows():
		c1 = cor[row[0]]
		c2 = cor[row[1]]
		distance = abs(c1[0] - c2[0]) + abs(c1[1] - c2[1])
		heappush(priority, (distance, (row[0], row[1])))

	links = []
	while priority:
		links.append(heappop(priority)[1])

	return links

def distance(links, coordinates):

	cor = {}
	dist = {}
	for c in coordinates:
		cor[c[0]] = (c[1], c[2])

	for index, row in links.iterrows():
		c1 = cor[row[0]]
		c2 = cor[row[1]]
		distance = abs(c1[0] - c2[0]) + abs(c1[1] - c2[1])
		dist[(row[0], row[1])] = distance

	return dist

def circuits_priority(links, coordinates):

	priority = []
	occurence = {}
	distance_dict = distance(links, coordinates)

	for index, row in links.iterrows():
		for point in row:
			if point in occurence:
				occurence[point] -= 1
			else: 
				occurence[point] = 4

	for index, row in links.iterrows():
		minimum = min([occurence[row[0]], occurence[row[1]]])
		dist_weight = distance_dict[(row[0], row[1])]/100
		heappush(priority, (minimum + dist_weight, (row[0], row[1])))

	links = []
	while priority:
		links.append(heappop(priority)[1])

	return links















