from matrix import Matrix

import numpy as np

class Circuit(object):

    def __init__(self, x, y, p):

        self.matrix = Matrix(x, y, 7, p)
        self.path = 101
        self.neighbours_xyz = [(0, 0, 1), (0, 1, 0), (0, 0, -1), \
                               (0, -1, 0), (1, 0, 0), (-1, 0, 0)]
        self.xbound = x
        self.ybound = y
        self.total_cost = 0

    def get_cost(self, start, goal):

        s = np.array([start[0], start[1], start[2]])
        g = np.array([goal[0], goal[1], goal[2]])
            
        dist = np.linalg.norm(s-g)

        (z1, y1, x1) = start
        (z2, y2, x2) = goal

        cost = abs(x1 - x2) + abs(y1 - y2) + \
               abs(z1 - z2)*1.5 + dist + abs(self.matrix.get_point(x1, y1, z1))
        return cost

    def conflict(self, point, prev_path):

        conflict = False
        z, y, x = point

        if (x >= self.xbound) or \
           (y >= self.ybound) or \
           (self.matrix.get_point(x, y, z) > 0) or \
           (point in prev_path):
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
                for n in self.neighbours_xyz:
                    cz = current[0] + n[0]
                    cy = current[1] + n[1]
                    cx = current[2] + n[2]
                    cur_neighbour = (cz, cy, cx)
                    if cz >= 0:
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

    def a_star2(self, key1, key2):

        start = self.matrix.get_key_cor(key1)
        end = self.matrix.get_key_cor(key2)
        if start and end: 
            current = start
            path = []
            paths = {}
            while current != end:
                cost_list = {}
                for n in self.neighbours_xyz:
                    cz = current[0] + n[0]
                    cy = current[1] + n[1]
                    cx = current[2] + n[2]
                    cur_neighbour = (cz, cy, cx)
                    if cur_neighbour == end: 
                        return path
                    if self.conflict(cur_neighbour, path) is False:
                        cur_cost = self.get_cost(cur_neighbour, end)
                        cost_list[cur_neighbour] = cur_cost
                if cost_list:
                    current = min(cost_list, key=cost_list.get)
                    path.append(current)
        return []

    def set_path(self, start, goal):

        circuit = self.a_star(start, goal)
        if circuit:
            for step in circuit:
                z, y, x = step
                self.matrix.insert(self.path, x, y, z)
                self.total_cost += 1
        self.path += 1

    def get_total_cost(self):

        return self.total_cost

    def __str__(self):

        return str(self.matrix)



