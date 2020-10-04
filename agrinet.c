/*
  ID: abacles1
  LANG: C
  TASK: agrinet
*/

#include <stdio.h>
#include <stdlib.h>

#define INF 100001

int **adjmat;

int prim(int ncount)
{
  int *dist = malloc(sizeof(int)*ncount),treesize = 1,treecost = 0,i,best;
  for(i=0;i<ncount;i++)
    dist[i] = adjmat[0][i];
  while(treesize < ncount)
    {
      for(i=0,best=-1;i<ncount;i++)
	{
	  if(dist[i] && (best == -1 || dist[i] < dist[best]))
	    best = i;
	}
      treesize++;
      treecost += dist[best];
      dist[best] = 0;
      for(i=0;i<ncount;i++)
	{
	  if(adjmat[best][i] < dist[i])
	    dist[i] = adjmat[best][i];
	}
    }
  free(dist);
  return treecost;
}

int main()
{
  FILE *in = fopen("agrinet.in","r"),*out = fopen("agrinet.out","w");
  int farms;
  int i,j;
  fscanf(in,"%d",&farms);
  adjmat = malloc(sizeof(int*)*farms);
  for(i=0;i<farms;i++)
    {
      adjmat[i] = malloc(sizeof(int)*farms);
      for(j=0;j<farms;j++)
	fscanf(in,"%d",&adjmat[i][j]);
    }
  fclose(in);
  fprintf(out,"%d\n",prim(farms));
  fclose(out);
  for(i=0;i<farms;i++)
    free(adjmat[i]);
  free(adjmat);
}
