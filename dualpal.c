/*
ID: abacles1
LANG: C
TASK: dualpal
*/

#include <stdio.h>
#include <string.h>

void dec_to_str(int dec_repr,int base,char repr [],int reprcap)
{
  int i,digit,len;
  char temp;
  for(i=0;i<reprcap && dec_repr!=0;i++)
    {
      digit=dec_repr%base;
      if(digit<10)
	repr [i]='0'+digit;
      else
	repr [i]='A'+digit-10;
      dec_repr/=base;
    }
  repr [i]='\0';
  for(len=i,i=len-1;i>(len-1)/2;i--)
    {
      temp=repr [i];
      repr [i]=repr [len-1-i];
      repr [len-1-i]=temp;
    }
}

int is_palin(char str [])
{
  int i,len=strlen(str);
  for(i=0;i<=(len-1)/2;i++)
    {
      if(str [i]!=str [len-1-i])
	return 0;
    }
  return 1;
}

int main()
{
  FILE *in=fopen("dualpal.in","r"),*out=fopen("dualpal.out","w");
  int count,start,found=0;
  char repr [20];
  int i,base,palcount;
  fscanf(in,"%d %d",&count,&start);
  for(i=start+1;found<count;i++)
    {
      palcount=0;
      for(base=2;base<=10;base++)
	{
	  dec_to_str(i,base,repr,20);
	  if(is_palin(repr))
	    palcount++;
	  if(palcount>=2)
	    {
	      fprintf(out,"%d\n",i);
	      found++;
	      break;
	    }
	}
    }
  fclose(in);
  fclose(out);
  return 0;
}
