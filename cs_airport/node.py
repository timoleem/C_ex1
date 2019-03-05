class Node(object):
    def __init__(self, key, value=None):
        """Store the key and value in the node and set the other attributes."""
        self.value = value
        self.key = key
        self.height = 0
        self.parent = None
        self.left = None
        self.right = None
    
    def get_key(self):
        """Return the key of this node."""
        return self.key

    def get_value(self):
        """Return the value of this node."""
        return self.value

    def get_parent(self):
        """Return the parent node of this node."""
        return self.parent 

    def get_left_child(self):
        """Return the left child node of this node."""
        return self.left

    def get_right_child(self):
        """Return the right child node of this node."""
        return self.right

    def get_height(self):
        """Return the height of this node."""
        return self.height

    def update_height(self):
        """Update the height based on the height of the left and right nodes."""
        self.height += 1

    def node_or_number(self, other):
        """Evaluate if other is a node or number and return number"""
        if isinstance(other, int):
            return other
        else: 
            return other.key        

    def __eq__(self, other):
        """Returns True if the node key is equal to other, which can be
           another node or a number."""
        if self.key:
            other_value = self.node_or_number(other)     
            if self.key == other_value:
                return True

    def __neq__(self, other):
        """Returns True if the node key is not equal to other, which can be
           another node or a number."""
        other_value = self.node_or_number(other) 
        if self.key != other_value:
            return True
        else:
            return False
    
    def __lt__(self, other):
        """Returns True if the node key is less than other, which can be
           another node or a number."""
        other_value = self.node_or_number(other) 
        if self.key < other_value:
            return True
        else: 
            return False
    
    def __le__(self, other):
        """Returns True if the node key is less than or equal to other, which
           can be another node or a number."""
        other_value = self.node_or_number(other) 
        if self.key <= other_value:
            return True
        else: 
            return False
    
    def __gt__(self, other):
        """Returns True if the node key is greater than other, which can be
           another node or a number."""
        other_value = self.node_or_number(other) 
        if self.key > other_value: 
            return True 
        else: 
            return False
    
    def __ge__(self, other):
        """Returns True if the node key is greater than or equal to other,
           which can be another node or a number."""
        other_value = self.node_or_number(other) 
        if self.key >= other_value:
            return True
        else:
            return False
    
    def __str__(self):
        """Returns the string representation of the node in format: 'key/value'.
           If no value is stored, the representation is just: 'key'."""
        if self.value == None: 
            return str(self.key)
        else:
            string = str(self.key) + '/' + str(self.value) 
            return string
