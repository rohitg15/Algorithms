#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<limits.h>

using namespace std;



#define FOR(i,x,n) for(int i=x;i<n;i++)


int main(int argc,char **argv)
{
	freopen("ip.txt","r",stdin);
	int n,cur_max = INT_MIN,cur_max_count = 0;
	scanf("%d",&n);
	int *a = (int*)malloc(n*sizeof(int));
	FOR(i,0,n){
		scanf("%d",&a[i]);
		}
		
	FOR(i,0,n)
	{
	/*
		if the same element has been observed already, increment the count
	*/
		if (a[i] == cur_max)
		{
			cur_max_count++;
		}
		else
		{
			/*  
				if there was no max element previously, then update it with the current element
				if there is a different max element, then decrement its count
			*/
			if (cur_max == INT_MIN)
			{
				cur_max = a[i];
				cur_max_count = 1;
			}
			else
			{
				cur_max_count--;
			}
			/* if the count of the max element reaches zero, simply make it -INF, so that the next incoming element can add itself  */
			if (cur_max_count == 0)
			{
				cur_max = INT_MIN;
			}
		}
	
	}
	
	cur_max_count = 0;
	/*  
		check if this is actually a majority element in the array
	*/
	FOR(i,0,n)
	{
		if (a[i] == cur_max)
			cur_max_count++;
	}
	
	if (cur_max_count > n>>1)
		printf("ans : %d\n",cur_max);
	else
		printf("No such element found\n");
	
	free(a);

	return 0;
}