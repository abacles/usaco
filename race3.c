/*
  ID: abacles1
  LANG: C
  TASK: race3
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FOUT out

struct edge
{
  int cn;
  struct edge *next;
};

struct edge *graph[50];
char visited[50];

struct edge *newedge(int c)
{
  struct edge *new = malloc(sizeof(struct edge));
  new->cn = c;
  new->next = NULL;
  return new;
}

void freenode(struct edge *n)
{
  if(n->next)
    freenode(n->next);
  free(n);
}

int reachable(int from, int to, int avoid)
{
  struct edge *e;
  visited[from] = 1;
  for(e=graph[from]->next;e;e=e->next)
    {
      if(e->cn != avoid && !visited[e->cn] &&
	 (e->cn == to || reachable(e->cn, to, avoid)))
	return 1;
    }
  return 0;
}

int cansplit(int s, int nc)
{
  int i, vd = 0;
  struct edge *e;
  for(i=0;i<nc;i++)
    {
      if(i != s &&
	 (memset(visited, 0, sizeof visited), !reachable(i, s, -1)) &&
	 (memset(visited, 0, sizeof visited), !reachable(s, i, -1)))
        return 0;
    }
  memset(visited, 0, sizeof visited), reachable(s, -1, -1);
  for(i=0;i<nc;i++)
    {
      for(e=graph[i]->next;e;e=e->next)
	{
	  if(i != s && e->cn != s && visited[i] != visited[e->cn])
	    return 0;
	}
      vd += visited[i];
    }
  return vd < nc;
}

int main()
{
  FILE *in = fopen("race3.in", "r"), *out = fopen("race3.out", "w");
  struct edge *tails[50];
  int nnodes = 0, bottleneck[50], nbn = 0, split[50], ns = 0, i, j;
  do
    {
      graph[nnodes] = tails[nnodes] = newedge(-1);
      while(fscanf(in, "%d", &j), j >= 0)
	tails[nnodes] = tails[nnodes]->next = newedge(j);
    } while(graph[nnodes] != tails[nnodes++]);
  for(i=1;i<nnodes-1;i++)
    {
      if(memset(visited, 0, sizeof visited), !reachable(0, nnodes-1, i))
	bottleneck[nbn++] = i;
    }
  fprintf(FOUT, "%d%c", nbn, nbn?' ':'\n');
  for(i=0;i<nbn;i++)
    {
      fprintf(FOUT, "%d%c", bottleneck[i], i!=nbn-1?' ':'\n');
      if(bottleneck[i] > 0 && bottleneck[i] < nnodes-1 &&
	 cansplit(bottleneck[i], nnodes))
	split[ns++] = bottleneck[i];
    }
  fprintf(FOUT, "%d%c", ns, ns?' ':'\n');
  for(i=0;i<ns;i++)
    fprintf(FOUT, "%d%c", split[i], i!=ns-1?' ':'\n');
  for(i=0;i<nnodes;i++)
    freenode(graph[i]);
  fclose(in), fclose(out);
}
