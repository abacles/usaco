/*
  ID: abacles1
  LANG: C
  TASK: bigbrn
*/

#include <stdio.h>

int min(int a, int b, int c)
{
  if(a <= b && a <= c) return a;
  else if(b <= a && b <= c) return b;
  return c;
}

int main()
{
  FILE *fin = fopen("bigbrn.in", "r"), *fout = fopen("bigbrn.out", "w");
  int n, ntrees, map[1000][1000], a, b, max = 0, i, j;
  fscanf(fin, "%d %d", &n, &ntrees);
  for(i=0;i<n;i++)
    {
      for(j=0;j<n;j++)
	map[i][j] = (i && j) ? -1:1;
    }
  for(i=0;i<ntrees;i++)
    {
      fscanf(fin, "%d %d", &a, &b);
      map[a-1][b-1] = 0;
    }
  for(i=0;i<n;i++)
    {
      for(j=0;j<n;j++)
	{
	  if(map[i][j] == -1)
	    map[i][j] = min(map[i-1][j-1], map[i-1][j], map[i][j-1]) + 1;
	  if(map[i][j] > max)
	    max = map[i][j];
	}
    }
  fprintf(fout, "%d\n", max);
}
