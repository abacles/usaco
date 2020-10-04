/*
  ID: abacles1
  LANG: C
  TASK: fence8
*/

#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b)
{
  int ia = *(int*)a, ib = *(int*)b;
  return (ia == ib ? (0) : (ia < ib ? -1 : 1));
}

int makeable(int rails[], int r, int boards[], int i, int b, int waste, int extra)
{
  int tmp;
  if (!r)
    return 1;
  if (waste > extra)
    return 0;
  if (i == -1 || rails[r-1] != rails[r])
    i = 0;
  for (; i<b; i++)
    {
      if (rails[r-1] <= boards[i])
	{
	  boards[i] -= rails[r-1];
	  tmp = makeable(rails, r-1, boards, i, b, waste + (boards[i]<rails[0] ? boards[i]:0), extra);
	  boards[i] += rails[r-1];
	  if (tmp)
	    return 1;
	  else if (rails[r-1] == boards[i])
	    return 0;
	}
    }
  return 0;
}

int main()
{
  FILE *fin = fopen("fence8.in", "r"), *fout = fopen("fence8.out", "w");
  int n, r, boards[50], rails[1023], totboard = 0, railsum[1024], lf, rt, i;
  fscanf(fin, "%d", &n);
  for (i=0; i<n; fscanf(fin, "%d", &boards[i++]));
  for (i=0; i<n; totboard += boards[i++]);
  fscanf(fin, "%d", &r);
  for (i=0; i<r; fscanf(fin, "%d", &rails[i++]));
  qsort(rails, r, sizeof(int), cmp);
  for (railsum[0]=0, i=1; i<=r; i++)
    railsum[i] = railsum[i-1] + rails[i-1];
  for (lf=0, rt=r+1; lf < rt-1; )
    {
      i = (lf + rt) / 2;
      if (railsum[i] > totboard || !makeable(rails, i, boards, -1, n, 0, totboard-railsum[i]))
	rt = i;
      else
	lf = i;
    }
  fprintf(fout, "%d\n", lf);
  fclose(fin), fclose(fout);
}
