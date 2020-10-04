/*
ID: abacles1
LANG: C
TASK: cowtour
*/

// 39796.392691

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int ncount,**points;
char **cmatrix;
double **dmatrix,*maxdist;

double dist(int a,int b)
{
  return sqrt((points[a][0]-points[b][0])*(points[a][0]-points[b][0]) + (points[a][1]-points[b][1])*(points[a][1]-points[b][1]));
}

void floyd_warshall()
{
  int k,i,j;
  for(k=0;k<ncount;k++)
    {
      for(i=0;i<ncount;i++)
	{
	  for(j=0;j<ncount;j++)
	    {
	      if(dmatrix[i][k]>0 && dmatrix[k][j]>0 && (dmatrix[i][k] + dmatrix[k][j] < dmatrix[i][j] || dmatrix[i][j]<0))
		  dmatrix[i][j] = dmatrix[i][k] + dmatrix[k][j];
	    }
	}
    }
}

int main()
{
  FILE *in,*out;
  double diam,mindiam = -1,ldiam,rdiam;
  int i,j,k;
  in = fopen("cowtour.in","r");
  fscanf(in,"%d",&ncount);
  points = malloc(sizeof(int*)*ncount);
  cmatrix = malloc(sizeof(char*)*ncount);
  dmatrix = malloc(sizeof(double*)*ncount);
  maxdist = malloc(sizeof(double)*ncount);
  for(i=0;i<ncount;i++)
    {
      points[i] = malloc(sizeof(int)*2);
      cmatrix[i] = malloc(sizeof(char)*(ncount+1));
      dmatrix[i] = malloc(sizeof(double)*ncount);      
      fscanf(in,"%d %d",&points[i][0],&points[i][1]);
    }
  for(i=0;i<ncount;i++)
    fscanf(in,"%s",cmatrix[i]);
  fclose(in);
  for(i=0;i<ncount;i++)
    {
      for(j=0;j<ncount;j++)
	{
	  if(i == j)
	    dmatrix[i][j] = 0;
	  else
	    {
	      dmatrix[i][j] = dist(i,j);
	      if(cmatrix[i][j] == '0')
		dmatrix[i][j] = -dmatrix[i][j];
	    }
	}
    }

  floyd_warshall();

  for(i=0;i<ncount;i++)
    {
      maxdist[i] = 0;
      for(j=0;j<ncount;j++)
	{
	  if(dmatrix[i][j] > maxdist[i])
	    maxdist[i] = dmatrix[i][j];
	}
    }

  for(i=0;i<ncount;i++)
    {
      for(j=i+1;j<ncount;j++)
	{
	  if(dmatrix[i][j] < 0)
	    {
	      ldiam = rdiam = 0;
	      for(k=0;k<ncount;k++)
		{
		  if(dmatrix[i][k] > 0 && maxdist[k] > ldiam)
		    ldiam = maxdist[k];
		  if(dmatrix[j][k] > 0 && maxdist[k] > rdiam)
		    rdiam = maxdist[k];
		}
	      diam = maxdist[i] + maxdist[j] - dmatrix[i][j];
	      if(ldiam > diam)
		diam = ldiam;
	      if(rdiam > diam)
		diam = rdiam;
	      if(diam < mindiam || mindiam < 0)
		mindiam = diam;
	    }
	}
    }

  out = fopen("cowtour.out","w");
  fprintf(out,"%.6lf\n",mindiam);
  fclose(out);

  for(i=0;i<ncount;i++)
    {
      free(points[i]);
      free(cmatrix[i]);
      free(dmatrix[i]);
    }
  free(points);
  free(cmatrix);
  free(dmatrix);
  free(maxdist);
  return 0;
}
