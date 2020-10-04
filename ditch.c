/*
  ID: abacles1
  LANG: C
  TASK: ditch
*/

#include <stdio.h>

#define INF 10000001

int graph[200][200] = {0};

int min(int a,int b)
{
  return a < b ? a : b;
}

int flow(int nc)
{
  int tflow = 0,prev[200],cflow[200],visited[200],mflowloc,pathcap,i,j;
  while(1)
    {
      for(i=0;i<nc;i++)
	{
	  prev[i] = -1;
	  cflow[i] = visited[i] = 0;
	}
      cflow[0] = INF;
      while(1)
	{
	  for(mflowloc=-1,i=0;i<nc;i++)
	    {
	      if(!visited[i] && cflow[i]>0 && (mflowloc<0 || cflow[i] > cflow[mflowloc]))
		mflowloc = i;
	    }
	  if(mflowloc < 0 || mflowloc == nc-1) break;
	  visited[mflowloc] = 1;
	  for(i=0;i<nc;i++)
	    {
	      if(cflow[i] < min(cflow[mflowloc],graph[mflowloc][i]))
		{
		  prev[i] = mflowloc;
		  cflow[i] = min(cflow[mflowloc],graph[mflowloc][i]);
		}
	    }
	}
      if(mflowloc < 0) break;
      pathcap = cflow[nc-1];
      tflow += pathcap;
      for(i=nc-1;i!=0;i=j)
	{
	  j = prev[i];
	  graph[j][i] -= pathcap;
	  graph[i][j] += pathcap;
	}
    }
  return tflow;
}

int main()
{
  FILE *in = fopen("ditch.in","r"),*out = fopen("ditch.out","w");
  int ditches_count,isc_count,i,a,b,cap;
  fscanf(in,"%d %d",&ditches_count,&isc_count);
  for(i=0;i<ditches_count;i++)
    {
      fscanf(in,"%d %d %d",&a,&b,&cap);
      graph[a-1][b-1] += cap;
    }
  fclose(in);
  fprintf(out,"%d\n",flow(isc_count));
  fclose(out);
}
