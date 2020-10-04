/*
ID: abacles1
LANG: C
TASK: friday
*/

#include <stdio.h>

/* 1900.1.1: Monday */

int main()
{
  FILE *in=fopen("friday.in","r"),*out=fopen("friday.out","w");
  int yearcount,freq [7]={0,0,0,0,0,0,0}; /*freq starts on Monday*/
  int dicm,days_in_months [12]={31,28,31,30,31,30,31,31,30,31,30,31};
  int i,j,month,dow=0;
  fscanf(in,"%d",&yearcount);
  for(i=0;i<yearcount;i++)
    {
      for(month=0;month<12;month++)
	{
	  if(month==1 && ((i%4==0 && i%100!=0) || (1900+i)%400==0))
	    dicm=29;
	  else
	    dicm=days_in_months [month];
	  for(j=0;j<dicm;j++)
	    {
	      if(j==12)
		freq [dow]++;
	      dow=(dow+1)%7;
	    }
	}
    }
  fprintf(out,"%d %d %d %d %d %d %d\n",freq [5],freq [6],freq [0],freq [1],freq [2],freq [3],freq [4]);
  fclose(in);
  fclose(out);
  return 0;
}
