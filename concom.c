/*
ID: abacles1
LANG: C
TASK: concom
*/

#include <stdio.h>

int main()
{
  FILE *in,*out;
  int ctrls,equity[101][101],ctrl[101][101],q[10000][2],indir[101];
  int i,j,r,a,b,perc,qread = 0,qwrite = 0;
  in = fopen("concom.in","r");
  fscanf(in,"%d",&ctrls);
  for(i=0;i<=100;i++)
    {
      for(j=0;j<=100;j++)
	ctrl[i][j] = equity[i][j] = 0;
    }
  for(i=0;i<ctrls;i++)
    {
      fscanf(in,"%d %d %d",&a,&b,&perc);
      equity[a][b] = perc;
      if(perc > 50 && a!=b)
	{
	  ctrl[a][b] = 1;
	  q[qwrite][0] = a;
	  q[qwrite][1] = b;
	  qwrite++;
	}
    }
  fclose(in);

  while(qread != qwrite)
    {
      if(qwrite >= 10000)
	printf("queue overflow\n");
      a = q[qread][0];
      b = q[qread][1];
      qread++;
      for(i=1;i<=100;i++)
	{
	  if(ctrl[b][i] && !ctrl[a][i] && a!=i)
	    {
	      ctrl[a][i] = 1;
	      q[qwrite][0] = a;
	      q[qwrite][1] = i;
	      qwrite++;
	    }
	}
      for(i=1;i<=100;i++)
	indir[i] = 0;
      for(i=1;i<=100;i++)
	{
	  for(j=1;j<=100;j++)
	    {
	      if(ctrl[a][j])
		indir[i] += equity[j][i];
	    }
	}
      for(i=1;i<=100;i++)
	{
	  if(indir[i]+equity[a][i] > 50 && !ctrl[a][i] && a!=i)
	    {
	      ctrl[a][i] = 1;
	      q[qwrite][0] = a;
	      q[qwrite][1] = i;
	      qwrite++;
	    }
	}
      for(i=1;i<=100;i++)
	{
	  if(ctrl[i][a])
	    {
	      for(j=1;j<=100;j++)
		{
		  if(ctrl[a][j] && !ctrl[i][j] && i!=j)
		    {
		      ctrl[i][j] = 1;
		      q[qwrite][0] = i;
		      q[qwrite][1] = j;
		      qwrite++;
		    }
		}
	    }
	}
    }

  out = fopen("concom.out","w");
  for(i=1;i<=100;i++)
    {
      for(j=1;j<=100;j++)
	{
	  if(ctrl[i][j])
	    fprintf(out,"%d %d\n",i,j);
	}
    }
  fclose(out);
  return 0;
}
