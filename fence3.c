/*
  ID: abacles1
  LANG: C
  TASK: fence3
*/

#include <stdio.h>
#include <math.h>

#define DELTA 0.01
#define MIN(A, B) (A<B ? A:B)
#define MAX(A, B) (A>B ? A:B)

double wire(int lines[150][4], int n, double x, double y)
{
  int a, b, i;
  double totdist = 0;
  for (i=0; i<n; i++)
    {
      if (lines[i][1] == lines[i][3])
	{
	  a = MIN(lines[i][0], lines[i][2]);
	  b = MAX(lines[i][0], lines[i][2]);
	  if (x < a)
	    totdist += hypot(a-x, lines[i][1]-y);
	  else if (x > b)
	    totdist += hypot(x-b, lines[i][1]-y);
	  else
	    totdist += fabs(lines[i][1] - y);
	}
      else
	{
	  a = MIN(lines[i][1], lines[i][3]);
	  b = MAX(lines[i][1], lines[i][3]);
	  if (y < a)
	    totdist += hypot(lines[i][0]-x, a-y);
	  else if (y > b)
	    totdist += hypot(lines[i][0]-x, y-b);
	  else
	    totdist += fabs(lines[i][0] - x);
	}
    }
  return totdist;
}

int main()
{
  FILE *fin = fopen("fence3.in", "r"), *fout = fopen("fence3.out", "w");
  int f, fences[150][4], i;
  double cx = 0, cy = 0, d, dx, dy, dbest, minwire = 30000, tmp;
  fscanf(fin, "%d", &f);
  for (i=0; i<f; i++)
    {
      fscanf(fin, "%d %d %d %d", &fences[i][0], &fences[i][1], &fences[i][2], &fences[i][3]);
      cx += fences[i][0] + fences[i][2];
      cy += fences[i][1] + fences[i][3];
    }
  cx /= 2*f;
  cy /= 2*f;
  minwire = wire(fences, f, cx, cy);
  while (1)
    {
      for (d=-DELTA, dbest=dx=dy=0; d<=DELTA; d+=2*DELTA)
	{
	  if ((tmp = wire(fences, f, cx+d, cy)) - minwire < dbest)
	    {
	      dx = d, dy = 0;
	      dbest = tmp - minwire;
	    }
	  if ((tmp = wire(fences, f, cx, cy+d)) - minwire < dbest)
	    {
	      dx = 0, dy = d;
	      dbest = tmp - minwire;
	    }
	}
      if (dbest == 0)
	break;
      cx += dx;
      cy += dy;
      minwire += dbest;
    }
  fprintf(fout, "%.1f %.1f %.1f\n", cx, cy, minwire);
  fclose(fin), fclose(fout);
}
