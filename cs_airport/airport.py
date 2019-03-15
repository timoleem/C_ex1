import argparse

"""
The Airport class which takes the BST tree and sets the plane flight 
   schedule according to the waiting time. Both the simple and the 
   'not simple' version work. 

Timo Leemans
10785612
"""

from bst import BST

class Airport(BST):
    def __init__(self, wait_time=300000, simple=False):
        BST.__init__(self)
        
        self.wait_time = wait_time
        self.simple = simple
    
    def find_conflict(self, time):
        """Return the first node in the tree that conflicts with the specified
           time and wait_time attribute set for the Airport.
           
           Returns None if no such conflict is found."""
        node = self.root
        wait_time = self.wait_time

        while node is not None: 
            lower_limit = node.key - wait_time
            upper_limit = node.key + wait_time
            
            if time > lower_limit and time < upper_limit: 
                return node
            if time < node.key: 
                node = node.left
            else: 
                node = node.right
        return None
    
    def bounded_insert(self, time, tailnumber):
        """Inserts a airplane with a time and tailnumber into the schedule.
           If the difference between the proposed time and an existing node
           in schedule is less then the wait_time, the airplane cannot be
           scheduled at that time.
           
           If the simple flag is set to True, conflict are not inserted
           and otherwise the program will try to insert in the next
           possible timeslot.

           Returns the node if successfully inserted and None otherwise."""
        if self.root is None: 
            node = self.insert(time, tailnumber)
            return node

        if self.simple is False: 
            conflict = self.find_conflict(time)
            if conflict is not None: 
                new_time = conflict.key + self.wait_time
                self.bounded_insert(new_time, tailnumber)
            else: 
                node = self.insert(time, tailnumber)
                return node 
        else: 
            conflict = self.find_conflict(time)
            if conflict is None: 
                node = self.insert(time, tailnumber)


    def __str__(self):
        """Return the airplanes in the schedule in sorted order."""
        schedule = ""

        schedule_list = self.in_order_traversal()
        for node in schedule_list:
            schedule += str(node)
            if node is not schedule_list[-1]:
                schedule += " "
        return schedule

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Sort a list of elements.')
    parser.add_argument('elements', nargs='+',
                    help='The elements of a list')
    parser.add_argument("-t", "--timestep", type=int,
                    help="set the minimum timestep (default=300000)", default=300000)
    parser.add_argument("-s", "--simple", action="store_true",
                    help="either become simple or not")
    args = parser.parse_args()

    cs_airport = Airport(args.timestep, args.simple)
    for elem in args.elements:
        try:
            s = elem.split('/')
            time, tail = int(s[0]), s[1]
            cs_airport.bounded_insert(time, tail)
        except (ValueError, IndexError):
            print("Invalid airplane format: "+elem)
    
    print(cs_airport)


# python3 airport.py 37/BLZ 256/TAA 87/OOP 123/TRX 73/STO 11/CRO 252/WRQ -t 10 -s 11/CRO 37/BLZ 73/STO 87/OOP 123/TRX 256/TAA



