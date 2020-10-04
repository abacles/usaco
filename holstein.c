/*
ID: abacles1
LANG: C
TASK: holstein
*/

#include <stdio.h>
#include <stdlib.h>

int enough(int *req,int *have,int len)
{
  int i;
  for(i=0;i<len;i++)
    {
      if(have[i] < req[i])
	return 0;
    }
  return 1;
}

// call with 123 5 3 for first call (choose 3 from 5)
int nextcombo(int *combo,int max,int len)
{
  int i,j;
  for(i=len-1;i>=0;i--)
    {
      if(combo[i]+(len-i-1) < max)
	{
	  combo[i]++;
	  for(j=1;i+j<len;j++)
	    combo[i+j] = combo[i] + j;
	  return 1;
	}
    }
  return 0;
}

int main()
{
  FILE *in,*out;
  int vtypes,scptypes;
  int *vreq,**scoops;
  int *feed,*chosen;
  int i,j,k;
  
  in = fopen("holstein.in","r");
  fscanf(in,"%d",&vtypes);
  vreq = malloc(sizeof(int)*vtypes);
  feed = malloc(sizeof(int)*vtypes);
  for(i=0;i<vtypes;i++)
    fscanf(in,"%d",vreq+i);
  fscanf(in,"%d",&scptypes);
  scoops = malloc(sizeof(int*)*scptypes);
  chosen = malloc(sizeof(int)*scptypes);
  for(i=0;i<scptypes;i++)
    {
      scoops[i] = malloc(sizeof(int)*vtypes);
      for(j=0;j<vtypes;j++)
	fscanf(in,"%d",&(scoops[i][j]));
    }
  fclose(in);

  for(i=1;i<=scptypes;i++)
    {
      for(j=0;j<scptypes;j++)
	chosen[j] = j;
      do
	{
	  for(j=0;j<vtypes;j++)
	    {
	      feed[j] = 0;
	      for(k=0;k<i;k++)
		feed[j] += scoops[chosen[k]][j];
	    }
	  if(enough(vreq,feed,vtypes))
	    goto FINISHED;
	} while(nextcombo(chosen,scptypes-1,i));
    }
 FINISHED:
  out = fopen("holstein.out","w");
  fprintf(out,"%d",i);
  for(j=0;j<i;j++)
    fprintf(out," %d",chosen[j]+1);
  fprintf(out,"\n");
  fclose(out);

  free(chosen);
  free(vreq);
  free(feed);
  for(i=0;i<scptypes;i++)
    free(scoops[i]);
  free(scoops);
  return 0;
}
