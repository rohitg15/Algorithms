#include<stdio.h>
#include<iostream>
#include<limits.h>
#include<string.h>

using namespace std;


#define FOR(i,x,n) for(int i=x;i<n;i++)
#define PRINT_ARRAY(a,x,n) FOR(i,x,n) { cout<<a[i]<<" "; }
#define MAX 10000000


int main(int argc,char **argv)
{

	freopen("ip.txt","r",stdin);
	int n,k = INT_MIN,idx = 0;
	scanf("%d",&n);
	if (n > MAX)
	{
		fprintf(stderr,"ERROR: size entered is too big. MAX is 10000000\n");
		return -1;
	}
	
	int *a = (int*)malloc(n*sizeof(int));
	int *b = NULL,*c = NULL;
	if (!a)
	{
		fprintf(stderr,"unable to allocate sufficient memory\n");
		return -1;
	}
	
	FOR(i,0,n)
	{
		scanf("%d",&a[i]);
		if (a[i] < 0)
		{
			fprintf(stderr,"ERROR: Only Positive numbers\n");
			free(a);
			return -1;
		}
		k = (k>a[i])?k:a[i];
		if (k > MAX)
		{
			fprintf(stderr,"ERROR: entered element is too big. MAX is 10000000\n");
			free(a);
			return -1;
		}
	}
	
	b = (int*)malloc((k+1)*sizeof(int));
	if (!b)
	{
		fprintf(stderr,"unable to allocate sufficient memory\n");
		free(a);
		return -1;
	}
	
	
	c = (int*)malloc(n*sizeof(int));
	if (!c)
	{
		fprintf(stderr,"unable to allocate sufficient memory\n");
		free(b);
		free(a);
		return -1;
	}
	
	//initialize count array b to zero
	memset(b,0,sizeof(int)*(k+1));
	
	FOR(i,0,n)
	{
		b[a[i]]++;
	}
	
	/*
		update b to reflect the last possible occurence of every element i (considering multiple occurences as well)
	*/
	FOR(i,1,(k+1))
	{
		b[i] += b[i-1];
	}
	
	FOR(i,0,n)
	{
		if (b[a[i]] > 0)
		{
			//place a[i] in c[b[a[i]] - 1] and decrement b[a[i]]
			c[b[a[i]] - 1] = a[i];
			b[a[i]]--;
		}
	}
	//we don't need b any more
	free(b);
	
	/*
		copy c back to a
	*/
	FOR(i,0,n)
	{
		a[i] = c[i];
	}
	free(c);
	
	PRINT_ARRAY(a,0,n)
	cout<<endl;
	
	free(a);

return 0;
}