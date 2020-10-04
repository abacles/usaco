/*
  ID: abacles1
  LANG: C
  TASK: fc
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float x[10000], y[10000];
double midx, midy, perim;

int compar(const void *va, const void *vb)
{
  const int *a = (const int*)va, *b = (const int*)vb;
  double theta1 = atan2(y[*a]-midy, x[*a]-midx), theta2 = atan2(y[*b]-midy, x[*b]-midx);
  return theta1 == theta2 ? 0 : (theta1 < theta2 ? -1 : 1);
}

int convex(int x1, int y1, int x2, int y2)
{
  double theta1 = atan2(y1, x1), theta2 = atan2(y2, x2);
  return (theta2 > theta1 && theta2 < theta1 + M_PI) || (theta2 + 2*M_PI < theta1 + M_PI);
}

int main()
{
  FILE *in = fopen("fc.in", "r"), *out = fopen("fc.out", "w");
  int nspots, order[10000], fence[10000], flen, i, j;
  fscanf(in, "%d", &nspots);
  for(i=0;i<nspots;i++)
    fscanf(in, "%f %f", &x[i], &y[i]);
  for(i=midx=midy=0;i<nspots;i++)
    {
      midx += x[i] / nspots;
      midy += y[i] / nspots;
    }
  for(i=0;i<nspots;order[i]=i,i++);
  qsort(order, nspots, sizeof(int), compar);
  fence[0] = order[0], fence[1] = order[1];
  for(i=flen=2;i<nspots;i++)
    {
      for(;flen > 1 && !convex(x[fence[flen-1]]-x[fence[flen-2]],
			       y[fence[flen-1]]-y[fence[flen-2]],
			       x[order[i]]-x[fence[flen-1]],
			       y[order[i]]-y[fence[flen-1]]);flen--);
      fence[flen++] = order[i];
    }
  i = 0;
  do
    {
      j = 0;
      if(!convex(x[fence[flen-1]]-x[fence[flen-2]],
		 y[fence[flen-1]]-y[fence[flen-2]],
		 x[fence[i]]-x[fence[flen-1]],
		 y[fence[i]]-y[fence[flen-1]]))
	{
	  flen--;
	  j = 1;
	}
      if(!convex(x[fence[i]]-x[fence[flen-1]],
		 y[fence[i]]-y[fence[flen-1]],
		 x[fence[i+1]]-x[fence[i]],
		 y[fence[i+1]]-y[fence[i]]))
	{
	  i++;
	  j = 1;
	}
    } while(j);
  perim = hypot(x[fence[i]]-x[fence[flen-1]], y[fence[i]]-y[fence[flen-1]]);
  for(i++;i<flen;i++)
    perim += hypot(x[fence[i]]-x[fence[i-1]], y[fence[i]]-y[fence[i-1]]);
  fprintf(stdout, "%.2f\n", perim);
  fclose(in), fclose(out);
}
