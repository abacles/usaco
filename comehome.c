/*
  ID: abacles1
  LANG: C
  TASK: comehome
*/

#include <stdio.h>

#define INF 100000000

int dist[52][52];

int id(char c)
{
  if(c >= 'a' && c <= 'z')
    return c-'a';
  return 26 + c-'A';
}

char ch(int i)
{
  return "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"[i];
}

void floyd_warshall()
{
  int k,i,j;
  for(k=0;k<52;k++)
    {
      for(i=0;i<52;i++)
	{
	  for(j=0;j<52;j++)
	    {
	      if(dist[i][k] + dist[k][j] < dist [i][j])
		dist[i][j] = dist[i][k] + dist[k][j];
	    }
	}
    }
}

int main()
{
  FILE *in,*out;
  int paths;
  char a,b;
  int d;
  int i,j,best = INF;
  in = fopen("comehome.in","r");
  fscanf(in,"%d",&paths);
  fgetc(in);
  for(i=0;i<52;i++)
    {
      for(j=0;j<52;j++)
	dist[i][j] = INF;
    }
  for(i=0;i<paths;i++)
    {
      fscanf(in,"%c %c %d",&a,&b,&d);
      fgetc(in);
      if(a != b && dist[id(a)][id(b)] > d)
	dist[id(a)][id(b)] = dist[id(b)][id(a)] = d;
    }
  fclose(in);

  floyd_warshall();

  for(i=26;i<51;i++)
    {
      if(best == INF || dist[i][id('Z')] < dist[best][id('Z')])
	best = i;
    }
  
  out = fopen("comehome.out","w");
  fprintf(out,"%c %d\n",ch(best),dist[best][id('Z')]);
  fclose(out);
  
  return 0;
}
