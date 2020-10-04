/*
ID: abacles1
LANG: C
TASK: kimbits
*/

#include <stdio.h>

int next(int len,int omax,int ocount,char str[])
{
  int i;
  for(i=len-1;i>=0;i--)
    {
      if(str[i] == '0')
	{
	  str[i] = '1';
	  ocount++;
	  if(ocount <= omax)
	    return ocount;
	  return next(len,omax,ocount,str);
	}
      str[i] = '0';
      ocount--;
    }
  return 0;
}

int solve(int len,int omax,unsigned int togo,char str[])
{
  int i,j;
  for(i=0;i<len;i++)
    str[i] = '0';
  if(omax == 0)
    return togo - 1;
  if(togo < (unsigned int)1<<omax)
    {
      j = 0;
      for(i=1;i<togo;i++)
	j = next(len,omax,j,str);
      return 0;
    }
  togo -= (unsigned int)1<<omax;
  for(i=len-omax;i<len;i++)
    str[i] = '1';
  for(i=len-omax-1;i>=0;i--)
    {
      if(!togo)
	return 0;
      str[i] = '1';
      for(j=i+1;j<len;j++)
	str[j] = '0';
      togo = solve(len-1-i,omax-1,togo,str+i+1);
    }
  return togo;
}

int main()
{
  FILE *in = fopen("kimbits.in","r"),*out = fopen("kimbits.out","w");
  char str[32];
  int len,omax;
  unsigned int pos,i,j;
  fscanf(in,"%d %d %u",&len,&omax,&pos);
  fclose(in);
  str[len] = 0;
  solve(len,omax,pos,str);
  fprintf(out,"%s\n",str);
  fclose(out);
}
