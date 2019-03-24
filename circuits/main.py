from process_files import import_circuit 
from matrix import Matrix
from circuit import Circuit

import numpy as np

""" Choose either f1 or f2 as files and n1, n2 or n3 as netlist """

# file = input()
# netlist = input()

# if file == 'f1':
# 	f = 'circuit_board_1.xlsx'
# else: 
# 	f = 'circuit_board_2.xlsx'

f = 'circuit_board_1.xlsx'

x, y, c, n1, n2, n3 = import_circuit(f)

c = Circuit(x, y, c)
n = n1

# if netlist == 'n1':
# 	n = n1
# elif netlist == 'n2':
# 	n = n2
# else: 
# 	n = n3

# print(c)
i = 1

for index, row in n.iterrows():
    print(row['first'], row['second'], i)
    c.set_path(row['first'], row['second'])
    print(c)
    i += 1

# print(c)
print(c.get_total_cost())


