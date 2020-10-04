/*
ID: abacles1
LANG: C
TASK: nocows
*/

#include <stdio.h>
#include <stdlib.h>

int **mem;

int cowtree(int nodes,int depth)
{
  int i,tcount = 0,l,r;
  if(nodes == 1)
    return 1;
  if(nodes % 2 == 0 || depth == 1)
    return 0;
  for(i=1;i<nodes-1;i++)
    {
      if(mem[i][depth-1] >= 0)
	l = mem[i][depth-1];
      else
	l = cowtree(i,depth-1);
      if(mem[nodes-1-i][depth-1] >= 0)
	r = mem[nodes-1-i][depth-1];
      else
	r = cowtree(nodes-1-i,depth-1);
      tcount += l*r;
    }
  tcount %= 9901;
  mem[nodes][depth] = tcount;
  return tcount;
}

int main()
{
  FILE *in,*out;
  int cowcount,gen,i,j;
  in = fopen("nocows.in","r");
  fscanf(in,"%d %d",&cowcount,&gen);
  fclose(in);
  mem = malloc(sizeof(int*)*(cowcount+1));
  for(i=0;i<=cowcount;i++)
    {
      mem[i] = malloc(sizeof(int)*(gen+1));
      for(j=0;j<=gen;j++)
	mem[i][j] = -1;
    }
  out = fopen("nocows.out","w");
  fprintf(out,"%d\n",(cowtree(cowcount,gen)-cowtree(cowcount,gen-1)+9901)%9901);
  fclose(out);
  for(i=0;i<=cowcount;i++)
    free(mem[i]);
  free(mem);
  return 0;
}
