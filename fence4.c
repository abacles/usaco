/*
  ID: abacles1
  LANG: C
  TASK: fence4
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DELTA 0.000001

long long zxprod(int ux, int uy, int vx, int vy)
{
  return ux*vy - uy*vx;
}

int opposite(int p1[2], int p2[2], int l1[2], int l2[2])
{
  return (zxprod(l2[0]-l1[0], l2[1]-l1[1], p1[0]-l1[0], p1[1]-l1[1]) *
	  zxprod(l2[0]-l1[0], l2[1]-l1[1], p2[0]-l1[0], p2[1]-l1[1])) < 0;
}

int intersect(int a1[2], int a2[2], int b1[2], int b2[2])
{
  return opposite(a1, a2, b1, b2) && opposite(b1, b2, a1, a2);
}

double fzxprod(double ux, double uy, double vx, double vy)
{
  return ux*vy - uy*vx;
}

int fopposite(double p1[2], double p2[2], double l1[2], double l2[2])
{
  double x1 = fzxprod(l2[0]-l1[0], l2[1]-l1[1], p1[0]-l1[0], p1[1]-l1[1]);
  double x2 = fzxprod(l2[0]-l1[0], l2[1]-l1[1], p2[0]-l1[0], p2[1]-l1[1]);
  if ((-DELTA <= x1 && x1 <= DELTA) || (-DELTA <= x2 && x2 <= DELTA))
    return 1;
  return x1 * x2 < 0;
}

int fintersect(int ia1[2], double a2[2], double b1[2], double b2[2])
{
  double a1[2];
  a1[0] = ia1[0], a1[1] = ia1[1];
  /*if ((a1[0] == b1[0] && a1[1] == b1[1]) ||
      (a1[0] == b2[0] && a1[1] == b2[1]) ||
      (a2[0] == b1[0] && a2[1] == b1[1]) ||
      (a2[0] == b2[0] && a2[1] == b2[1]))
      return 1;*/
  return fopposite(a1, a2, b1, b2) && fopposite(b1, b2, a1, a2);
}

int spc_oppo(int p1[2], double p2[2], double l1[2], double l2[2])
{
  double x1 = fzxprod(l2[0]-l1[0], l2[1]-l1[1], p1[0]-l1[0], p1[1]-l1[1]);
  double x2 = fzxprod(l2[0]-l1[0], l2[1]-l1[1], p2[0]-l1[0], p2[1]-l1[1]);
  return x1 * x2 < 0;
}

void arrange(double r[2])
{
  double tmp = r[1] - r[0];
  if ((0 <= tmp && tmp <= M_PI) || (-2*M_PI <= tmp && tmp <= -M_PI))
    return;
  tmp = r[0], r[0] = r[1], r[1] = tmp;
}

int inrange(double p, double lo, double hi, int inc)
{
  if (lo > 0 && hi < 0)
    {
      if (p > 0)
	hi += 2*M_PI;
      else if (p < 0)
	lo -= 2*M_PI;
    }
  if (inc)
    return lo <= p && p <= hi;
  return lo < p && p < hi;
}

int overlap(double a[2], double b[2])
{
  int status = 0;
  if (inrange(b[0], a[0], a[1], 0))
    status += 1;
  if (inrange(b[1], a[0], a[1], 0))
    status += 2;
  if (inrange(a[0], b[0], b[1], 1) && inrange(a[1], b[0], b[1], 1))
    status = 4;
  return status;
}

void rayseg(int seg1[2], int seg2[2], int p[2], double theta, double cross[2])
{
  double qx = seg1[0], qy = seg1[1], sx = seg2[0]-seg1[0], sy = seg2[1]-seg1[1];
  double rx = cos(theta), ry = sin(theta), u;
  u = (p[1] - qy + (ry/rx) * (qx-p[0])) / (sy - (ry*sx)/rx);
  cross[0] = qx + u * sx;
  cross[1] = qy + u * sy;
}

int cmp(const void *pa, const void *pb)
{
  int *a = (int*)pa, *b = (int*)pb;
  if (a[1] != b[1])
    return a[1] < b[1] ? -1:1;
  return a[0] != b[0] ? (a[0] < b[0] ? -1:1) : 0;
}

