#include<stdio.h>
#include<vector>
#include<set>
#include<limits.h>
#include<fcntl.h>
#include<stdlib.h>

using namespace std;


typedef pair<int,int> pii;
typedef vector<pii> vpi;
typedef vector<vpi> vvpi;
typedef vector<int> vi;

#define FOR(i,x,n) for(int i=x;i<n;i++)
#define init_source(source,d) { d[source] = 0; }
/*
  function to print the graph
 */
void print_graph(vvpi &g)
{
  FOR(i,0,g.size())
    {
      FOR(j,0,g[i].size())
	{
	  printf("%d -> %d : [ %d ] \n",i,g[i][j].first,g[i][j].second);
	}
      
    }
}


/*
  computing shortest path in a graph using Dijkstra's Algorithm
  assuming node 0 as the root
 */
void compute_shortest_path(vvpi &g,vi &d,int source)
{
  // create a priority queue
  set<pii> q;

  /* initialize priority queue and minimum distance array
     first entry stores the distance of node i and second entry stores
   node i
  */
  q.insert(pii(d[source],source));
  

  while(!q.empty())
    {
      // extract min from priority queue
      pii min_node_pair = *q.begin();
      int min_node = min_node_pair.second;
      int w = min_node_pair.first;
      q.erase(q.begin());
      // iterate over all nodes adjacent to min_node
      FOR(i,0,g[min_node].size())
	{

	  pii p = g[min_node][i];
	  if (d[p.first] > w + p.second)
	    {
	      /*
		this node was already inserted into the priority queue
		so we remove it
	       */
	      if (d[p.first] != INT_MAX)
		{
		  set<pii>::iterator it = q.find(p);
		  if (it != q.end())
		    {
		      q.erase(q.find(p));
		    }
		  
		}
	      d[p.first] = d[min_node] + p.second;
	      q.insert(pii(d[p.first],p.first));
	    }
	}
    }
  
}




int main(int argc,char *argv[])
{
  if (argc != 3)
    {
      fprintf(stderr,"ERROR: use <executable> number_vertices(n)  source_index (o to n)\n");
      exit(0);
    }
  
  freopen("ip.txt","r",stdin);
  int n,m, a,b,c, source;
  n = atoi(argv[1]);
  source = atoi(argv[2]);
  scanf("%d",&m);

  if (n >= INT_MAX || source >= INT_MAX || n<= 0 || source < 0)
    {
      fprintf(stderr,"ERROR : number of vertices should be positive and index should be non-negative\n");
      exit(0);
    }
  
  
  vvpi g;
  // small memory optimization while using vectors in C++
  g.resize(n);
  
  // array of distances from the source
  vi d(n,INT_MAX);
  
  FOR(i,0,m)
    {
      //input source_vertex destination_vertex edge_weight
      scanf("%d%d%d",&a,&b,&c);
      // since the graph is undirected we add 2 entries
      g[a].push_back(pii(b,c));
      //      g[b].push_back(pii(a,c));
    }
  
  //initialize source values
  init_source(source,d);

  print_graph(g);
  printf("\n\n");
  compute_shortest_path(g,d,source);
  

  /*
    print the array of distances from the source
   */
  FOR(i,0,n)
    {
      printf("%d %d\n",i,d[i]);
    }

  return 0;
}
