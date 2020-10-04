/*
ID: abacles1
LANG: C
TASK: fracdec
*/

#include <stdio.h>

#define MAX 1000000

int rp[MAX];
char dec[MAX+1];
int dwrite = 0,rps = -1;

void expr(int inner,int outer)
{
  while(1)
    {
      if(rp[inner] >= 0)
	{
	  rps = rp[inner];
	  return;
	}
      dec[dwrite] = '0' + inner / outer;
      rp[inner] = dwrite;
      dwrite++;
      if(inner % outer == 0)
	{
	  dec[dwrite] = 0;
	  return;
	}
      inner = (inner % outer) * 10;
    }
}

int main()
{
  FILE *in = fopen("fracdec.in","r"),*out = fopen("fracdec.out","w");
  char pref[100002];
  int numer,denom;
  int i,cil;
  fscanf(in,"%d %d",&numer,&denom);
  fclose(in);
  for(i=0;i<MAX;i++)
    rp[i] = -1;

  sprintf(pref,"%d.",numer/denom);
  fprintf(out,"%s",pref);
  for(cil=0;pref[cil];cil++) {}
  expr((numer%denom)*10,denom);
  for(i=0;i<dwrite;i++)
    {
      if(i == rps)
	{
	  fprintf(out,"(");
	  cil++;
	}
      if(cil == 76)
	{
	  fprintf(out,"\n");
	  cil = 0;
	}
      fprintf(out,"%c",dec[i]);
      cil++;
      if(cil == 76)
	{
	  fprintf(out,"\n");
	  cil = 0;
	}
    }
  if(rps >= 0)
    fprintf(out,")");
  fprintf(out,"\n");

  fclose(out);
  return 0;
}
