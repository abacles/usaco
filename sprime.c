/*
ID: abacles1
LANG: C
TASK: sprime
*/

#include <stdio.h>
#include <stdlib.h>

int prime(int n)
{
  int i;
  for(i=2;i*i<=n;i++)
    {
      if(n%i == 0)
	return 0;
    }
  return 1;
}

int main()
{
  FILE *in,*out;
  int len;
  long int *primelib [8] = {NULL};
  int sprimecount [8];
  int i,j,k;

  primelib[0] = malloc(sizeof(long int)*4);
  primelib[0][0] = 2;
  primelib[0][1] = 3;
  primelib[0][2] = 5;
  primelib[0][3] = 7;
  sprimecount[0] = 4;

  in = fopen("sprime.in","r");
  fscanf(in,"%d",&len);
  fclose(in);

  for(i=1;i<len;i++)
    {
      primelib[i] = malloc(sizeof(long int)*5*sprimecount[i-1]);
      sprimecount[i] = 0;
      for(j=0;j<sprimecount[i-1];j++)
	{
	  for(k=1;k<10;k++)
	    {
	      if(prime(primelib[i-1][j]*10+k))
		{
		  primelib[i][sprimecount[i]] = primelib[i-1][j]*10+k;
		  sprimecount[i]++;
		}
	    }
	}
    }

  out = fopen("sprime.out","w");
  for(i=0;i<sprimecount[len-1];i++)
    fprintf(out,"%ld\n",primelib[len-1][i]);
  fclose(out);

  for(i=0;i<8;i++)
    free(primelib [i]);
  
  return 0;
}
