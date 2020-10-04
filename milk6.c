/*
  ID: abacles1
  LANG: C
  TASK: milk6
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 2000000000

int origcost[32][32] = {0}, cost[32][32] = {0};

int min(int a, int b)
{
  return a < b ? a : b;
}

int flow(int src, int sink, int nc)
{
  int tflow = 0, flow[32], visited[32], prev[32], maxloc, pathcap, i, j;
  while(1)
    {
      for(i=0;i<nc;i++)
	{
	  visited[i] = flow[i] = 0;
	  prev[i] = -1;
	}
      flow[src] = INF;
      while(1)
	{
	  for(i=0,maxloc=-1;i<nc;i++)
	    {
	      if(!visited[i] && flow[i] && (maxloc<0 || flow[i] > flow[maxloc]))
		maxloc = i;
	    }
	  if(maxloc < 0 || maxloc == sink)
	    break;
	  visited[maxloc] = 1;
	  for(i=0;i<nc;i++)
	    {
	      if(flow[i] < min(flow[maxloc], cost[maxloc][i]))
		{
		  prev[i] = maxloc;
		  flow[i] = min(flow[maxloc], cost[maxloc][i]);
		}
	    }
	}
      if(maxloc < 0)
	break;
      pathcap = flow[sink];
      tflow += pathcap;
      for(i=sink;i!=src;i=prev[i])
	{
	  cost[prev[i]][i] -= pathcap;
	  cost[i][prev[i]] += pathcap;
	}
    }
  return tflow;
}

int compar(const void *a, const void *b)
{
  int *ca = (int*)a, *cb = (int*)b;
  if(ca[2] - cb[2])
    return ca[2] - cb[2];
  return ca[3] - cb[3];
}

int main()
{
  FILE *in = fopen("milk6.in", "r"), *out = fopen("milk6.out", "w");
  int nwhouses, ntrucks, trucks[1000][4], incut[1000] = {0}, i, j, k, l;
  fscanf(in, "%d %d", &nwhouses, &ntrucks);
  for(i=0;i<ntrucks;i++)
    {
      fscanf(in, "%d %d %d", &trucks[i][0], &trucks[i][1], &trucks[i][2]);
      cost[trucks[i][0]-1][trucks[i][1]-1] += trucks[i][2];
      trucks[i][3] = i;
    }
  memcpy(origcost, cost, sizeof cost);
  fprintf(out, "%d ", l=flow(0, nwhouses-1, nwhouses));
  memcpy(cost, origcost, sizeof cost);
  for(i=0;i<ntrucks;i++)
    cost[trucks[i][0]-1][trucks[i][1]-1]++;
  memcpy(origcost, cost, sizeof cost);
  fprintf(out, "%d\n", (k=flow(0, nwhouses-1, nwhouses)) - l);
  qsort(trucks, ntrucks, sizeof trucks[0], compar);
  for(i=0;i<ntrucks;i++)
    {
      memcpy(cost, origcost, sizeof cost);
      cost[trucks[i][0]-1][trucks[i][1]-1] -= trucks[i][2] + 1;      
      j = flow(0, nwhouses-1, nwhouses);
      if(k - j == trucks[i][2] + 1)
	{
	  incut[trucks[i][3]] = 1;
	  origcost[trucks[i][0]-1][trucks[i][1]-1] -= trucks[i][2] + 1;
	  k = j;
	}
    }
  for(i=0;i<ntrucks;i++)
    {
      if(incut[i])
	fprintf(out, "%d\n", i+1);
    }
  fclose(in), fclose(out);
}
