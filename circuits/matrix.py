
import numpy as np

class Matrix(object):

    def __init__(self, x, y, z, p):

        self.links = p
        self.matrix = np.zeros((z, y, x))
        self.xbound = x
        self.ybound = y
        self.neighbours_xyz = [(0, 0, 1), (0, 1, 0), (0, 0, -1), \
                               (0, -1, 0), (1, 0, 0), (-1, 0, 0)]

        for pp, xx, yy in p: 
            self.insert(pp, xx, yy, 0)

    def insert(self, point, x, y, z):

        if x <= self.xbound and y <= self.ybound and \
           x >= 0 and y >= 0 and z >= 0 and z <= 7: 
            self.matrix[z, y, x] = point

    def get_key_cor(self, key):

        x, y, z = np.where(self.matrix==key)
        if len(x) == 0:
            return ()
        return (x[0], y[0], z[0])

    def get_point(self, x, y, z):

        return self.matrix[z, y, x]

    def remove_zero_layer(self):

        m = self.matrix

        for layer in range(len(m)):
            if np.count_nonzero(m[layer]) == 0:
                for delete in range(len(m)-layer):
                    m = np.delete(m, 6 - delete, axis=0)
                return m

    def __str__(self):

        # print_matrix = self.remove_zero_layer()
        print_matrix = self.matrix

        s = ""
        for layer in print_matrix:
            for row in layer: 
                for point in row: 
                    if point == 0:
                        s += "__ "
                    elif point < 100:
                        # s += "GA "
                        if point < 10:
                            s += str(int(point)) + "  "
                        else: 
                            s += str(int(point)) + " "
                    else: 
                        if point > 109:
                            s += str(int(point-100)) + " "
                        else: 
                            s += "0" + str(int(point-100)) + " "
                s += "\n"
            s += "\n"
        return s



