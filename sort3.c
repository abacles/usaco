/*
ID: abacles1
LANG: C
TASK: sort3
*/

#include <stdio.h>
#include <stdlib.h>

#define MIN(A,B) (A<B?A:B)
#define MAX(A,B) (A>B?A:B)
#define ABS(A) (A<0?-(A):A)

int main()
{
  FILE *in,*out;
  int len;
  int *a;
  int count[9] = {0};
  int swaps;
  int i;
    
  in = fopen("sort3.in","r");
  fscanf(in,"%d",&len);
  a = malloc(sizeof(int)*len);
  for(i=0;i<len;i++)
    {
      fscanf(in,"%d",a+i);
      count[a[i]-1]++;
    }
  fclose(in);
  
  for(i=0;i<len;i++)
    {
      if(i<count[0])
	{
	  if(a[i]!=1)
	    count[a[i]+1]++; // 3 4
	}
      else if(i<count[0]+count[1])
	{
	  if(a[i]==1)
	    count[5]++; // 5 6
	  else if(a[i]==3)
	    count[6]++;
	}
      else if(a[i]!=3)
	count[a[i]+6]++; // 7 8
    }

  /*
    3 5
    4 7
    6 8
   */
  swaps = MIN(count[3],count[5]) + MIN(count[4],count[7]) + MIN(count[6],count[8]);
  swaps += (ABS(count[3]-count[5]) + ABS(count[4]-count[7]) + ABS(count[6]-count[8]))/3*2;

  printf("%d\n",swaps);
  out = fopen("sort3.out","w");
  fprintf(out,"%d\n",swaps);
  fclose(out);

  free(a);
  return 0;
}
