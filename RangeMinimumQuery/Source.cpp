#include<stdio.h>
#include<stdlib.h>
#include "RMQHelper.h"


int main()
{
	int *arr = NULL,size = 0;
	FILE *f = NULL;
	unsigned int i=0;
	freopen("ip.txt","r",stdin);
	scanf("%d",&size);
	arr = (int*)malloc(size*sizeof(int));
	for(i=0;i<size;i++)
	{
		scanf("%d",&arr[i]);
	}
	RangeMinimumQueryHelper helper(arr,size);
	int pos = helper.QuerySegmentTree(1,0,size-1,1,7);
	f = fopen("op.txt","w");
	fprintf(f,"index : %d  , minimum value : %d",pos,arr[pos]);
	fclose(f);
	free(arr);
	return 0;
}