int main()
{
  FILE *fin = fopen("fence4.in", "r"), *fout = fopen("fence4.out", "w");
  int n, obs[2], fence[200][2], nsegs, visible[200][2], nvis = 0, i, j, k, tmp;
  double segments[400][2], cut[2], seg1[2], seg2[2], cut1[2], cut2[2];
  fscanf(fin, "%d\n%d %d", &n, &obs[0], &obs[1]);
  for (i=0; i<n; i++)
    fscanf(fin, "%d %d", &fence[i][0], &fence[i][1]);

  for (i=0; i<n; i++)
    {
      segments[0][0] = atan2(fence[i][1]-obs[1], fence[i][0]-obs[0]);
      segments[0][1] = atan2(fence[(i+1)%n][1]-obs[1], fence[(i+1)%n][0]-obs[0]);
      arrange(segments[0]);
      nsegs = 1;
      if (-DELTA <= segments[0][0]-segments[0][1] && segments[0][0]-segments[0][1] <= DELTA)
	nsegs = 0;
      for (j=0; j<n; j++)
	{
	  if (i == j)
	    continue;
	  if (intersect(fence[i], fence[(i+1)%n], fence[j], fence[(j+1)%n]))
	    goto NO_SOL;
	  cut[0] = atan2(fence[j][1]-obs[1], fence[j][0]-obs[0]);
	  cut[1] = atan2(fence[(j+1)%n][1]-obs[1], fence[(j+1)%n][0]-obs[0]);
	  arrange(cut);
	  rayseg(fence[j], fence[(j+1)%n], obs, cut[0], cut1);
	  rayseg(fence[j], fence[(j+1)%n], obs, cut[1], cut2);
	  for (k=0; k<nsegs; k++)
	    {
	      rayseg(fence[i], fence[(i+1)%n], obs, segments[k][0], seg1);
	      rayseg(fence[i], fence[(i+1)%n], obs, segments[k][1], seg2);
	      //printf("%d %d\n", fintersect(obs, seg1, cut1, cut2), fintersect(obs, seg2, cut1, cut2));
	      if ((tmp = overlap(segments[k], cut)) == 0 ||
		  (tmp == 1 && !(fintersect(obs, seg2, cut1, cut2) && !spc_oppo(obs, cut1, seg1, seg2))) ||
		  (tmp == 2 && !(fintersect(obs, seg1, cut1, cut2) && !spc_oppo(obs, cut2, seg1, seg2))) ||
		  (tmp == 3 && (fintersect(obs, cut1, seg1, seg2) && fintersect(obs, cut2, seg1, seg2))) ||
		  (tmp == 4 && !(fintersect(obs, seg1, cut1, cut2) && fintersect(obs, seg2, cut1, cut2))))
		continue;
	      /*printf("%d %d %d %d (%d)\n", i, j, nsegs, k, tmp);
		printf("%f %f %f %f | %f %f %f %f\n", seg1[0], seg1[1], seg2[0], seg2[1], cut1[0], cut1[1], cut2[0], cut2[1]);*/
	      if (tmp == 1 || tmp == 3)
		{
		  segments[nsegs][0] = segments[k][0];
		  segments[nsegs][1] = cut[0];
		  nsegs++;
		}
	      if (tmp == 2 || tmp == 3)
		{
		  segments[nsegs][0] = cut[1];
		  segments[nsegs][1] = segments[k][1];
		  nsegs++;
		}
	      segments[k][0] = segments[nsegs-1][0];
	      segments[k][1] = segments[nsegs-1][1];
	      nsegs--;
	      k--;
	    }
	}
      if (nsegs > 0)
	{
	  visible[nvis][0] = i;
	  visible[nvis][1] = i+1;
	  if (i+1 == n)
	    {
	      visible[nvis][0] = 0;
	      visible[nvis][1] = i;
	    }
	  nvis++;
	}
    }

  qsort(visible, nvis, sizeof visible[0], cmp);
  fprintf(fout, "%d\n", nvis);
  for (i=0; i<nvis; i++)
    fprintf(fout, "%d %d %d %d\n", fence[visible[i][0]][0], fence[visible[i][0]][1], fence[visible[i][1]][0], fence[visible[i][1]][1]);

  if (0)
  NO_SOL: fprintf(fout, "NOFENCE\n");
  
  fclose(fin), fclose(fout);
}
