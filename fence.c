/*
  ID: abacles1
  LANG: C
  TASK: fence
*/

#include <stdio.h>
#include <stdlib.h>

struct edge
{
  int connect;
  int id;
  struct edge *next;
} *graph[1025];

int seq[1025];
int seqlen = 0;

struct edge *addedge(int c,int i,struct edge *np)
{
  struct edge *new = malloc(sizeof(struct edge));
  new->connect = c;
  new->id = i;
  new->next = np;
  return new;
}

void fleury(int node)
{
  int onode,path;
  struct edge *e,*temp;
  if(!graph[node]->next)
    seq[seqlen++] = node + 1;
  else
    {
      for(e=graph[node]->next;graph[node]->next;e=graph[node]->next)
	{
	  onode = e->connect;
	  path = e->id;
	  temp = e->next;
	  free(e);
	  graph[node]->next = temp;
	  for(e=graph[onode];e->next;e=e->next)
	    {
	      if(e->next->connect == node)
		{
		  temp = e->next;
		  e->next = e->next->next;
		  free(temp);
		  break;
		}
	    }
	  fleury(onode);
	}
      seq[seqlen++] = node + 1;
    }
}

int main()
{
  FILE *in = fopen("fence.in","r"),*out = fopen("fence.out","w");
  int edgecount,nodecount;
  struct edge *temp;
  int connecting[1025];
  int i,j,k;
  fscanf(in,"%d",&edgecount);
  nodecount = edgecount + 1;
  for(i=0;i<1025;i++)
    {
      graph[i] = addedge(-1,-1,NULL);
      connecting[i] = 0;
    }
  for(i=0;i<edgecount;i++)
    {
      fscanf(in,"%d %d",&j,&k);
      for(temp=graph[j-1];temp->next && temp->next->connect<k-1;temp=temp->next) {}
      temp->next = addedge(k-1,i+1,temp->next);
      connecting[k-1]++;
      for(temp=graph[k-1];temp->next && temp->next->connect<j-1;temp=temp->next) {}
      temp->next = addedge(j-1,i+1,temp->next);
      connecting[j-1]++;
    }
  /*for(i=0;i<nodecount;i++)
    {
      printf("%d\n",connecting[i]);
      for(temp=graph[i]->next;temp;temp=temp->next)
	{
	  printf("%d - %d\n",i+1,temp->connect+1);
	}
	}*/
  for(i=0;i<1025;i++)
    {
      if(connecting[i]%2 == 1)
	break;
    }

  fleury(i==1025?0:i);
  for(i=seqlen-1;i>=0;i--)
    fprintf(out,"%d\n",seq[i]);
  fclose(out);
  
  for(i=0;i<1025;i++)
    free(graph[i]);
}
