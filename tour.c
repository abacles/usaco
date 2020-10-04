/*
  ID: abacles1
  LANG: C
  TASK: tour
*/

#include <stdio.h>
#include <string.h>

struct city
{
  int degree, flights[100];
};

int tour(struct city map[], int n)
{
  int dp[100][100] = {0}, maxvisit = 1, i, j, p, k;
  dp[0][0] = 1;
  for(i=0;i<n;i++)
    {
      for(j=i+1;j<n;j++)
	{
	  for(k=0;k<map[j].degree;k++)
	    {
	      p = (map[j].flights)[k];
	      if(p < j && dp[i][p] && dp[i][j] < dp[i][p]+1)
		dp[i][j] = dp[j][i] = dp[i][p] + 1;
	    }
	}
    }
  for(i=0;i<n-1;i++)
    {
      for(j=0; j<map[i].degree && (map[i].flights)[j]!=n-1; j++);
      if(j < map[i].degree && dp[i][n-1] > maxvisit)
	maxvisit = dp[i][n-1];
    }
  return maxvisit;
}

int main()
{
  FILE *in = fopen("tour.in", "r"), *out = fopen("tour.out", "w");
  int ncities, nflights, a, b, i, j;
  char cities[100][15], u[15], v[15];
  struct city canada[100];
  fscanf(in, "%d %d", &ncities, &nflights);
  for(i=0;i<ncities;canada[i++].degree=0)
    fscanf(in, "%s", cities[i]);
  for(i=0;i<nflights;i++)
    {
      fscanf(in, "%s %s", u, v);
      for(j=0;j<ncities;j++)
	{
	  if(!strcmp(u, cities[j])) a = j;
	  if(!strcmp(v, cities[j])) b = j;
	}
      canada[a].flights[(canada[a].degree)++] = b;
      canada[b].flights[(canada[b].degree)++] = a;
    }
  fprintf(out, "%d\n", tour(canada, ncities));
}
