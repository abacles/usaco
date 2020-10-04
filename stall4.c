/*
 ID: abacles1
 LANG: C
 TASK: stall4
 */

#include <stdio.h>

#define INF 10000

int graph[402][402];

int min(int a, int b)
{
  return a < b ? a : b;
}

int flow(int nc)
{
  int tflow = 0, prev[402], cflow[402], visited[402], mflowloc, pathcap, i, j;
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
        if(cflow[i] < min(cflow[mflowloc], graph[mflowloc][i]))
        {
          prev[i] = mflowloc;
          cflow[i] = min(cflow[mflowloc], graph[mflowloc][i]);
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
  FILE *in = fopen("stall4.in","r"), *out = fopen("stall4.out","w");
  int cc, sc, gsc, gs, i, j;
  fscanf(in,"%d %d",&cc,&sc);
  for(i=0;i<cc;i++) graph[0][1+i] = 1;
  for(i=cc;i<cc+sc;i++) graph[1+i][1+cc+sc] = 1;
  for(i=0;i<cc;i++)
  {
    fscanf(in,"%d",&gsc);
    for(j=0;j<gsc;j++)
    {
      fscanf(in,"%d",&gs);
      graph[1+i][cc+gs] = 1;
    }
  }
  fprintf(out,"%d\n",flow(cc+sc+2));
  fclose(in), fclose(out);
}
