import numpy as np

# Timo Leemans
# 10785612

"""The matrix class contains everything to create a matrix and insert the 
key points according to their coordinations"""

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

    # Insert points of to the grid with its value.
    def insert(self, point, x, y, z):

        if x <= self.xbound and y <= self.ybound and \
           x >= 0 and y >= 0 and z >= 0 and z <= 7: 
            self.matrix[z, y, x] = point

    # Get the coordinates of 
    def get_key_cor(self, key):

        x, y, z = np.where(self.matrix==key)
        if len(x) == 0:
            return ()
        return (x[0], y[0], z[0])

    # Get the key value of a specific point in the grid.
    def get_point(self, x, y, z):
        # print(x, y, z)
        return self.matrix[z, y, x]

    # Remove zero layers to print out only the used layers.
    def remove_zero_layer(self):

        m = self.matrix

        for layer in range(len(m)):
            if np.count_nonzero(m[layer]) == 0:
                for delete in range(len(m)-layer):
                    m = np.delete(m, 6 - delete, axis=0)
                return m

    # Print the layers and the paths inside it that are taken. 
    def __str__(self):

        print_matrix = self.remove_zero_layer()

        s = ""
        n = 1
        for layer in print_matrix:
            s += "### LAYER %d ###" % (n,) + "\n"
            for row in layer: 
                for point in row: 
                    if point == 0:
                        s += "__ "
                    elif point < 100:
                        s += "GA "
                    else: 
                        if point > 109:
                            s += str(int(point-100)) + " "
                        else: 
                            s += "0" + str(int(point-100)) + " "
                s += "\n"
            s += "\n"
            n += 1
        return s



