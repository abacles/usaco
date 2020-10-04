/*
  ID: abacles1
  LANG: C
  TASK: nuggets
*/

#include <stdio.h>
#include <stdlib.h>

int compar(const void *a,const void *b)
{
  return *(int*)a - *(int*)b;
}

int gcf(int a,int b)
{
  if(a == 0) return b;
  return gcf(b%a,a);
}

int repeat(int *prev,int c,int biggest)
{
  int i;
  for(i=0;i<biggest;i++)
    if(!prev[(c-i+514)%514]) return 0;
  return 1;
}

int main()
{
  FILE *in = fopen("nuggets.in","r"),*out = fopen("nuggets.out","w");
  int options,packages[10],i,j,agcf,good[514] = {0},gw = 0,biggestbad = 0;
  fscanf(in,"%d",&options);
  for(i=0;i<options;i++) fscanf(in,"%d",&packages[i]);
  fclose(in);
  qsort(packages,options,sizeof(int),compar);
  for(agcf=packages[0],i=1;i<options;i++)
    agcf = gcf(agcf,packages[i]);
  if(agcf > 1 || packages[0] == 1)
    fprintf(out,"0\n");
  else
    {
      for(i=0;i<options;i++) good[packages[i]] = 1;
      for(i=1;;i++)
	{
	  if(good[i%514])
	    for(j=0;j<options;j++) good[(i+packages[j])%514] = 1;
	  else
	    {
	      biggestbad = i;
	      good[i%514] = 0;
	    }
	  if(repeat(good,i,packages[options-1])) break;
	  good[(i-256+514)%514] = 0;
	}
      fprintf(out,"%d\n",biggestbad);
    }
  fclose(out);
}
