/*
ID: abacles1
LANG: C
TASK: subset
*/

#include <stdio.h>
#include <stdlib.h>

long int **mem;

long int totalpart(int n,int sum)
{
  int i,s = n*(n+1)/2;
  long int total = 0;
  if(s < sum)
    {
      mem[n][sum] = 0;
      return 0;
    }
  else if(s == sum)
    {
      mem[n][sum] = 1;
      return 1;
    }
  for(i=n;i>0;i--)
    {
      if(i > sum)
	continue;
      else if(mem[i-1][sum-i] > 0)
	total += mem[i-1][sum-i];
      else
	total += totalpart(i-1,sum-i);
    }
  mem[n][sum] = total;
  return total;
}

int main()
{
  FILE *in,*out;
  int n,sum,i,j;
  long int partitions = 0;
  in = fopen("subset.in","r");
  fscanf(in,"%d",&n);
  fclose(in);
  if((n*(n+1)/2)%2 == 0)
    {
      sum = n*(n+1)/4;
      mem = malloc(sizeof(long int*)*(n+1));
      for(i=0;i<=n;i++)
	{
	  mem[i] = malloc(sizeof(long int)*(sum+1));
	  for(j=0;j<=sum;j++)
	    mem[i][j] = -1;
	}
      partitions = totalpart(n,sum);
      for(i=0;i<=n;i++)
	free(mem[i]);
      free(mem);
    }
  out = fopen("subset.out","w");
  fprintf(out,"%ld\n",partitions);
  fclose(out);
  return 0;
}
