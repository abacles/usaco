/*
ID: abacles1
LANG: C
TASK: namenum
*/

#include <stdio.h>
#include <string.h>

int dig_to_int(char dig)
{
  return dig-'0';
}

int diglet_match(char dig,char let)
{
  switch(dig_to_int(dig))
    {
    case 2:
      {
	if(let>='A' && let<='C')
	  return 1;
	return 0;
      }
    case 3:
      {
	if(let>='D' && let<='F')
	  return 1;
	return 0;
      }
    case 4:
      {
	if(let>='G' && let<='I')
	  return 1;
	return 0;
      }
    case 5:
      {
	if(let>='J' && let<='L')
	  return 1;
	return 0;
      }
    case 6:
      {
	if(let>='M' && let<='O')
	  return 1;
	return 0;
      }
    case 7:
      {
	if(let=='P' || let=='R' || let=='S')
	  return 1;
	return 0;
      }
    case 8:
      {
	if(let>='T' && let<='V')
	  return 1;
	return 0;
      }
    case 9:
      {
	if(let>='W' && let<='Y')
	  return 1;
	return 0;
      }
    }
}

int main()
{
  FILE *in=fopen("namenum.in","r"),*dict=fopen("dict.txt","r"),*out=fopen("namenum.out","w");
  char id [14],name [14];
  int i,match,match_ever=0;
  fscanf(in,"%s",id);
  while(!feof(dict))
    {
      match=1;
      fscanf(dict,"%s",name);
      for(i=0;name [i]!='\0' && id [i]!='\0' && name [i]!='\n' && id [i]!='\n';i++)
	{
	  /*if(name [i]<(dig_to_int(id [i])-2)*3+'A' || name [i]>=(dig_to_int(id [i])-1)*3+'A')*/
	  if(!diglet_match(id [i],name [i]))
	    {
	      match=0;
	      break;
	    }
	}
      if(match && (name [i]=='\0' || name [i]=='\n') && (id [i]=='\0' || id [i]=='\n'))
	{
	  fprintf(out,"%s\n",name);
	  match_ever=1;
	}
    }
  if(!match_ever)
    fprintf(out,"NONE\n");
  fclose(in);
  fclose(dict);
  fclose(out);
  return 0;
}
