/*
  ID: abacles1
  LANG: C
  TASK: inflate
*/

#include <stdio.h>
#include <stdlib.h>

struct class
{
  int solvtime,points;
}*problems;

int knapsack(int cap,int objcount)
{
  int i,j,*mem = malloc(sizeof(int)*(cap+1));
  mem[0] = 0;
  for(i=1;i<=cap;i++)
    {
      mem[i] = mem[i-1];
      for(j=0;j<objcount;j++)
	{
	  if(problems[j].solvtime <= i &&
	     mem[i-problems[j].solvtime] + problems[j].points > mem[i])
	    mem[i] = mem[i-problems[j].solvtime] + problems[j].points;
	}
    }
  i = mem[cap];
  free(mem);
  return i;
}

int main()
{
  FILE *in = fopen("inflate.in","r"),*out = fopen("inflate.out","w");
  int total_time,classes;
  int i;
  fscanf(in,"%d %d",&total_time,&classes);
  problems = malloc(sizeof(struct class)*classes);
  for(i=0;i<classes;i++)
    fscanf(in,"%d %d",&(problems[i].points),&(problems[i].solvtime));
  fclose(in);
  fprintf(out,"%d\n",knapsack(total_time,classes));
  fclose(out);
  free(problems);
}
