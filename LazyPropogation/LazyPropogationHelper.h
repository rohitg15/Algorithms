#include<stdlib.h>
#include<string.h>

class LazyPropogation
{
	int *a,*tree,*lazy;
	int array_length,tree_length,lazy_length;


	int gcd(int a,int b);
	int logn(int &n);

	void build_tree(int node,int lo,int hi);


public:
	/* 
	   Allocate the memory for the tree and lazy arrays 
	 */
	LazyPropogation(int *arr,int &length)
	{
		array_length = length;
		a = arr;
		/* the tree's maximum possible size is 2*2^(1+Log(n)) where n is the size of the array */
		lazy_length = tree_length = (1<<(1+logn(array_length)))<<1;
		/* allocate memory for the arrays  */
		tree = (int*)malloc(tree_length * sizeof (int));
		lazy = (int*)malloc(lazy_length * sizeof (int));
		/* initialize the arrays */
		memset(tree,0,tree_length * sizeof(int));
		memset(lazy,0,lazy_length * sizeof(int));

		build_tree(1,0,array_length-1);

	}

	void update_tree(int node,int lo,int hi,int i,int j,int value);

	int query_tree(int node,int lo,int hi,int i,int j);


	/* 
	   Deallocate the memory allocated for the tree and lazy arrays  
	*/
	~LazyPropogation()
	{
		free(tree);
		free(lazy);
	}
};

/* 
   This function computes the GCD of the given numbers (a,b) usign Euclid's Algorithm  
*/
int LazyPropogation::gcd(int a,int b)
{
	if (a <= 0 || b <= 0)
	{
		return -1;
	}
	if (a < b)
	{
		return gcd(b,a);
	}

	if (b == 1 || a == 1)
	{
		return 1;
	}

	while(b)
	{
		int temp = a%b;
		a = b;
		b = temp;
	}

	return a;
}

/* 
    This function returns the logarithm of the input n to the base 2  
*/
int LazyPropogation::logn(int &n)
{
	if ( n <= 0)
	{
		return -1;
	}

	if (n == 1)
	{
		return 0;
	}
	int x = 1,i = 1;
	while(x <= n)
	{
		x = (1<<i);
		i++;
	}

	return --i;
}

/* 
   This method Builds the Segment Tree
   Call this method as follows - build_tree(1,0,n-1) where n is the length of the input array
*/
void LazyPropogation::build_tree(int node,int lo,int hi)
{
	if (lo == hi)
	{
		/* This is a leaf node */
		tree[node] = a[lo];
		return;
	}
	/* Recursively build the left and right subtrees */
	build_tree(node<<1,lo,(lo+hi)>>1);
	build_tree(1+(node<<1),1+((lo+hi)>>1),hi);
	/* update the root node with the max value from the left and right subtrees */
	tree[node] = (tree[node<<1] > tree[(node<<1)+1]) ? tree[node<<1] : tree[(node<<1) + 1];
}

/* 
   Perform update operations on the segment tree
   Invoke this method as follows - 
   update_tree(1,0,n-1,2,3,value) to update the range [2,3] with the value = value. n is the length of the original array	
*/
void LazyPropogation::update_tree(int node,int lo,int hi,int i,int j,int value)
{
	if (lazy[node] != 0)
	{
		/* we must update the value of the tree at node */
		tree[node] += lazy[node];
		if (lo != hi)
		{
			/* This node is not a leaf and consequently has child nodes 
			   Mark the child nodes for an update
			*/
			lazy[node<<1] += lazy[node];
			lazy[(node<<1) + 1] += lazy[node];
		}
		/* mark the current node as updated  */
		lazy[node] = 0;
	}

	if (lo > hi || lo > j || hi < i)
		{
			return ;
		}
	/* if the current interval falls completely ewithin the queried interval, then update the value */
	if (lo >= i && hi <= j)
	{
		tree[node] += value;
		/* This node is not a leaf and consequently has child nodes 
		   Mark the child nodes for an update
		*/
		if (lo != hi)
		{
			lazy[node<<1] += value;
			lazy[(node<<1) + 1] += value;
		}
		return ;
	}
	update_tree(node<<1,lo,(lo+hi)>>1,i,j,value);
	update_tree((node<<1) + 1,((lo+hi)>>1) + 1,hi,i,j,value);

	/* Update the root node with the max of left and right children */
	tree[node] = (tree[node<<1] > tree[(node<<1)+1]) ? tree[node<<1] : tree[(node<<1) + 1];
	
}

/*
	This method queries the segment tree for a given range
	Invoke this methods as follows - 
	query_tree(1,0,n-1,2,3) to get the maximum element in the range 2,3. n is the length of the original array
*/
int LazyPropogation::query_tree(int node,int lo,int hi,int i,int j)
{
	if (lazy[node] !=0 )
	{
		/* 
		   we must update the value of the tree at node 
		 */
		tree[node] += lazy[node];
		if (lo != hi)
		{
			/* 
			   This node is not a leaf and consequently has child nodes 
			   Mark the child nodes for an update
			*/
			lazy[node<<1] += lazy[node];
			lazy[(node<<1) + 1] += lazy[node];
		}
		/* 
		   mark the current node as updated  
		*/
		lazy[node] = 0;
	}

	/*
		The current interval is outside the range of the query interval
	*/
	if (i > j || lo > j || hi < i)
	{
		return INT_MIN;
	}

	/*
		The current interval lies completely inside the queried interval
	*/
	if ( lo >= i && hi <= j)
	{
		return tree[node];
	}

	int left = query_tree(node<<1,lo,(lo+hi)>>1,i,j);
	int right = query_tree((node<<1) + 1,((lo+hi)>>1) +1,hi,i,j);
	
	return (left > right) ? left : right;
}