/*
ID: abacles1
LANG: C
TASK: hamming
*/

#include <stdio.h>
#include <stdlib.h>

int hamdist(int a,int b,int bits)
{
  int dist = 0;
  int bit = 1 << bits;
  while(bit >= 1)
    {
      if(a/bit != b/bit)
	dist++;
      a %= bit;
      b %= bit;
      bit /= 2;
    }
  return dist;
}

int valid(int n,int exist[],int elen,int mindist,int maxbits)
{
  int i;
  for(i=0;i<elen;i++)
    {
      if(hamdist(n,exist[i],maxbits) < mindist)
	return 0;
    }
  return 1;
}

int main()
{
  FILE *in,*out;
  int len,size,dist;
  int i,j,*prev;

  in = fopen("hamming.in","r");
  fscanf(in,"%d %d %d",&len,&size,&dist);
  fclose(in);
  prev = malloc(sizeof(int)*len);

  out = fopen("hamming.out","w");
  for(i=0,j=0;i<len;j++)
    {
      if(valid(j,prev,i,dist,size))
	{
	  prev[i] = j;
	  i++;
	  if(i%10 == 0 || i==len)
	    fprintf(out,"%d\n",j);
	  else
	    fprintf(out,"%d ",j);
	}
    }
  fclose(out);

  free(prev);
  return 0;
}
