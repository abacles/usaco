/*
 ID: abacles1
 LANG: C
 TASK: packrec
 */

#include <stdio.h>
#include <stdlib.h>

int min(int a, int b) { return a<b ? a:b; }
int max(int a, int b) { return a>b ? a:b; }

int hhh(int rect[4][2], int *w, int *h) // diagram 1
{
  *w = rect[0][0]+rect[1][0]+rect[2][0]+rect[3][0];
  *h = max(max(max(rect[0][1], rect[1][1]), rect[2][1]), rect[3][1]);
  return (*w) * (*h);
}

int hhv(int rect[4][2], int *w, int *h) // diagram 2
{
  *w = max(rect[0][0]+rect[1][0]+rect[2][0], rect[3][0]);
  *h = max(max(rect[0][1], rect[1][1]), rect[2][1]) + rect[3][1];
  return (*w) * (*h);
}

int hvh1(int rect[4][2], int *w, int *h) // diagram 4
{
  *w = rect[0][0] + max(rect[1][0], rect[2][0]) + rect[3][0];
  *h = max(max(rect[0][1], rect[3][1]), rect[1][1]+rect[2][1]);
  return (*w) * (*h);
}

int hvh2(int rect[4][2], int *w, int *h) // diagram 3
{
  *w = rect[3][0] + max(rect[0][0]+rect[1][0], rect[2][0]);
  *h = max(rect[2][1] + max(rect[0][1], rect[1][1]), rect[3][1]);
  return (*w) * (*h);
}

int hvv1(int rect[4][2], int *w, int *h) // diagram 5
{
  *w = max(rect[0][0]+rect[1][0], max(rect[2][0], rect[3][0]));
  *h = max(rect[0][1], rect[1][1]) + rect[2][1] + rect[3][1];
  return (*w) * (*h);
}

int hvv2(int rect[4][2], int *w, int *h) // diagram 6
{
  *w = max(max(rect[0][0]+rect[1][0], rect[1][0]+rect[2][0]), rect[2][0]+rect[3][0]);
  *h = max(max(rect[0][1]+rect[2][1], rect[0][1]+rect[3][1]), rect[1][1]+rect[3][1]);
  return (*w) * (*h);
}

int (*f[6])(int[4][2], int *, int *) = {hhh, hhv, hvh1, hvh2, hvv1, hvv2};
int x[4], y[4], r[4][2], v[4], minpack = 10000, packings[3000][2], pc = 0;

void pack(int p)
{
  int i, w, h, temp, j;
  if (p == 4)
  {
    for (i=0; i<6; i++)
    {
      if ((temp = (*f[i])(r, &w, &h)) <= minpack)
      {
        minpack = temp;
        packings[pc][0] = min(w, h);
        packings[pc++][1] = max(w, h);
      }
    }
    return;
  }
  for (i=0; i<4; i++)
  {
    if (!v[i])
    {
      v[i] = 1;
      r[p][0] = x[i], r[p][1] = y[i];
      pack(p+1);
      r[p][0] = y[i], r[p][1] = x[i];
      pack(p+1);
      v[i] = 0;
    }
  }
}

int cmp(const void *a, const void *b)
{
  int *x = ((int *)a), *y = ((int *)b);
  if (x[0] != y[0])
    return x[0]<y[0] ? -1:1;
  if (x[1] != y[1])
    return x[1]<y[1] ? -1:1;
  return 0;
}

int main()
{
  FILE *fin = fopen("packrec.in", "r"), *fout = fopen("packrec.out", "w");
  int i;
  for (i=0; i<4; i++)
    fscanf(fin, "%d %d", &x[i], &y[i]);
  pack(0);
  fprintf(fout, "%d\n", minpack);
  qsort(packings, pc, sizeof(int)*2, cmp);
  for (i=0; i<pc; i++)
  {
    if (packings[i][0] * packings[i][1] == minpack && (i == 0 || packings[i][0] != packings[i-1][0] || packings[i][1] != packings[i-1][1]))
      fprintf(fout, "%d %d\n", packings[i][0], packings[i][1]);
  }
  fclose(fin), fclose(fout);
}
