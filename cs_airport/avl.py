from bst import BST

"""AVL class creates a tree while keeping its balance. If there is an inbalance
then rotate the tree and then insert or delete nodes again.

Note: the rotations do NOT work, calculating the balance does work. I did not 
understand how to work with the static functions.

Timo Leemans
10785612
"""

class AVL(BST):
    def __init__(self, key_list=[]):
        """Create a new AVL Tree, set its attributes, and insert all the keys 
           in the key_list into the AVL."""
        BST.__init__(self, key_list)
        self.balance = 0

    def update_balance(self, node):
        """Update the balance of the node and all its parent nodes."""
        while node is not None:
            if node.height == 0:
                node.balance = 0
            elif node.height > 0:
                # According to the formula balance = richt - left 
                if node.left is None: 
                    node.balance = -1 - node.right.height
                elif node.right is None: 
                    node.balance = node.left.height + 1
                else: 
                    node.balance = node.right.height - node.left.height
            # For all parents of the node
            node = node.parent
    
    def balance(self, node): 
        """Return the balance value of the specific node. This is -1 if the 
           node is a None value, else if the height is greater then 0 return 
           the balance of the specific node"""
        if node is None: 
            return - 1
        elif node.height >= 0:
            return node.balance
        else: 
            return - 1

    def insert(self, key, value=None):
        """Create a new node for this key and value, and insert it into the AVL
           using the BST insert operation. In addition, it ensures that the AVL
           tree is still balanced after this operation is performed.
           
           Return the new inserted node, or None if the key and value could not
           be inserted."""

        # Insert a key to the tree
        BST.insert(self, key, value)
        node = BST.search(self, key)
        root = BST.get_root(self)

        # Update balance and fix balance (rotate tree) if necessary
        self.update_balance(node)
        self.fix_balance(node)
    
    def delete(self, key):
        """Remove the Node object containing the key if the key exists in
           the AVL using the BST delete operation. In addition, it ensures that
           the AVL tree is still balanced after this operation is performed.
           
           Return the node that actually got removed from the AVL, which might
           be successor of the removed key."""

        # Delete a key from the tree
        BST.delete(self, key)
        node = BST.search(self, key)
        root = BST.get_root(self)

        # Update balance and fix balance (rotate tree) if necessary
        self.update_balance(node)
        self.fix_balance(root)
    
    @staticmethod
    def left_rotate(node):
        """Performs a left rotation of the specified node. This code is not
           working unfortunately."""
        prev_root = node.parent
        prev_root.right = node.left 

        if node.left is not None: 
            node.left.parent = prev_root
        node.parent = prev_root.parent

        node.left = prev_root
        prev_root.parent = node

    @staticmethod
    def right_rotate(node):
        """Performs a right rotation of the specified node. This code is not
           working unfortunately."""
        new_root = node.left
        node.left = new_root.right

        if new_root.right is not None: 
            new_root.right.parents = node
        new_root.parent = node.parent

        new_root.right = node
        node.parent = new_root

        # Update balance
    
    def fix_balance(self, node):
        """Performs a sequence of rotations to fix the balance of a node and
           all its parent nodes if needed to maintain the AVL property."""
        if node is not None: 
            # I could not finish the code so I wrote a pass just to show 
            # what I had made. It checks if there is a inbalance and it then
            # refers to the rotate functions (not working) to rotate the tree
            # according to its condition.
            while node is not None: 
                if node.parent is not None: 
                    if self.balance(node) < 0 and \
                       self.balance(node.parent) < -1:
                        pass
                    elif self.balance(node) > 0 and \
                         self.balance(node.parent) > 1:
                        pass
                    elif self.balance(node) < 0 and \
                         self.balance(node.parent) > -1: 
                        pass
                    elif self.balance(node) > 0 and \
                         self.balance(node.parent) < 1: 
                        pass 
                node = node.parent

