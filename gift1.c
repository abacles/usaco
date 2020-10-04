/*
ID: abacles1
LANG: C
TASK: gift1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find(char **people,char person [],int np)
{
  int i;
  for(i=0;i<np;i++)
    {
      if(strcmp(people [i],person)==0)
	return i;
    }
  return -1;
}

int main()
{
  FILE *in=fopen("gift1.in","r"),*out=fopen("gift1.out","w");
  int np;
  char **people,current [16];
  int *balance,*orig_balance,*givecount,**give;
  int i,j,k;
  fscanf(in,"%d",&np);
  people=malloc(sizeof(char *)*np);
  balance=malloc(sizeof(int)*np);
  orig_balance=malloc(sizeof(int)*np);
  givecount=malloc(sizeof(int)*np);
  give=malloc(sizeof(int *)*np);
  for(i=0;i<np;i++)
    {
      people [i]=malloc(sizeof(char)*16);
      fscanf(in,"%s",people [i]);
    }
  for(i=0;i<np;i++)
    {
      fscanf(in,"%s",current);
      j=find(people,current,np);
      fscanf(in,"%d %d",&(balance [j]),&(givecount [j]));
      orig_balance [j]=balance [j];
      give [j]=malloc(sizeof(int)*(givecount [j]));
      for(k=0;k<givecount [j];k++)
	{
	  fscanf(in,"%s",current);
	  give [j][k]=find(people,current,np);
	}
    }
  for(i=0;i<np;i++)
    {
      for(j=0;j<givecount [i];j++)
	balance [give [i][j]]+=orig_balance [i]/givecount [i];
      if(givecount [i]>0)
	balance [i]+=orig_balance [i]%givecount [i]-orig_balance [i];
    }
  for(i=0;i<np;i++)
    {
      fprintf(out,"%s %d\n",people [i],balance [i]-orig_balance [i]);
      free(people [i]);
      free(give [i]);
    }
  free(people);
  free(balance);
  free(orig_balance);
  free(givecount);
  free(give);
  fclose(in);
  fclose(out);
  return 0;
}
