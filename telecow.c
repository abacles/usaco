/*
  ID: abacles1
  LANG: C
  TASK: telecow
*/

#include <stdio.h>

#define INF 0x7FFFFFFF
#define MIN(A, B) (A<B ? A:B)

int maxflow(int g[200][200], int n, int src, int sink)
{
  int flownet[200][200], prev[200], q[200], qr, qw, v, flow, totflow = 0, i, j;
  for(i=0;i<n;i++)
    {
      for(j=0;j<n;j++)
	flownet[i][j] = g[i][j];
    }
  while(1)
    {
      for(i=0;i<n;prev[i++]=-1);
      prev[src] = -2; qw = 0; qr = 0; q[qw++] = src;
      while(qr < qw)
	{
	  v = q[qr++];
	  for(i=0;i<n;i++)
	    {
	      if(flownet[v][i] > 0 && prev[i] == -1)
		{
		  prev[i] = v;
		  q[qw++] = i;
		}
	    }
	  if(prev[sink] != -1) break;
	}
      if(prev[sink] == -1) return totflow;
      for(i=sink,flow=INF;prev[i]>=0;i=prev[i])
	flow = MIN(flow, flownet[prev[i]][i]);
      for(i=sink;prev[i]>=0;i=prev[i])
	{
	  if(flownet[prev[i]][i] != INF) flownet[prev[i]][i] -= flow;
	  if(flownet[i][prev[i]] != INF) flownet[i][prev[i]] += flow;
	}
      totflow += flow;
    }
}

int main()
{
  FILE *fin = fopen("telecow.in", "r"), *fout = fopen("telecow.out", "w");
  int ncows, m, a, b, cownet[200][200] = {0}, mincut, u, v, i;
  fscanf(fin, "%d %d %d %d", &ncows, &m, &a, &b);
  for(i=0;i<ncows;i++)
    cownet[2*i][2*i+1] = 1;
  for(i=0;i<m;i++)
    {
      fscanf(fin, "%d %d", &u, &v);
      cownet[2*(u-1)+1][2*(v-1)] = INF;
      cownet[2*(v-1)+1][2*(u-1)] = INF;
    }
  mincut = maxflow(cownet, ncows*2, 2*(a-1)+1, 2*(b-1));
  fprintf(fout, "%d\n", mincut);
  for(i=0; i<ncows && mincut; i++)
    {
      cownet[2*i][2*i+1] = 0;
      if(maxflow(cownet, ncows*2, 2*(a-1)+1, 2*(b-1)) < mincut)
	fprintf(fout, "%d%c", i+1, --mincut ? ' ':'\n');
      else
	cownet[2*i][2*i+1] = 1;
    }
  fclose(fin); fclose(fout);
}
