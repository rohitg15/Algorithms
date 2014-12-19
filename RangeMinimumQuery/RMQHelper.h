#include<stdlib.h>
#include<stdio.h>

class RangeMinimumQueryHelper
{


	 int *a,*tree;
	 int array_length,tree_size;

	 int LOGN(int &n)
	 {
		 if (n <= 0)
		 {
			 return -1;
		 }
		 if (n == 1)
		 {
			 return 0;
		 }
		 int i = 1,x=0;
		 while(x <= n)
		 {
			 x = 1<<i;
			 i++;
		 }
		 return --i;
	 }

	


	 int calculate_tree_size();
	 

	 void BuildSegmentTree(int node,int lo,int hi);


public:

	  RangeMinimumQueryHelper(int* &source,int &size)
	 {
		 a = source;
		 array_length = size;
		 tree_size = calculate_tree_size();
		 tree = (int*)malloc(tree_size*sizeof(int));
		 BuildSegmentTree(1,0,array_length-1);
	 }

	  int QuerySegmentTree(int node,int lo,int hi,int i,int j);

	  ~RangeMinimumQueryHelper()
	  {
		  free(tree);
	  }



	 

};

int RangeMinimumQueryHelper::calculate_tree_size()
{
	// tree_size = 2*(2^[log(array_length)] + 1)
	int n = LOGN(array_length);
	return (1<<(n+1))<<1;
}

void RangeMinimumQueryHelper::BuildSegmentTree(int node,int lo,int hi)
{
	if (node > tree_size)
	{
		printf("the tree is not large enough to hold the values\n");
		return ; 
	}
	if (lo == hi)
	{
		 tree[node] = lo;
	}
	else
	{
		//recursively build the segment tree for the left and right subtrees from the current node
		BuildSegmentTree(node<<1,lo,(lo+hi)>>1);
		BuildSegmentTree((node<<1) + 1,((lo+hi)>>1) + 1,hi);

		//update the root node with the minimum of the left and right subtrees
		if (a[tree[node<<1]] < a[tree[(node<<1)+1]])
		{
			tree[node] = tree[node<<1];
		}
		else
		{
			tree[node] = tree[(node<<1)+1];
		}
	    
	}
}

/* lo,hi specify the range of the original array that was supposed to be queried
	i,j specify the query interval
	This returns the index of the smallest array element that falls in the range i,j
*/
int RangeMinimumQueryHelper::QuerySegmentTree(int node,int lo,int hi,int i,int j)
{
	if (i>j || lo>hi)
	{
		return -1;
	}
	// if the current interval and query interval do NOT intersect, then return -2
	if (i>hi || j<lo)
	{
		return -2;
	}
	if (lo >= i && hi <= j)
	{
		return tree[node];
	}
	/* In this case we must compute the minimum values from the left and right subtrees recursively, as the query interval i,j is 
		contained within the current interval lo,hi
	*/
	int left_min = QuerySegmentTree(node<<1,lo,(lo+hi)>>1,i,j);
	int right_min = QuerySegmentTree((node<<1) + 1,((lo+hi)>>1) +1,hi,i,j);

	if (left_min == -2)
	{
		return tree[node] = right_min;
	}
	if (right_min == -2)
	{
		return tree[node] = left_min;
	}
	if (a[left_min] < a[right_min])
	{
		return tree[node] = left_min;
	}
	return tree[node] = right_min;

}

