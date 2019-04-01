from process_files import import_circuit, distance_priority, circuits_priority, n_c_specific, distance
from matrix import Matrix
from circuit import Circuit
from random import shuffle
from heapq import heappush, heappop, heapify

import numpy as np

# Timo Leemans
# 10785612

"""Testing algorithms. These try to find the shortest path. Everytime it finds 
a dead end, it moves the failed connection one up the list to make sure that 
connection will be found the next time. If it failes multiple times, then the 
list is shuffled. I do multiple things here and lost track of who and what but I
will try to make it clear"""

# Searches the shortest path and moves the failed connection up the list
def shortest_path(C, x, y, c, n, t, s):

    paths = []
    i = 1
    temp = 0
    for j in range(15):
    	# New grid with a differend n 
        C = Circuit(x, y, c)
        for x_n, y_n in n:
        	# change the direction of the connection (did not help though)
            if s:
                y_n, x_n = x_n, y_n
            # keep track of the amount of paths found
            if C.set_path(x_n, y_n):
                i += 1
            else:
            	# if the same path failed, change it to index 10 (dont ask why)
                if i == temp:
                    heappush(paths, (t-i, n))
                    n[10], n[i-1] = n[i-1], n[10]
                    temp = i
                    i = 1
                    break
                # If path failed, move the connection one up the list
                else:
                    heappush(paths, (t-i, n))
                    n[i-2], n[i-1] = n[i-1], n[i-2]
                    temp = i
                    i = 1
                    break
    if paths:
    	print(paths[0][0])
    	return paths[0]
    else: 
    	print(paths[0][0])
    	return []

# Shuffel the two parts of the list, depending on how big the list is
def shuffle_n(l, value):

    a = l[:value]
    b = l[value:]
    shuffle(a)
    shuffle(b)
    return a+b

# Find the quickest path or else a path that gets as close as possible
def search_till_found(x, y, n, c, shuffle_val, iterations):

	# Fresh start
    C = Circuit(x, y, c)
    n = circuits_priority(n, c)
    total_links = len(n)
    heap = []
    # Else the if statement crases later
    heappush(heap, (100, 0))

    # shuffle the deck, assign values to variables
    n = shuffle_n(n, shuffle_val)
    temp, spec, temp2, temp3 = -1, False, 0, 0

    # Either use a while loop till you find all or a forloop for any path
    # while heap[0][0] != 0:
    for i in range(iterations):
        shortest = shortest_path(C, x, y, c, n, total_links, spec)

        if not shortest: 
        	n = shuffle_n(n, shuffle_val)
        # If it found the same path, shuffle it
        elif temp == shortest[0]:
            n = shuffle_n(n, shuffle_val)
        # Else push the new path to the heap
        else:
            temp0 = heap[0][0]
            if temp0 == heap[0][0]:
                temp3 += 1
            if temp3 >= 5:
                spec = True
            temp = shortest[0]
            heappush(heap, shortest)
            n = heap[0][1]
    return heap[0]


