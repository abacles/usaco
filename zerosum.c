/*
ID: abacles1
LANG: C
TASK: zerosum
*/

#include <stdio.h>

int nextopseq(char op[],int len)
{
  int i;
  for(i=len-1;i>=0;i--)
    {
      if(op[i] == ' ')
	{
	  op[i] = '+';
	  return 1;
	}
      else if(op[i] == '+')
	{
	  op[i] = '-';
	  return 1;
	}
      op[i] = ' ';
    }
  return 0;
}

void printexp(int n,char op[],FILE *fp)
{
  int i;
  fprintf(fp,"1");
  for(i=0;i<n-1;i++)
    fprintf(fp,"%c%d",op[i],i+2);
  fprintf(fp,"\n");
}

void findzsums(int n,FILE *fp)
{
  int i,rval,rslt,prevsign;
  char op[10];
  for(i=0;i<n-1;i++)
    op[i] = ' ';
  op[i] = 0;
  while(nextopseq(op,n-1))
    {
      prevsign = rval = 1;
      rslt = 0;
      for(i=0;i<n-1;i++)
	{
	  if(op[i] == ' ')
	    rval = 10*rval + i+2;
	  else
	    {
	      rslt += rval * prevsign;
	      rval = i + 2;
	      if(op[i] == '+')
		prevsign = 1;
	      else
		prevsign = -1;
	    }
	}
      if(rslt+rval*prevsign == 0)
	printexp(n,op,fp);
    }
}

int main()
{
  FILE *in,*out;
  int n;
  in = fopen("zerosum.in","r");
  fscanf(in,"%d",&n);
  fclose(in);
  out = fopen("zerosum.out","w");
  findzsums(n,out);
  fclose(out);
  return 0;
}
