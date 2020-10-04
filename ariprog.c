/*
ID: abacles1
LANG: C
TASK: ariprog
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
  FILE *in=fopen("ariprog.in","r"),*out=fopen("ariprog.out","w");
  int slen,bound;
  long int max,diff,start,curr;
  char *bsq;
  long int i,j,success,count=0;

  fscanf(in,"%d",&slen);
  fscanf(in,"%d",&bound);

  max = 2 * (bound*bound);
  bsq = malloc(sizeof(char)*(max+2));

  for(i=0;i<=max;i++)
    bsq [i] = 0;
  bsq [max+1] = '\0';
  for(i=0;i<=bound;i++)
    {
      for(j=0;j<=bound;j++)
	bsq [i*i+j*j] = 1;
    }

  for(diff=1;diff<=max/(slen-1);diff++)
    {
      for(start=0;start<=max-diff*(slen-1);start++)
	{
	  curr = start;
	  success = 1;
	  for(i=0;i<slen;i++)
	    {
	      if(bsq [curr])
		{
		  curr += diff;
		  continue;
		}
	      success = 0;
	      break;
	    }
	  if(success)
	    {
	      fprintf(out,"%ld %ld\n",start,diff);
	      count++;
	    }
	}
    }

  if(!count)
    fprintf(out,"NONE\n");

  free(bsq);
  fclose(in);
  fclose(out);
  return 0;
}
