#include<stdio.h>
#include<stdlib.h>

/* Compute the GCD of x,y using Euclid's Algorithm */
int gcd(int x,int y)
{
	if (y == 0)
	{
		return -1;
	}
	if (y == 1 || x == 1)
	{
		return 1;
	}

	if ( y > x)
	{
		return gcd(y,x);
	}

	while(y)
	{
		int t = x % y;
		x = y;
		y = t;
	}

	return x;
}


/* rotate the array of length by k units 
	Time Complexity = O(n) * GCD(n,k)
*/
void Rotate(int *a,int n,int k)
{
	if (n <= 0)
	{
		return ;
	}
	int GCD = gcd(n,k);
	unsigned int i=0,j=0;
	for(i=0;i<GCD;i++)
	{
		/* Rotate the Array by 1 step here
		 */
		int temp = a[0];
		for(j=0;j<n-1;j++)
		{
			a[j] = a[j+1];
		}
		// place the first element in the last slot
		a[n-1] = temp;
	}
}

void PrintArray(int *a,int n)
{
	unsigned int i=0;
	for(i=0;i<n;i++)
	{
		printf("%d ",a[i]);
	}
}

int main(int argc,char **argv)
{
	freopen("ip.txt","r",stdin);
	int n,k;
	unsigned int i=0;
	scanf("%d%d",&n,&k);
	int *a = (int*)malloc(n*sizeof(int));


	for(i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
	}

	Rotate(a,n,k);

	PrintArray(a,n);

	free(a);

	return 0;
}