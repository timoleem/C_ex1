Timo Leemans
10785612

README
------

External libraries: 

- Numpy (for calculations)
- Heapq (as data structure)
- Pandas (to process the data)

How to use? 


Inside the main.py file you can run the code. 
There is some explanation in that file how to run it. 

Main takes its functions to run the code from run.py. This file runs pretty much all the code. Inside matrix.py there is a class that creates a matrix and inserts all points with its coordinations. Inside circuit.py there is the class that finds the (shortest) paths to and from the connections as assigned in the different netlists. 

Then in the process files there are some functions to process the datafiles correctly. Also here are a few functions to set the netlists in a certain order, depending on the connections between different points in a grid. This is a priority grid to improve path-finding. 

I hope it is clear, I explained everything fairly well inside the files as well. 

Good luck / Enjoy.  