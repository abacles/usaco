/*
ID: abacles1
LANG: C
TASK: runround
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int inc(char n[])
{
  sprintf(n,"%ld",atol(n)+1);
  return strlen(n);
}

int main()
{
  FILE *in,*out;
  char num[10];
  int digs[9];
  int *touched;
  int rr,di,i,l;
  in = fopen("runround.in","r");
  fscanf(in,"%s",num);
  fclose(in);
  touched = malloc(sizeof(int)*strlen(num));

  while(1)
    {
      for(i=0;i<9;i++)
	digs[i] = 0;
      l = inc(num);
      rr = 1;
      for(i=0;num[i];i++)
	{
	  if(num[i] == '0' || digs[num[i]-'1'] > 0)
	    {
	      rr = 0;
	      break;
	    }
	  digs[num[i]-'1'] = 1;
	}
      if(!rr)
	continue;
      di = 0;
      for(i=0;i<l;i++)
	touched[i] = 0;
      for(i=0;i<l;i++)
	{
	  if(touched[di])
	    {
	      rr = 0;
	      break;
	    }
	  touched[di] = 1;
	  di = (di+(num[di]-'1')+1) % l;
	}
      if(rr && di == 0)
	{
	  out = fopen("runround.out","w");
	  fprintf(out,"%s\n",num);
	  fclose(out);
	  break;
	}
    }

  free(touched);
  return 0;
}
