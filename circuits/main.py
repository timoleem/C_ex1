from process_files import import_circuit 
from matrix import Matrix

import numpy as np

f = 'circuit_board_1.xlsx'
x, y, c, n1, n2, n3 = import_circuit(f)

m = Matrix(x, y, c)

# for index, row in n1.iterrows():
#     m.set_path(row['first'], row['second'])
#     print(m)
#     print(row['first'], row['second'])



print(m)
print(m.get_key_cor(16))
print(m.get_key_cor(2))

# # print(m.a_star(1, 5))
# m.set_path(1, 5)
# print(m)
# m.set_path(1, 2)
# print(m)