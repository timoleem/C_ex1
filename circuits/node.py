from matrix import Matrix

import numpy as np

class Circuit(object):

    def __init__(self, x, y, p):

        self.matrix = Matrix(x, y, 7, p)
        self.path = 0.01
        self.neighbours = [(1, 0), (0, 1), (-1, 0), (0, -1), (-1), (1)]
        self.xbound = x
        self.ybound = y

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
           (self.matrix.get_point(x, y) != 0) or \
           (key in prev_path):
            conflict = True

        return conflict

    def a_star(self, key1, key2):

        start = self.matrix.get_key_cor(key1)
        end = self.matrix.get_key_cor(key2)
        if start and end: 
            current = start

            path = []
            while current != end:
                cost_list = {}
                for n in self.neighbours:
                    cur_neighbour = (current[0] + n[0], current[1] + n[1]) 

                    if cur_neighbour == end: 
                        return path
                    if self.conflict(cur_neighbour, path) is False:
                        cur_cost = self.get_cost(cur_neighbour, end)
                        if cur_cost > 0: 
                            cost_list[cur_neighbour] = cur_cost
                if cost_list:
                    current = min(cost_list, key=cost_list.get)
                    path.append(current)
        return []

    def set_path(self, key1, key2):
        circuit = self.a_star(key1, key2)
        if circuit:
            for step in circuit:
                x, y = step
                self.insert(self.path, x, y)
            self.path += 0.01

    def set_path(self, start, goal):

        circuit = self.a_star(start, goal)
        if circuit:
            for step in circuit:
                x, y = step
                self.matrix.insert(self.path, x, y)
            self.path += 0.01

    def __str__(self):

        return str(self.matrix)



