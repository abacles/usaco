/*
  ID: abacles1
  LANG: C
  TASK: schlnet
*/

#include <stdio.h>
#include <stdlib.h>

struct vtx
{
  int indeg, outdeg, incap, outcap, *in, *out, visited, scc;
};

void init(struct vtx *v)
{
  v->indeg = v->outdeg = 0;
  v->incap = v->outcap = 1;
  v->in = malloc(sizeof(int)); v->out = malloc(sizeof(int));
  v->scc = -1;
}

void destroy(struct vtx v)
{
  free(v.in);
  free(v.out);
}

void append(int **list, int *len, int *cap, int elem)
{
  if(*len == *cap)
    *list = realloc(*list, sizeof(int) * ((*cap)*=2));
  (*list)[(*len)++] = elem;
}

void dfs(struct vtx g[], int v, int next)
{
  int i;
  g[v].scc = next;
  for(i=0;i<g[v].outdeg;i++)
    {
      if(g[(g[v].out)[i]].scc == -1)
	dfs(g, (g[v].out)[i], next);
    }
}

void rdfs(struct vtx g[], int v, int post[], int *next)
{
  int i;
  g[v].visited = 1;
  for(i=0;i<g[v].indeg;i++)
    {
      if(!g[(g[v].in)[i]].visited)
	rdfs(g, (g[v].in)[i], post, next);
    }
  post[(*next)++] = v;
}

int kosaraju(struct vtx g[], int n)
{
  int post[100], i, k = 0;
  for(i=0;i<n;g[i++].visited=0);
  for(i=0;i<n;i++)
    {
      if(!g[i].visited)
	rdfs(g, i, post, &k);
    }
  for(k=0,i=n-1;i>=0;i--)
    {
      if(g[post[i]].scc == -1)
	dfs(g, post[i], k++);
    }
  return k;
}

void srcsink(struct vtx g[], int n, int ncomp, FILE *fout)
{
  int meta[100][100] = {0}, meta_indeg[100] = {0}, meta_outdeg[100] = {0};
  int u, v, nsink, nsrc, i, j;
  for(i=0;i<n;i++)
    {
      for(j=0;j<g[i].outdeg;j++)
	{
	  u = g[i].scc; v = g[(g[i].out)[j]].scc;
	  if(u != v && !meta[u][v])
	    {
	      meta[u][v] = 1;
	      meta_outdeg[u]++; meta_indeg[v]++;
	    }
	}
    }
  for(i=0;i<ncomp;i++)
    {
      nsink += !(meta_outdeg[i]);
      nsrc += !(meta_indeg[i]);
    }
  if(ncomp == 1)
    fprintf(fout, "%d\n0\n", nsrc);
  else
    fprintf(fout, "%d\n%d\n", nsrc, nsrc>nsink ? nsrc:nsink);
}

int main()
{
  FILE *fin = fopen("schlnet.in", "r"), *fout = fopen("schlnet.out", "w");
  struct vtx g[100];
  int n, v, ncomponents, i;
  fscanf(fin, "%d", &n);
  for(i=0;i<n;init(&g[i++]));
  for(i=0;i<n;i++)
    {
      while(fscanf(fin, "%d", &v), v)
	{
	  append(&(g[i].out), &(g[i].outdeg), &(g[i].outcap), v-1);
	  append(&(g[v-1].in), &(g[v-1].indeg), &(g[v-1].incap), i);
	}
    }
  ncomponents = kosaraju(g, n);
  srcsink(g, n, ncomponents, fout);
  for(i=0;i<n;destroy(g[i++]));
  fclose(fin), fclose(fout);
}
