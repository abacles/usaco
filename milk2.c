/*
ID: abacles1
LANG: C
TASK: milk2
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
  FILE *in=fopen("milk2.in","r"),*out=fopen("milk2.out","w");
  int farmers;
  long int **milking_time,ctime,cmp=0,cnmp=0,bmp=0,bnmp=0;
  long int begin=1000001,end=-1;
  int i,milking;
  fscanf(in,"%d",&farmers);
  milking_time=malloc(sizeof(long int *)*farmers);
  for(i=0;i<farmers;i++)
    {
      milking_time [i]=malloc(sizeof(long int)*2);
      fscanf(in,"%ld %ld",&(milking_time [i][0]),&(milking_time [i][1]));
      if(milking_time [i][0]<begin)
	begin=milking_time [i][0];
      if(milking_time [i][1]>end)
	end=milking_time [i][1];
    }
  for(ctime=begin;ctime<=end;ctime++)
    {
      milking=0;
      for(i=0;i<farmers;i++)
	{
	  if(milking_time [i][0]<=ctime && ctime<milking_time [i][1])
	    {
	      milking=1;
	      break;
	    }
	}
      if(milking)
	{
	  if(cnmp>bnmp && bmp!=0)
	    bnmp=cnmp;
	  cnmp=0;
	  cmp++;
	}
      else
	{
	  if(cmp>bmp)
	    bmp=cmp;
	  cmp=0;
	  cnmp++;
	}
    }
  fprintf(out,"%ld %ld\n",bmp,bnmp);
  for(i=0;i<farmers;i++)
    free(milking_time [i]);
  free(milking_time);
  fclose(in);
  fclose(out);
  return 0;
}
