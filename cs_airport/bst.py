from node import Node

class BST(object):
    def __init__(self, key_list=[]):
        """Create a new BST, set its attributes, and insert all the keys in
           the key_list into the BST."""
        self.root = None
        self.size = 0
        for key in key_list:
            self.insert(key)
            self.back_to_top()
    
    def get_root(self):
        """Return the root of the BST."""
        return self.root
    
    def is_empty(self):
        """Return True if the BST is empty."""
        if not self.root: 
          return True
    
    def find_max(self):
        """Return the node with the maximum key in the BST."""
        self.back_to_top()
        if self.root is None: 
            return None
        elif self.root.right is None: 
            return self.root
        else: 
            while self.root.right is not None: 
                self.root = self.root.right
        max_node = self.root
        return max_node
    
    def find_min(self):
        """Return the node with the minimum key in the BST."""
        self.back_to_top()
        if self.root is None: 
            return None
        elif self.root.left is None: 
            return self.root
        else: 
            while self.root.left is not None: 
                self.root = self.root.left
        min_node = self.root
        return min_node
    
    def search(self, key):
        """Return the Node object containing the key if the key exists in
           the BST, else return None."""
        self.back_to_top()
        while self.root.key != key: 
            if key > self.root: 
                if self.root.right is not None: 
                    self.root = self.root.right
                else: 
                    return None
            else: 
                if self.root.left is not None: 
                    self.root = self.root.left 
                else: 
                    return None
        key_node = self.root 
        return key_node
    
    def contains(self, key):
        """ Return True if the key exists in the BST, else return False."""
        self.back_to_top()
        while self.root.key != key: 
            if key > self.root: 
                if self.root.right is not None: 
                    self.root = self.root.right
                else: 
                    return False
            else: 
                if self.root.left is not None: 
                    self.root = self.root.left 
                else: 
                    return False
        return True
    
    def insert(self, key, value=None):
        """Create a new node for this key and value, and insert it into the BST.
           Return the new inserted node, or None if the key and value could not
           be inserted."""
        if not self.root: 
            self.root = Node(key, value)
            return self.root

        new_node = Node(key, value)
        current = self.root
        parent_node = None
 
        while current is not None:
            parent_node = current
            if new_node.key < current.key: 
                current = current.left
            else: 
                current = current.right
        new_node.parent = parent_node
        if new_node.key < parent_node.key:
            parent_node.left = new_node
        elif new_node.key > parent_node.key: 
            parent_node.right = new_node
        else: 
            return None        
        return new_node

    def back_to_top(self): 
        """Set the root back at the top of the tree such that the program 
           can start over and work itself down the branches again"""
        while self.root.parent is not None: 
            self.root = self.root.parent 

    def min_rightside_tree(self, node):
        '''Helper function for the delete, get the minimun node of the 
           right side of the tree'''
        if node.left is None: 
            return node
        else: 
            while node.left is not None: 
                node = node.left
        return node    

    def transplant(self, node, child):
        '''Swap two nodes'''
        print(node.key, child.key)
        if node.parent is None: 
            self.root = child
        elif node is node.parent.left:
            node.parent.left = child
        else: 
            node.parent.right = child
        if child is not None: 
            print('yes', child.key)
            child.parent = node.parent


    def delete(self, key):
        """Remove the Node object containing the key if the key exists in
           the BST and return the removed node, else return None.
           
           The returned node is the actual Node object that got removed
           from the BST, and so might be the successor of the removed key."""
        if self.contains(key): 
            node = self.search(key)
            self.back_to_top()
        else: 
            return None

        if node.left is None: 
            self.transplant(node, node.right)
        elif node.right is None:
            self.transplant(node, node.left)
        else: 
            minimum = self.min_rightside_tree(node.right)
            if minimum.parent is not node: 
                self.transplant(minimum, minimum.right)
                minimum.right = node.right
                minimum.right.parent = node 
            self.transplant(node, minimum)
            minimum.left = node.left
            minimum.left.parent = minimum

            # minimum.right = node.right
            # minimum.right.parent = minimum 
        return node
    
    def in_order_traversal(self):
        """Return a list of the Nodes in the tree in sorted order."""
        self.back_to_top()
        order = []
        sorted_order = self.in_order_recursion(self.root, order)
        return sorted_order

    def in_order_recursion(self, root, ordered):
        """"""
        if root.left is not None: 
            self.in_order_recursion(root.left, ordered)
        ordered.append(root.key)
        if root.right is not None:
            self.in_order_recursion(root.right, ordered)
        return ordered

    def breadth_first_traversal(self):
        """Return a list of lists, where each inner lists contains the elements
           of one layer in the tree. Layers are filled in breadth-first-order,
           and contain contain all elements linked in the BST, including the
           None elements.
           >> BST([5, 8]).breadth_first_traversal()
           [[Node(5)], [None, Node(8)], [None, None]]"""
        bft_list = []
        temp_nodes = [self.root]
        bft_list.append([self.root])
        while bft_list[-1]:
            temp_keys = []
            branch = []
            for node in temp_nodes:
                temp_nodes = []
                if node is not None: 
                    if node.left is None: 
                        temp_keys.append(None)
                    else: 
                        temp_keys.append(node.left)
                    if node.right is None: 
                        temp_keys.append(None)
                    else: 
                        temp_keys.append(node.right)
                    temp_nodes.extend((node.left, node.right))
                branch.extend(temp_nodes)
            temp_nodes = branch    
            bft_list.append(temp_keys)
        return bft_list[:-1]
        
    
    def __str__(self):
        """Return a string containing the elements of the tree in breadth-first
           order, with each on a new line, and None elements as `_`, and
           finally a single line containing all the nodes in sorted order.
           >> print(BST([5, 8, 3]))
           5
           3 8
           _ _ _ _
           3 5 8
           """
        if self.root is None: 
            return 'None'
        string = ''  
        for branch in self.breadth_first_traversal():
            for leaf in branch: 
                if leaf is None: 
                    string += str('_ ')
                else: 
                    string += str(leaf) + ' '
            string += '\n'
        for key in self.in_order_traversal(): 
            string += str(key) + ' '
        return string        
        
h = BST([20, 10, 25, 5, 18, 13, 15, 14])
print(h)
h.delete(10)
print('\n')
print(h)









