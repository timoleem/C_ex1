import pandas as pd
import numpy as np
import os

file = 'circuit_board_1.xlsx'

if not os.path.exists(file):
	print('no')	
else: 
	df = pd.read_excel(file, index_col=None)
	gate = {}
	netlist = {}

	print(df)

	for i in range(len(df['Circuit Board'])):
		print(df['Circuit Board'][i])
		# gate[df['Circuit Board'][i]] = (df['X42 – 1'][i], df['Unnamed: 2'][i])	

	print(gate)
	
