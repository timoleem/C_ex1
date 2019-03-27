from matrix import Matrix

import numpy as np
from heapq import heappop, heappush

class Circuit(object):

    def __init__(self, x, y, p):

        self.xbound = x
        self.ybound = y
        self.zbound = 7        
        self.links = p

        self.matrix = Matrix(self.xbound, self.ybound, self.zbound, self.links)
        self.heath_map = Matrix(self.xbound, self.ybound, self.zbound, \
                                self.links)
        
        self.total_cost = 0
        self.path = 101
        self.neighbours_xyz = [(0, 0, 1), (0, 1, 0), (0, 0, -1), \
                               (0, -1, 0), (1, 0, 0), (-1, 0, 0)]

    def distance(self, current, point):

        (z1, y1, x1) = current
        (z2, y2, x2) = point

        return abs(x1 - x2) + abs(y1 - y2) + abs(z1 - z2)

    def get_cost(self, current, goal):

        s = np.array([current[0], current[1], current[2]])
        g = np.array([goal[0], goal[1], goal[2]])
            
        dist = np.linalg.norm(s-g)

        (z1, y1, x1) = current
        (z2, y2, x2) = goal

        key = self.heath_map.get_point(x1, y1, z1)

        if key > 0: 
            key = 0

        cost = abs(x1 - x2) + abs(y1 - y2) + \
               abs(z1 - z2)*1.2 + dist + abs(key) - z1
        return cost

    def conflict(self, point, end_point, prev_points):

        conflict = False
        z, y, x = point

        if x >= self.xbound or y >= self.ybound or z < 0 or z >= 7:
            conflict = True
        elif point in prev_points:
            conflict = True
        else: 
            key = self.matrix.get_point(x, y, z)
            if key > 0 and int(key) != int(end_point):
                conflict = True
        return conflict

    def a_star2(self, start, end, end_key):

        current = start
        history = []
        gscore = {start:0}
        fscore = []
        heappush(fscore, (self.get_cost(start, end), [start]))
        best_path = []

        while True:

            best_path_cost = heappop(fscore)
            best_path = best_path_cost[1]
            current = best_path[-1]
            dist = self.distance(current, end)

            # print("BEST PATH \n")
            # print(best_path)

            for n in self.neighbours_xyz:
                cz = current[0] + n[0]
                cy = current[1] + n[1]
                cx = current[2] + n[2]
                cur_neighbour = (cz, cy, cx)

                if cur_neighbour == end:
                    return best_path
                if self.conflict(cur_neighbour, end_key, best_path) is True:
                    continue

                tentative_gscore = gscore[current] + 1
                gscore[cur_neighbour] = tentative_gscore
                temp = best_path + [cur_neighbour]
                heappush(fscore, (gscore[cur_neighbour] + \
                         self.get_cost(cur_neighbour, end) + dist, temp))

    def update_heath_map(self, start, goal):

        self.heath_map = Matrix(self.xbound, self.ybound, 7, self.links)

        for point, x, y in self.links:
            self.heath_map.insert(point, x, y, 0)

            for n in self.neighbours_xyz:
                cz = 0 + n[0]
                cy = y + n[1]
                cx = x + n[2]

                value = self.heath_map.get_point(cx, cy, cz)
                if value <= 0:
                    if cz == 0:
                        self.heath_map.insert(value - 3, cx, cy, cz)
                    else: 
                        self.heath_map.insert(value - 10, cx, cy, cz)

    def update_heath_end(self, goal):

        z, y, x = goal
        for n in self.neighbours_xyz:
            cz = 0 + n[0]
            cy = y + n[1]
            cx = x + n[2]

            value = self.heath_map.get_point(cx, cy, cz)
            if value < 0:
                self.heath_map.insert(0, cx, cy, cz)

    def set_path(self, start, goal):

        self.update_heath_map(start, goal)

        strt = self.matrix.get_key_cor(start)
        gl = self.matrix.get_key_cor(goal)

        self.update_heath_end(gl)

        print(strt, gl)
        print("")

        if gl and strt: 
            circuit = self.a_star2(strt, gl, goal)
            print(circuit)
            for step in circuit[1:]:
                z, y, x = step
                self.matrix.insert(self.path, x, y, z)
                self.total_cost += 1
        self.path += 1

    def get_total_cost(self):

        return self.total_cost

    def __str__(self):

        return str(self.matrix)



