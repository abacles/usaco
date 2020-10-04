/*
ID: abacles1
LANG: C
TASK: butter
*/

#include <stdio.h>
#include <stdlib.h>

#define INF 100000000

struct lnode
{
  int a,w;
  struct lnode *next;
};

struct hnode
{
  int d,id;
};

struct lnode **adjlist;
int *withcow;
struct hnode *distheap;
int *locinheap;
int hlen = 0;

struct lnode *lladd(int connect,int weight)
{
  struct lnode *new = malloc(sizeof(struct lnode));
  new->a = connect;
  new->w = weight;
  new->next = NULL;
  return new;
}
void llfree(struct lnode *alist)
{
  struct lnode *next;
  while(alist)
    {
      next = alist->next;
      free(alist);
      alist = next;
    }
}

int lchild(int n)
{
  return 2*n + 1;
}
int rchild(int n)
{
  return 2*n + 2;
}
int parent(int n)
{
  return (n-1) / 2;
}

void heapswap(int pa,int pb)
{
  int temp;
  locinheap[distheap[pa].id] = pb;
  locinheap[distheap[pb].id] = pa;
  temp = distheap[pb].d;
  distheap[pb].d = distheap[pa].d;
  distheap[pa].d = temp;
  temp = distheap[pb].id;
  distheap[pb].id = distheap[pa].id;
  distheap[pa].id = temp;
}
int siftdown(int pos)
{
  int (*cfunc)(int);
  while((lchild(pos) < hlen && distheap[lchild(pos)].d < distheap[pos].d) ||
	(rchild(pos) < hlen && distheap[rchild(pos)].d < distheap[pos].d))
    {
      if(rchild(pos) >= hlen ||
	 (lchild(pos) < hlen && distheap[lchild(pos)].d < distheap[rchild(pos)].d))
	cfunc = lchild;
      else
	cfunc = rchild;
      heapswap(pos,cfunc(pos));
      pos = cfunc(pos);
    }
  return pos;
}
int heaprm(int pos)
{
  int old = distheap[pos].id;
  heapswap(pos,--hlen);
  siftdown(pos);
  return old;
}
int heapchange(int pos,int newval)
{
  int temp;
  distheap[pos].d = newval;
  while(distheap[parent(pos)].d > distheap[pos].d)
    {
      heapswap(pos,parent(pos));
      pos = parent(pos);
    }
  return pos;
}

int dijkstra(int ncount,int source)
{
  int i,j,node,cowtravel = 0;
  struct lnode *edge;
  for(i=0;i<ncount;i++)
    {
      distheap[i].d = INF;
      distheap[i].id = i;
      locinheap[i] = i;
    }
  hlen = ncount;
  heapchange(source,0);
  while(hlen > 0)
    {
      j = distheap[0].d;
      node = heaprm(0);
      for(edge=adjlist[node]->next;edge;edge=edge->next)
	{
	  if(locinheap[edge->a] < hlen && 
	    j + edge->w < distheap[locinheap[edge->a]].d)
	    heapchange(locinheap[edge->a],j + edge->w);
	}
    }
  for(i=0;i<ncount;i++)
    cowtravel += distheap[i].d * withcow[distheap[i].id];
  return cowtravel;
}

int main()
{
  FILE *in = fopen("butter.in","r"),*out = fopen("butter.out","w");
  int cows,pastures,paths;
  struct lnode *temp;
  int i,j,k,l,min = INF;
  fscanf(in,"%d %d %d",&cows,&pastures,&paths);
  withcow = malloc(sizeof(int)*pastures);
  for(i=0;i<pastures;i++)
    withcow[i] = 0;
  for(i=0;i<cows;i++)
    {
      fscanf(in,"%d",&j);
      withcow[j-1]++;
    }
  adjlist = malloc(sizeof(struct lnode*)*pastures);
  for(i=0;i<pastures;i++)
    {
      adjlist[i] = malloc(sizeof(struct lnode));
      adjlist[i]->next = NULL;
    }
  distheap = malloc(sizeof(struct hnode)*pastures);
  locinheap = malloc(sizeof(int)*pastures);
  for(i=0;i<paths;i++)
    {
      fscanf(in,"%d %d %d",&j,&k,&l);
      for(temp=adjlist[j-1];temp->next;temp=temp->next) {}
      temp->next = lladd(k-1,l);
      for(temp=adjlist[k-1];temp->next;temp=temp->next) {}
      temp->next = lladd(j-1,l);
    }
  fclose(in);

  for(i=0;i<pastures;i++)
    {
      k = dijkstra(pastures,i);
      min = k < min? k : min;
    }

  fprintf(out,"%d\n",min);
  fclose(out);
  
  free(withcow);
  for(i=0;i<pastures;i++)
    llfree(adjlist[i]);
  free(adjlist);
  free(distheap);
  free(locinheap);
}
