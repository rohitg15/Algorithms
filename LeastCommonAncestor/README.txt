This is a sample implementation of the least common ancestor problem. The input is a binary tree and the keys corresponding to two other nodes are provided. Each node has the following structure -

     struct node
     {
	int x;
	node *left,*right
     };

node *root; // the root node of the tree
So given (root,a,b) where a and b are 2 integers, we must search for the least common ancestor of 2 nodes whose keys are equal to a and b respectively. We return NULL if either of the nodes are absent from the tree.

We use a recursive algorithm to search for the LCA and return NULL if either of the nodes were not present. 

Time complexity : O(n) 
     where n is the number of nodes in the tree.
