The attached program contains a solution to the following problem : 
	Given an array of integers (initialized to 0), we must perform various query operations where,
	query  -> returns the minimum value in a given range (low,high)
	
Solution:

	This is a classic Range problem that also requires an update operation. We can Build a Segment Tree where every node stores the minimum value of an interval (i,j)
	The Root would store the minimum value in the entire range (0,n-1) where n is the length of the given array. We build the child nodes recursively and update
	the values of the corresponding root nodes.
	
	LeftChildNode = 2*Node;
	RightChildNode = 2*Node + 1;
	Tree[Node] = min(Tree[LeftChildNode],Tree[RightChildNode]);
	
	Complexity : 
	
	Build Tree : O(n)
	Query Tree : O(Log(n))
	