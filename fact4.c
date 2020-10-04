/*
ID: abacles1
LANG: C
TASK: fact4
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
  FILE *in = fopen("fact4.in","r"),*out = fopen("fact4.out","w");
  int n,*factnums,dig = 1,i,two = 0,five = 0,base,exp;
  fscanf(in,"%d",&n);
  fclose(in);
  factnums = malloc(sizeof(int)*n);
  for(i=1;i<=n;i++)
    {
      for(factnums[i-1]=i;factnums[i-1]%2 == 0;two++,factnums[i-1]/=2) {}
      for(;factnums[i-1]%5 == 0;five++,factnums[i-1]/=5) {}
    }
  for(i=0;i<n;i++)
    dig = (dig*factnums[i]) % 10;
  base = 2;
  exp = two - five;
  if(five > two)
    {
      base = 5;
      exp = five - two;
    }
  for(i=0;i<exp;i++)
    dig = (dig*base) % 10;
  fprintf(out,"%d\n",dig);
  fclose(out);
  free(factnums);
}
