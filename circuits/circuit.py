import numpy as np
from matrix import Matrix
from heapq import heappop, heappush

# Timo Leemans
# 10785612

""" The following Class contains everything necessary to find the shortest path
between points on a grid. I have made a variation on Astar that remembers 
previous paths but keeps on taking the quickest path untill the costs are 
higher then paths taken in the past. It works well enough to find a solution.
"""

class Circuit(object):

    def __init__(self, x, y, p):

        self.xbound = x
        self.ybound = y
        self.zbound = 7        
        self.links = p

        # Two maps, one to keep track of the paths, the other to assign weights
        # to points in the grid to improve the path-finding
        self.matrix = Matrix(self.xbound, self.ybound, self.zbound, self.links)
        self.heath_map = Matrix(self.xbound, self.ybound, self.zbound, \
                                self.links)
        
        # keeping track of the costs
        self.total_cost = 0
        # first path starts with 101, then 102 etc... 
        self.path = 101
        # 6 possible neighbours of point x
        self.neighbours_xyz = [(0, 0, 1), (0, 1, 0), (0, 0, -1), \
                               (0, -1, 0), (1, 0, 0), (-1, 0, 0)]

    # Calculate the Manhatten distance between two points
    def distance(self, current, point):

        (z1, y1, x1) = current
        (z2, y2, x2) = point

        return abs(x1 - x2) + abs(y1 - y2) + abs(z1 - z2)

    # Total heuristical cost between two points
    def get_cost(self, current, goal):

        # direct distance between two points
        s = np.array([current[0], current[1], current[2]])
        g = np.array([goal[0], goal[1], goal[2]])    
        dist = np.linalg.norm(s-g)

        # Coordinates of the current point and the goal
        (z1, y1, x1) = current
        (z2, y2, x2) = goal

        # If the key value is either a key or a path, then ignore it
        key = self.heath_map.get_point(x1, y1, z1)
        if key > 0: 
            key = 0

        # I used both metrics for the cost function as it improved path-finding
        cost = abs(x1 - x2) + abs(y1 - y2) - \
               abs(z1 - z2)*0.3 + dist - z1 + abs(key)
        return cost

    # If there is a conflict, ignore this option (set conflict to True)
    def conflict(self, point, end_point, prev_points):

        conflict = False
        z, y, x = point

        # If x/y/z is out of bounce, or if it is a previous path or
        # if the key value is bigger then zero AND not the final goal. 
        if x >= self.xbound or y >= self.ybound or z < 0 or z >= 7:
            conflict = True
        elif point in prev_points:
            conflict = True
        else: 
            key = self.matrix.get_point(x, y, z)
            if key > 0 and int(key) != int(end_point):
                conflict = True
        return conflict

    # Some parts taken from A star but mostly rewritten. It always takes the 
    # path with the lowest cost and remembers previous paths in a heap
    def shortest_path(self, start, end, end_key):

        # All lists/heaps/dicts necessary to keep track of possible paths
        current = start
        history = []
        gscore = {start:0}
        fscore = []
        heappush(fscore, (self.get_cost(start, end), [start]))
        best_path = []

        # I allow it to try a 1000 times before returning the path
        for i in range(1000):

            # Do not pop the last element in the list
            if len(fscore) > 1:
                best_path_cost = heappop(fscore)
            else: 
                best_path_cost = fscore[0]

            # Take the best possible path untill now
            best_path = best_path_cost[1]
            current = best_path[-1]
            # The closer it is, the lower the cost (it favors short options)
            dist = self.distance(current, end)

            # Check possible paths for all neighbours, if no conflict then add
            # it to the possible paths with its cost value
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
        return []

    # Set all neighbour as weights to keep options possible to connect
    def update_heath_map(self, start, goal):

        self.heath_map = Matrix(self.xbound, self.ybound, 7, self.links)

        for point, x, y in self.links:
            self.heath_map.insert(point, x, y, 0)
            free_neighbours = 0
            for n in self.neighbours_xyz:
                cz = 0 + n[0]
                cy = y + n[1]
                cx = x + n[2]
                value = self.heath_map.get_point(cx, cy, cz)
                if value <= 0:
                    # Prevent paths to go over other keys in the grid and
                    # keep locations free, especially where keys have few 
                    # open spaces 
                    if cz == 0:
                        self.heath_map.insert(value - 2 - free_neighbours, \
                                              cx, cy, cz)
                    else: 
                        self.heath_map.insert(value - 5, cx, cy, cz)
                        self.heath_map.insert(value - free_neighbours, cx, \
                                              cy, cz+1)
                else: 
                    free_neighbours += 1

    # The goal does not need to have weights as it is meant to be achieved.
    def update_heath_end(self, goal):

        z, y, x = goal
        for n in self.neighbours_xyz:
            cz = 0 + n[0]
            cy = y + n[1]
            cx = x + n[2]
            value = self.heath_map.get_point(cx, cy, cz)
            if value < 0:
                self.heath_map.insert(0, cx, cy, cz)

    # Set path of two points and return True if succeeded, else return False.
    def set_path(self, start, goal):

        # Update heath map
        self.update_heath_map(start, goal)
        strt = self.matrix.get_key_cor(start)
        gl = self.matrix.get_key_cor(goal)
        self.update_heath_end(gl)

        # Find shortest path (or a path in general)
        if gl and strt: 
            circuit = self.shortest_path(strt, gl, goal)
            if not circuit:
                return False
            for step in circuit[1:]:
                z, y, x = step
                self.matrix.insert(self.path, x, y, z)
                self.total_cost += 1
        self.path += 1
        return True

    # Return the total cost
    def get_total_cost(self):

        return self.total_cost

    # Print the matrix 
    def __str__(self):

        return str(self.matrix)



