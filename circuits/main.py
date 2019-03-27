from process_files import import_circuit, distance_priority, circuits_priority
from matrix import Matrix
from circuit import Circuit

import numpy as np

""" Choose either f1 or f2 as files and n1, n2 or n3 as netlist """

# file = input()
# netlist = input()

# if file == 'f1':
#   f = 'circuit_board_1.xlsx'
# else: 
#   f = 'circuit_board_2.xlsx'

f = 'circuit_board_1.xlsx'
# f = 'circuit_board_2.xlsx'

x, y, c, n1, n2, n3 = import_circuit(f)

C = Circuit(x, y, c)
# n = distance_priority(n1, c)
n = circuits_priority(n1, c)

total_links = len(n)

i = 1
for x, y in n:
    print("             NEW                 ")
    print("---------------------------------")
    print(x, " -> ", y, "link nr ", i, " of total links ", total_links)
    C.set_path(x, y)
    print(C)
    i += 1
    print("")

# print(c)
# print(c.get_total_cost())


