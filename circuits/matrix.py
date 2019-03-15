import numpy as np
from scipy.spatial.distance import cdist

from node import Node
from process_files import import_circuit

class Matrix(object):

    def __init__(self, x, y, p):

        self.matrix = np.zeros((x, y))
        self.xbound = x
        self.ybound = y
        self.neighbours = [(1, 0), (0, 1), (-1, 0), (0, -1)]
        self.path = 0.01

        for pp, xx, yy in p: 
            self.insert(pp, xx, yy)

    def insert(self, p_ga, x_ga, y_ga):

        if x_ga <= self.xbound and y_ga <= self.ybound and \
           x_ga >= 0 and y_ga >= 0: 

            node = Node(p_ga, 0)
            self.matrix[x_ga, y_ga] = node.key

    def get_key_cor(self, key):

        x, y = np.where(self.matrix==key)
        if x: 
            return (x[0], y[0])
        return ()

    def cost(self, start, goal):

        (x1, y1) = start
        (x2, y2) = goal
        cost = abs(x1 - x2) + abs(y1 - y2)
        return cost

    def conflict(self, key):
        print(key)
        conflict = False
        x, y = key

        try:
            self.matrix[x, y]
        except IndexError:
            conflict = True

        if self.matrix[x, y] != 0:
            conflict = True

        return conflict

    def a_star(self, key1, key2):

        start = self.get_key_cor(key1)
        end = self.get_key_cor(key2)

        if start and end: 
            path_cost = 0
            current = start
            path = []
            while current != end:
                cost = {}
                for n in self.neighbours:
                    cur_neighbour = (current[0] + n[0], current[1] + n[1]) 
                    if sorted(cur_neighbour) == sorted(end): 
                        return path
                    if self.conflict(cur_neighbour) is False:
                        cur_cost = self.cost(cur_neighbour, end)
                        if cur_cost > 0: 
                            cost[cur_neighbour] = cur_cost
                current = min(cost, key=cost.get)
                path.append(current)
        return []

    def set_path(self, key1, key2):

        for step in self.a_star(key1, key2):
            x, y = step
            self.insert(self.path, x, y)
        self.path += 0.01

    def __str__(self):

        s = ""
        for row in self.matrix: 
            for ga in row: 
                # print(ga)
                if ga == 0: 
                    s += "__ "
                elif ga >= 1:                    
                    # s += "GA "
                    if ga < 10:
                        s += str(int(ga)) + "  "
                    else: 
                        s += str(int(ga)) + " "
                    # s += str(int(ga))
                else: 
                    s += "0" + str(int(ga*100)) + " "              
            s += "\n"

        return s



