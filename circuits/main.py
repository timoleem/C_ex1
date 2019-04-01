from circuit import Circuit
from matrix import Matrix
from run import search_till_found
from process_files import import_circuit

# Timo Leemans
# 10785612

"""The main file where you can run the code. Select / Deselect the 
'circuit_board_1.xlsx' or 'circuit_board_2.xlsx' to choose the grid
and set n1 to n2 or n3 to choose the connections. It will run 
for some time (maybe 5 sec per iteration, you can adjust the amount 
of iterations as well. I have tweeked so much the last few hours and 
I have only remembered the completed grids yesterday. If it does not
find a path then some of the parameters are wrong I think.. 

ONLY board1 list1 and board1 list2 succeeded..

Good luck with / enjoy nakijken"""

# f = 'circuit_board_1.xlsx'
f = 'circuit_board_2.xlsx'
x, y, c, n1, n2, n3 = import_circuit(f)
iterations = 3
circ = n2

for i in range(3):

    n = search_till_found(x, y, circ, c, 12, iterations)
    if n[0] <= 30:
        break

C = Circuit(x, y, c)
i = 0
for x, y in n[1]:
    if C.set_path(x, y):
        i += 1

print(C)
print("Got till ", i, "of total ", len(n), " with cost ", C.get_total_cost())


