from process_files import import_circuit 
from matrix import Matrix

import numpy as np

f = 'circuit_board_1.xlsx'
x, y, c, n1, n2, n3 = import_circuit(f)

m = Matrix(x, y, c)

print(" ------------------------------ NEW ------------------------------ ")
print(" ------------------------------ NEW ------------------------------ ")
print(" ------------------------------ NEW ------------------------------ ")
print(" ------------------------------ NEW ------------------------------ ")
print(" ------------------------------ NEW ------------------------------ ")
print(" ------------------------------ NEW ------------------------------ ")
print(" ------------------------------ NEW ------------------------------ ")

for index, row in n1.iterrows():
    print(row['first'], row['second'])
    m.set_path(row['first'], row['second'])    
    print(m)