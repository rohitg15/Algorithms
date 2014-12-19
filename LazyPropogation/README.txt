The attached program contains a solution to the following problem : 
	Given an array of integers (initialized to 0), we must perform various update and query operations where,
	update -> adds a given value to a range (low,high)
	query  -> returns the maximum value in a given range (low,high)
	
Solution:

	This is a classic Range problem that also requires an update operation. We can Build a Segment Tree where every node stores the maximum value of an interval (i,j)
	The Root would store the maximum value in the entire range (0,n-1) where n is the length of the given array. We build the child nodes recursively and update
	the values of the corresponding root nodes.
	
	Sometimes a Segment Tree alone is inefficient when there are many update/query operations. This is because everytime we query/update a particular range, we 
	must traverse down to every child node corresponding to that range and update that. But we can defer these updates to a later stage where an update/query request
	actually references the respective child nodes. This technique is called Lazy Propogation and we can use that to improve the efficiency of the operations.