from node import Node

"""The BST class creates a tree and updates the height of the nodes. It is 
all supposed to work in O(h). In the end it prints the inserted nodes as a 
tree and in sorted order.

Timo Leemans
10785612
"""

class BST(object):
    def __init__(self, key_list=[]):
        """Create a new BST, set its attributes, and insert all the keys in
           the key_list into the BST."""
        self.root = None
        self.size = 0
        for key in key_list:
            self.insert(key)
    
    def get_root(self):
        """Return the root of the BST."""
        return self.root
    
    def is_empty(self):
        """Return True if the BST is empty."""
        if not self.root: 
          return True
    
    def find_max(self):
        """Return the node with the maximum key in the BST."""
        root = self.root
        # keep taking the right node till its right node is None
        if root is None: 
            return None
        elif root.right is None: 
            return root
        else: 
            while root.right is not None: 
                root = root.right
        max_node = root
        return max_node.key
    
    def find_min(self):
        """Return the node with the minimum key in the BST."""
        root = self.root 
        # keep taking the left node till its left node is None
        if root is None: 
            return None
        elif root.left is None: 
            return root
        else: 
            while root.left is not None: 
                root = root.left
        min_node = root
        return min_node.key
    
    def search(self, key):
        """Return the Node object containing the key if the key exists in
           the BST, else return None."""
        root = self.root
        # Take the left or right node according to its key-value untill 
        # it finds the key
        while root.key != key: 
            if key > root: 
                if root.right is not None: 
                    root = root.right
                else: 
                    return None
            else: 
                if root.left is not None: 
                    root = root.left 
                else: 
                    return None
        key_node = root 
        return key_node

    def contains(self, key):
        """ Return True if the key exists in the BST, else return False."""
        root = self.root 
        while root.key != key: 
            if key > root: 
                if root.right is not None: 
                    root = root.right
                else: 
                    return False
            else: 
                if root.left is not None: 
                    root = root.left 
                else: 
                    return False
        return True
    
    def insert(self, key, value=None):
        """Create a new node for this key and value, and insert it into the BST.
           Return the new inserted node, or None if the key and value could not
           be inserted."""

        # If the tree is empty, add the node as root
        if not self.root: 
            self.root = Node(key, value)
            # self.root.update_height()
            self.root.height = 0
            return self.root

        # Else create a node and get the current root node 
        new_node = Node(key, value)
        current = self.root
        parent_node = None
 
        # move the node to the required spot according to its key-value
        while current is not None:
            parent_node = current
            if new_node.key < current.key: 
                current = current.left
            else: 
                current = current.right

        # Assign pointers from node to parent and back, then update height
        new_node.parent = parent_node
        if new_node.key < parent_node.key:
            parent_node.left = new_node
        elif new_node.key > parent_node.key: 
            parent_node.right = new_node
        else: 
            return None
        new_node.update_height()
        return new_node

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
        '''Swap two nodes and re-assign all the pointers between these two 
           nodes. After that update the height from the point of the swapped
           node.'''
        if node.parent is None: 
            self.root = child
        elif node is node.parent.left:
            node.parent.left = child
        else: 
            node.parent.right = child
        if child is not None: 
            child.parent = node.parent
        node.update_height()

    def delete(self, key):
        """Remove the Node object containing the key if the key exists in
           the BST and return the removed node, else return None.
           
           The returned node is the actual Node object that got removed
           from the BST, and so might be the successor of the removed key."""
        
        # If the key is not present, return None, else get the key-node
        if self.contains(key): 
            node = self.search(key)
        else: 
            return None

        # Transplant the right or left node in this order if either is None
        if node.left is None: 
            self.transplant(node, node.right)
        elif node.right is None:
            self.transplant(node, node.left)

        # Transplant the minimum value of the right child and swap this with 
        # its right child if necessary, then swap it with the key-node.
        else: 
            minimum = self.min_rightside_tree(node.right)
            # Remember the parent of the minimum
            parent = minimum.parent
            if minimum.parent is not node: 
                self.transplant(minimum, minimum.right)
                minimum.right = node.right
                minimum.right.parent = node 
            self.transplant(node, minimum)
            minimum.left = node.left
            minimum.left.parent = minimum
            if minimum.right is not None:
                minimum.right.parent = minimum
            # Update the height of the minimum.parent node and its parents
            parent.update_height()
        return node
    
    def in_order_traversal(self):
        """Return a list of the Nodes in the tree in sorted order."""
        order = []
        root = self.root
        sorted_order = self.in_order_recursion(root, order)
        return sorted_order

    def in_order_recursion(self, root, ordered):
        """Helper function to make the recursion happend. It always takes the 
           most left key-value and then the right, untill it is in order"""
        if root.left is not None: 
            self.in_order_recursion(root.left, ordered)
        ordered.append(root)
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

        # Initiate the final bft list and temporary nodes list 
        bft_list = []
        temp_nodes = [self.root]
        bft_list.append([self.root])

        # While there are items in the last list of the bft list
        while bft_list[-1]:
            temp_nodes = bft_list[-1]
            # Keep track of the nodes in the current level of the tree
            level = []
            for node in temp_nodes: 
                if node is not None: 
                    if node.left is None: 
                        level.append(None)
                    else: 
                        level.append(node.left)
                    if node.right is None:
                        level.append(None)
                    else: 
                        level.append(node.right)
            # Add the tree level to the bft list 
            bft_list.append(level)
        # Return all but the last empty list
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

        # Add all nodes to the string with new lines where necessary 
        # (spreekt voor zichaelf toch?)
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
