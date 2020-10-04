/*
ID: abacles1
LANG: C
TASK: skidesign
*/

#include <stdio.h>
#include <stdlib.h>

int squared(int a)
{
  return a*a;
}

int main()
{
  FILE *in=fopen("skidesign.in","r"),*out=fopen("skidesign.out","w");
  int n,*elevation,cost,mincost=-1;
  int i,rstart;
  fscanf(in,"%d",&n);
  elevation=malloc(sizeof(int)*n);
  for(i=0;i<n;i++)
    fscanf(in,"%d",&(elevation [i]));
  for(rstart=0;rstart+17<=100;rstart++)
    {
      cost=0;
      for(i=0;i<n;i++)
	{
	  if(elevation [i]<rstart)
	    cost+=squared(rstart-elevation [i]);
	  else if(elevation [i]>rstart+17)
	    cost+=squared(elevation [i]-(rstart+17));
	}
      if(mincost==-1 || cost<mincost)
	mincost=cost;
    }
  fprintf(out,"%d\n",mincost);
  /*printf("%d\n",mincost);*/
  free(elevation);
  fclose(in);
  fclose(out);
  return 0;
}
