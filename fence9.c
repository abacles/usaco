/*
  ID: abacles1
  LANG: C
  TASK: fence9
*/

#include <stdio.h>
#include <math.h>

float point(int x,int n,int m,int p,int q)
{
  return m + (x - n) * (1.0 * (q - m) / (p - n));
}

int main()
{
  FILE *in = fopen("fence9.in","r"),*out = fopen("fence9.out","w");
  int n,m,p,i,inarea = 0;
  fscanf(in,"%d %d %d",&n,&m,&p);
  fclose(in);
  for(i=1;i<(p<n?p:n);i++)
    inarea += (int)ceil(point(i,0,0,n,m)) - 1;
  for(;i<(p>n?p:n);i++)
    {
      if(p >= n)
	inarea += (int)ceil(point(i,n,m,p,0)) - 1;
      else
	inarea += (int)ceil(point(i,0,0,n,m)) - 1 - (int)floor(point(i,p,0,n,m));
    }
  fprintf(out,"%d\n",inarea);
  fclose(out);
}
