#include<iostream>
#include<stdio.h>
#include<vector>
#include<algorithm>
#include<stdlib.h>
#include<set>
#include<climits>

using namespace std;


#define FOR(i,x,n) for(int i=x;i<n;i++)

typedef pair<int,int> PAIR;
typedef vector<PAIR> vp;
typedef vector<vector<PAIR> > vvp;
typedef vector<int> vi;


// this is the graph represented as an adjacency list
vvp g;

// this is the distamce vector denoting the distance of each node
vi d;

// this is the priority queue data structure
set<PAIR> q;


void print_graph(int n)
{
  FOR(i,0,n)
    {
      printf("%d -> ",i);
      FOR(j,0,g[i].size())
	{
	  printf("(%dw,%d) ",g[i][j].first,g[i][j].second);
	}
      printf("\n");
    }
}


void print_shortest_distances(int n)
{
  FOR(i,0,n)
    {
      printf("(%d -> %d) ",i,d[i]);
    }
}


void initialize(int n,int src)
{
  
  g.resize(n);
  d.resize(n);
  FOR(i,1,n)
    d[i] = INT_MAX; 
  d[src] = 0;
	 

  /*
    q is the set datastructure in C++ which behaves pretty much like a priority queue for our purpose
    we insert a pair representing the weight and the corresponding node
    it is initialized with the source node whose initial distance is 0 (src,0)
   */
  q.insert(PAIR(d[src],src));


}

int main(int argc,char *argv[])
{

  if (argc != 2)
    {
      fprintf(stderr,"ERROR: usage %s input_file_name\n",argv[0]);
      exit(-1);
    }
  freopen(argv[1],"r",stdin);
  int n,e,src;
  scanf("%d%d%d",&n,&e,&src);
  
  /*
    consume input in the form of an edge list for the graph
    example - u,v,w => (u,v) -> edge with vertices u and v; w -> weight of the edge
   */

  
  printf("initializing data structures\n");
  initialize(n,src);
  
  FOR(i,0,e)
    {
      int u,v,w;
      scanf("%d%d%d",&u,&v,&w);
      PAIR p(w,v);
      g[u].push_back(p);

    }

  printf("printing original graph\n\n");

  print_graph(n);

  printf("\ncomputing shortest paths\n");
  while(!q.empty())
    {
      set<PAIR>::iterator it = q.begin();
      PAIR p = *it;
      int u,v,w,du;

      du = p.first;
      u = p.second;
      
      q.erase(it);
      
      FOR(i,0,g[u].size())
	{
	  p = g[u][i];
	  w = p.first;
	  v = p.second;

	  if (d[v] > d[u] + w)
	    {
	      if (w != INT_MAX)
		{
		  it = q.find(p);
		  if (it != q.end())
		    {
		      q.erase(it);
		    }
		}
	        d[v] = d[u] + w;
	        q.insert(PAIR(d[v],v));
	    }
	  
	}


    }

  printf("\n\n printing shortest distances for each vertex (vertex -> shortest_distance)\n\n");
  print_shortest_distances(n);
  printf("\n\n");
  return 0;
}
