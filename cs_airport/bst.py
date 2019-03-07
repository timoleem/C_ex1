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
        else: 
            if key < self.root:
                if self.root.left is None: 
                    self.root.left = Node(key, value)
                    self.root.left.parent = self.root
                    # print('yes left', self.root, self.root.left, self.root.left.parent)                 
                    self.min = key 
                else: 
                    self.root = self.root.left
                    # print('no left', self.root, self.root.left)
                    self.insert(key)
            else: 
                if self.root.right is None: 
                    self.root.right = Node(key, value)
                    self.root.right.parent = self.root
                    # print('yes right', self.root, self.root.right, self.root.right.parent)
                    self.max = key
                else: 
                    self.root = self.root.right
                    # print('no right', self.root, self.root.right)
                    self.insert(key)

    def back_to_top(self): 
        """Set the root back at the top of the tree such that the program can start over and
           work itself down the branches again"""
        while self.root.parent is not None: 
            self.root = self.root.parent 

    def delete(self, key):
        """Remove the Node object containing the key if the key exists in
           the BST and return the removed node, else return None.
           
           The returned node is the actual Node object that got removed
           from the BST, and so might be the successor of the removed key."""
        if self.contains(key):
            self.root = self.search(key)
            self.root.left = None
            self.root.right = None
            deleted_node = self.root
            if self.root is self.root.parent.right: 
                self.root.parent.right = None
            elif self.root is self.root.parent.left: 
                self.root.parent.left = None
            self.root.parent = None 
            return deleted_node
        else: 
            return None
        pass
    
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

    def validate_end_tree(self, tree_list):
        for item in tree_list: 
            if isinstance(item, int): 
                return True
        return False

    def breadth_first_traversal(self):
        """Return a list of lists, where each inner lists contains the elements
           of one layer in the tree. Layers are filled in breadth-first-order,
           and contain contain all elements linked in the BST, including the
           None elements.
           >> BST([5, 8]).breadth_first_traversal()
           [[Node(5)], [None, Node(8)], [None, None]]"""
        bft_list = []
        temp_nodes = [self.root]
        bft_list.append([self.root.key])
        while self.validate_end_tree(bft_list[-1]):
            temp_keys = []
            branch = []
            for node in temp_nodes:
                temp_nodes = []
                if node is not None: 
                    if node.left is None: 
                        temp_keys.append(None)
                    else: 
                        temp_keys.append(node.left.key)
                    if node.right is None: 
                        temp_keys.append(None)
                    else: 
                        temp_keys.append(node.right.key)
                    temp_nodes.extend((node.left, node.right))
                branch.extend(temp_nodes)
            temp_nodes = branch    
            bft_list.append(temp_keys)
        return bft_list
        
    
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
           
        

bst = BST([3, 2, 4, 8, 3, 6, 0, 1, 3])
# print(bst.search(4))
# print(bst.contains(3))
# print(bst.contains(6))
# print(bst.find_min())
# print(bst.find_max())
# print('')
# print(bst.in_order_traversal())
# print(bst. breadth_first_traversal())

# print(bst.get_root())
# print(BST([1, 2]).insert(4))