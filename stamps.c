/*
ID: abacles1
LANG: C
TASK: stamps
*/

#include <stdio.h>
#include <stdlib.h>

#define INF 300

int main()
{
  FILE *in = fopen("stamps.in","r"),*out = fopen("stamps.out","w");
  int maxstamps,stamptypes,*stamps,*minscount;
  int i,j;
  fscanf(in,"%d %d",&maxstamps,&stamptypes);
  stamps = malloc(sizeof(int)*stamptypes);
  for(i=0;i<stamptypes;i++)
    fscanf(in,"%d",stamps+i);
  fclose(in);
  minscount = malloc(sizeof(int)*(maxstamps*10000+1));
  minscount[0] = 0;
  for(i=1;i<=maxstamps*10000;i++)
    {
      minscount[i] = INF;
      for(j=0;j<stamptypes;j++)
	{
	  if(stamps[j] <= i && minscount[i-stamps[j]]+1 < minscount[i])
	    minscount[i] = minscount[i-stamps[j]] + 1;
	}
      if(minscount[i] > maxstamps)
	break;
    }
  fprintf(out,"%d\n",i-1);
  fclose(out);
  free(stamps);
  free(minscount);
}
