/*
  ID: abacles1
  LANG: C
  TASK: fence6
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX(A,B) (A>B?A:B)
#define MIN(A,B) (A<B?A:B)
#define INF 100000

struct edge
{
  int cn,wt;
  struct edge *next;
};

struct edge *graph[100];

struct edge *newedge(int c,int w)
{
  struct edge *new = malloc(sizeof(struct edge));
  new->cn = c;
  new->wt = w;
  new->next = NULL;
  return new;
}
void freeedge(struct edge *e)
{
  if(e->next) freeedge(e->next);
  free(e);
}

int getmin(int n[100],int len)
{
  int mindex = -1,i;
  for(i=0;i<len;i++)
    if(n[i] >= 0 && (n[i] < n[mindex] || mindex < 0)) mindex = i;
  return mindex;
}

int dijkstra(int sn,int en,int nc)
{
  int dist[100],n,visited,i,j;
  struct edge *e;
  for(i=0;i<nc;i++) dist[i] = INF;
  dist[sn] = 0;
  for(visited=0;visited<nc;visited++)
    {
      n = getmin(dist,nc);
      for(e=graph[n]->next;e;e=e->next)
	{
	  if((n==sn && e->cn==en) || (n==en && e->cn==sn))
	    continue;
	  if(dist[e->cn] > dist[n] + e->wt)
	    dist[e->cn] = dist[n] + e->wt;
	}
      dist[n] = -dist[n] - 1;
    }
  return -(dist[en] + 1);
}

int main()
{
  FILE *in = fopen("fence6.in","r"),*out = fopen("fence6.out","w");
  int ec,nmap[10000],nextid = 0,len[100],id,l,lc,rc,lcs[8],rcs[8],m,m2,i,j,lid[100],rid[100];
  struct edge *temp;
  fscanf(in,"%d",&ec);
  for(i=0;i<10000;i++) nmap[i] = -1;
  for(i=0;i<100;i++) graph[i] = newedge(-1,-1);
  for(i=0;i<ec;i++)
    {
      fscanf(in,"%d %d %d %d",&id,&l,&lc,&rc),id--;
      len[i] = l;
      for(m=id,m2=-1,j=0;j<lc;j++)
	{
	  fscanf(in,"%d",&lcs[j]),lcs[j]--;
	  if(lcs[j] > m) m2 = m,m = lcs[j];
	  else if(lcs[j] > m2) m2 = lcs[j];
	}
      lid[i] = m * 100 + m2;
      if(nmap[lid[i]] == -1) nmap[lid[i]] = nextid++;
      for(m=id,m2=-1,j=0;j<rc;j++)
	{
	  fscanf(in,"%d",&rcs[j]),rcs[j]--;
	  if(rcs[j] > m) m2 = m,m = rcs[j];
	  else if(rcs[j] > m2) m2 = rcs[j];
	}
      rid[i] = m * 100 + m2;
      if(nmap[rid[i]] == -1) nmap[rid[i]] = nextid++;
      for(temp=graph[nmap[lid[i]]];temp->next;temp=temp->next);
      temp->next = newedge(nmap[rid[i]],len[i]);
      for(temp=graph[nmap[rid[i]]];temp->next;temp=temp->next);
      temp->next = newedge(nmap[lid[i]],len[i]);
    }
  fclose(in);
  for(m=INF,i=0;i<ec;i++)
    {
      j = dijkstra(nmap[lid[i]],nmap[rid[i]],nextid) + len[i];
      m = MIN(m,j);
    }
  fprintf(out,"%d\n",m);
  fclose(out);
  for(i=0;i<100;i++) freeedge(graph[i]);
}
