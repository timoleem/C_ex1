import pandas as pd
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

		# dimension = 
		# print(df['Circuit Board'] == 'Dimensions')
		dimension = df[df["Circuit Board"] == "Dimensions"]["X42 – 1"].item()
		x, y = dimension.split(" x ")

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
