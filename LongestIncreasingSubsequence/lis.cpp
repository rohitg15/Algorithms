#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<algorithm>
#include<climits>
#include<iostream>

using namespace std;

#define FOR(i,x,n) for(int i=x;i<n;i++)


vector<int> v;

int compute_lis(int *a,int n)
{
  int len = 0, idx = 0;
  if (n <= 0)
    {
      return INT_MIN;
    }

  v.push_back(a[0]);
  len = 1;

  FOR(i,1,n)
    {
      /*
	the current element is lesser than the least element of the current active set. So we
	replace the current active set's smallest element with the current element.
       */
      if (v.size() > 0 && a[i] < v[0])
	{
	  v[0] = a[i];
	}
      /*
	the current element is greater than the largest element of the current active set. So we 
	add this element to our active set and increment the length by 1
       */
      else if (v.size() > 0 && a[i] > v[v.size()-1])
	{
	  v.push_back(a[i]);
	  len++;
	}
      /*
	if the current element is somewhere in between, then we do a binary search
       */
      else
	{
	  vector<int>::iterator pos = lower_bound(v.begin(),v.end(),a[i]);
	  pos--;
	  int pos_idx = pos-v.begin();
	  if (pos_idx >= 0)
	    v[pos-v.begin()] = a[i];
	}
      
    }
  

  return v.size();
}

void print_vec()
{
  for(vector<int>::iterator it = v.begin();it != v.end();it++)
    {
      cout<<*it<<" ";
    }
}


int main(int argc,char *argv[])
{


  freopen("ip.txt","r",stdin);
  int n;
  scanf("%d",&n);
  int *a = new int[n];
  
  FOR(i,0,n)
    {
      scanf("%d",&a[i]);
    }
 
  //call the appropriate function to compute the longest increasing subsequence
    int len = compute_lis(a,n);
    
    printf("length of longest increasing subsequence is %d\n",len);
    printf("\n");
    print_vec();
    delete a;

  return 0;
}
