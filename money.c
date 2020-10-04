/*
ID: abacles1
LANG: C
TASK: money
*/

#include <stdio.h>
#include <stdlib.h>

long long int **mem;

void sort(int list[],int len)
{
  int i,j,temp;
  for(i=0;i<len;i++)
    {
      for(j=i+1;j<len;j++)
	{
	  if(list[i] > list[j])
	    {
	      temp = list[i];
	      list[i] = list[j];
	      list[j] = temp;
	    }
	}
    }
}

long long int combos(int sum,int *parts,int pcount)
{
  int i,j,prevcycle;
  long long int c;
  for(j=1;j<=sum;j++)
    {
      for(i=1;i<pcount;i++)
	{
	  c = mem[i-1][j];
	  for(prevcycle=1;j-prevcycle*parts[i]>=0;prevcycle++)
	    c += mem[i-1][j-prevcycle*parts[i]];
	  mem[i][j] = c;
	}
    }
  /* for(i=0;i<pcount;i++)
    {
      for(j=0;j<=sum;j++)
	printf("%lld ",mem[i][j]);
      printf("\n");
    } */
  return mem[pcount-1][sum];
}

int main()
{
  FILE *in,*out;
  int ctypes,money,*coins;
  int i;
  in = fopen("money.in","r");
  fscanf(in,"%d %d",&ctypes,&money);
  coins = malloc(sizeof(int)*ctypes);
  mem = malloc(sizeof(long long int*)*ctypes);
  for(i=0;i<ctypes;i++)
    {
      fscanf(in,"%d",coins+i);
      mem[i] = malloc(sizeof(long long int)*(money+1));
      mem[i][0] = 1;
    }
  fclose(in);

  sort(coins,ctypes);
  for(i=1;i<=money;i++)
    mem[0][i] = (i % coins[0]) == 0;

  out = fopen("money.out","w");
  fprintf(out,"%lld\n",combos(money,coins,ctypes));
  fclose(out);
  
  free(coins);
  for(i=0;i<ctypes;i++)
    free(mem[i]);
  free(mem);
  
  return 0;
}
