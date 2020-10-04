/*
ID: abacles1
LANG: C
TASK: palsquare
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
  FILE *in=fopen("palsquare.in","r"),*out=fopen("palsquare.out","w");
  int base;
  char repr [10],sqrepr [20];
  int i;
  long int square;
  fscanf(in,"%d",&base);
  for(i=1;i<=300;i++)
    {
      square=i*i;
      dec_to_str(square,base,sqrepr,20);
      if(is_palin(sqrepr))
	{
	  dec_to_str(i,base,repr,10);
	  fprintf(out,"%s %s\n",repr,sqrepr);
	}
    }
  fclose(in);
  fclose(out);
  return 0;
}
