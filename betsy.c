/*
  ID: abacles1
  LANG: C
  TASK: betsy
*/

#include <stdio.h>
#include <string.h>

int sq[9][9], v[9][9] = {0}, rowfil[9] = {0}, colfil[9] = {0}, tot = 0, dead_ends = 0;

int sum(int a[], int start, int end)
{
  int s = 0;
  while (start < end)
    s += a[start++];
  return s;
}

int blanks(int n, int i, int j, int ci, int cj)
{
  int b = 0, d, o = 0;
  if (sq[i][j] || v[i][j])
    return 0;
  v[i][j] = 1;
  for (d=-1; d<=1; d+=2)
    {
      b += blanks(n, i+d, j, ci, cj);
      b += blanks(n, i, j+d, ci, cj);
      if (sq[i+d][j] && !(i+d == ci && j == cj))
	o++;
      if (sq[i][j+d] && !(i == ci && j+d == cj))
	o++;
    }
  if (o == 3 && !(i == n && j == 1))
    dead_ends++;
  return b + 1;
}

void tour(int n, int i, int j, int c)
{
  int d;
  if (i == n && j == 1 && c == n*n-1)
    {
      tot++;
      return;
    }
  if ((rowfil[i] == n && sum(rowfil, 1, i) < n*i) ||
      (colfil[j] == n && sum(colfil, j+1, n+1) < n*(n-j)))
    return;
  sq[i][j] = 1;
  rowfil[i]++;
  colfil[j]++;
  if (n*n - c <= 20)
    goto PROCEED;
  memset(v, 0, sizeof v);
  dead_ends = 0;
  if (blanks(n, n, 1, i, j) + c + 1 == n*n && !dead_ends)
  PROCEED:
    for (d=-1; d<=1; d+=2)
      {
	if (!sq[i][j+d])
	  if (!((d == -1 && n-colfil[j] == 1) || (d == 1 && n-colfil[j] == 0)))
	    tour(n, i, j+d, c+1);
	if (!sq[i+d][j])
	  if (!((d == 1 && n-rowfil[i] == 1) || (d == -1 && n-rowfil[i] == 0)))
	    tour(n, i+d, j, c+1);
      }
  sq[i][j] = 0;
  rowfil[i]--;
  colfil[j]--;
}

int main()
{
  FILE *fin = fopen("betsy.in", "r"), *fout = fopen("betsy.out", "w");
  int n, i, j;
  fscanf(fin, "%d", &n);
  for (i=0; i<9; i++)
    for (j=0; j<9; j++)
      sq[i][j] = 0;
  for (i=0; i<9; i++)
    sq[0][i] = sq[i][0] = sq[n+1][i] = sq[i][n+1] = 1;
  tour(n, 1, 1, 0);
  fprintf(fout, "%d\n", tot);
  fclose(fin), fclose(fout);
}
