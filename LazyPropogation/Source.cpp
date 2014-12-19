#include<stdio.h>
#include<stdlib.h>
#include "LazyPropogationHelper.h"

int main()
{
	int n;
	unsigned int i=0;
	scanf("%d",&n);
	int *a = (int*)malloc(n * sizeof(int));
	memset(a,0,n * sizeof(int));


	LazyPropogation helper(a,n);

	helper.update_tree(1, 0, n-1, 0, 6, 5); // Increment range (0, 6) by 5
	helper.update_tree(1, 0, n-1, 7, 10, 12); // Incremenet range (7, 10) by 12
	helper.update_tree(1, 0, n-1, 10, n-1, 100); // Increment range (10, n-1) by 100

	printf("max element in the range [0,%d] is : %d\n",n-1,helper.query_tree(1, 0, n-1, 0, 1));

	system("PAUSE");
 


	free(a);
}