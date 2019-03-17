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
        self.cost = 0

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

    def get_cost(self, start, goal):

        s = np.array([start[0], start[1]])
        g = np.array([goal[0], goal[1]])
            
        dist = np.linalg.norm(s-g)

        (x1, y1) = start
        (x2, y2) = goal
        cost = abs(x1 - x2) + abs(y1 - y2) + dist
        return cost

    def conflict(self, key, prev_path):
        conflict = False
        x, y = key

        if (x >= self.xbound) or \
           (y >= self.ybound) or \
           (self.matrix[x, y] != 0) or \
           key in prev_path:
            # print('yes conflict')
            conflict = True

        return conflict

    def a_star(self, key1, key2):

        start = self.get_key_cor(key1)
        end = self.get_key_cor(key2)
        # print(start, end, key1, key2)
        if start and end: 
            current = start
            # print(current)
            # print('\n')
            path = []
            while current != end:
                cost_list = {}
                for n in self.neighbours:
                    cur_neighbour = (current[0] + n[0], current[1] + n[1]) 
                    # print(cur_neighbour)
                    if cur_neighbour == end: 
                        return path
                    if self.conflict(cur_neighbour, path) is False:
                        cur_cost = self.get_cost(cur_neighbour, end)
                        if cur_cost > 0: 
                            cost_list[cur_neighbour] = cur_cost
                # print('\n')
                if cost_list:
                    current = min(cost_list, key=cost_list.get)
                    path.append(current)
                    print(path)
                # print('\n')
        return []

    def set_path(self, key1, key2):
        circuit = self.a_star(key1, key2)
        if circuit:
            for step in circuit:
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
                    if ga >= 0.10:
                        s += str(int(ga*100)) + " "
                    else: 
                        s += "0" + str(int(ga*100)) + " "              
            s += "\n"

        return s



