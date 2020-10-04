/*
  ID: abacles
  LANG: C
  TASK: range
*/

#include <stdio.h>

char field[250][250];

int count(int len)
{
  int i,j,c = 0;
  for(i=0;i<len-1;i++)
    {
      for(j=0;j<len-1;j++)
	{
	  field[i][j] = field[i][j] && field[i+1][j] && field[i][j+1] && field[i+1][j+1];
	  c += field[i][j];
	}
    }
  return c;
}

int main()
{
  FILE *in = fopen("range.in","r"),*out = fopen("range.out","w");
  int size,sqcount;
  int i,j;
  fscanf(in,"%d",&size);
  for(i=0,fgetc(in);i<size;i++,fgetc(in))
    {
      for(j=0;j<size;j++)
	field[i][j] = fgetc(in) - '0';
    }
  fclose(in);
  for(i=2;i<=size;i++)
    {
      sqcount = count(size-i+2);
      if(!sqcount)
	break;
      fprintf(out,"%d %d\n",i,sqcount);
    }
  fclose(out);
}
