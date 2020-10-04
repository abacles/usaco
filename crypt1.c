/*
ID: abacles1
LANG: C
TASK: crypt1
*/

#include <stdio.h>
#include <stdlib.h>

int eval(int num [],int digits)
{
  if(digits==3)
    return num [0]*100+num [1]*10+num [2];
  else if(digits==2)
    return num [0]*10+num [1];
  return 0;
}

void repr(int num,int rslt [3])
{
  rslt [0]=num/100;
  rslt [1]=(num%100)/10;
  rslt [2]=num%10;
}

void sum(int a [3],int b [3],int rslt [4])
{
  int carry;
  rslt [3]=a [2];
  rslt [2]=(a [1]+b [2])%10;
  carry=(a [1]+b [2])/10;
  rslt [1]=(a [0]+b [1]+carry)%10;
  carry=(a [0]+b [1]+carry)/10;
  rslt [0]=b [0]+carry;
}

int included(int check,int n,int poss [])
{
  int i;
  for(i=0;i<n;i++)
    if(poss [i]==check)
      return 1;
  return 0;
}

int possible(int mi [3],int mii [2],int dc,int digits [])
{
  int i;
  int midi [3],midii [3],prod [4],fm=eval(mi,3);
  if(fm*mii [1]>=1000 || fm*mii [0]>=1000)
    return 0;
  repr(fm*mii [1],midi);
  for(i=0;i<3;i++)
    {
      if(!included(midi [i],dc,digits))
	return 0;
    }
  repr(fm*mii [0],midii);
  for(i=0;i<3;i++)
    {
      if(!included(midii [i],dc,digits))
	return 0;
    }
  sum(midi,midii,prod);
  for(i=0;i<4;i++)
    {
      if(!included(prod [i],dc,digits))
	return 0;
    }
  return 1;
}

int main()
{
  FILE *in=fopen("crypt1.in","r"),*out=fopen("crypt1.out","w");
  int digits_used,solutions=0;
  int *digits;
  int mi [3],mii [2];
  int i,j,k,l,q;
  fscanf(in,"%d",&digits_used);
  digits=malloc(sizeof(int)*digits_used);
  for(i=0;i<digits_used;i++)
    fscanf(in,"%d",&(digits [i]));
  for(i=0;i<digits_used;i++)
    {
      mi [0]=digits [i];
      for(j=0;j<digits_used;j++)
	{
	  mi [1]=digits [j];
	  for(k=0;k<digits_used;k++)
	    {
	      mi [2]=digits [k];
	      for(l=0;l<digits_used;l++)
		{
		  mii [0]=digits [l];
		  for(q=0;q<digits_used;q++)
		    {
		      mii [1]=digits [q];
		      if(possible(mi,mii,digits_used,digits))
			{
			  solutions++;
			  /*printf("%d%d%d * %d%d\n",mi [0],mi [1],mi [2],mii [0],mii [1]);*/
			}
		    }
		}
	    }
	}
    }
  fprintf(out,"%d\n",solutions);
  /*printf("%d\n",solutions);*/
  free(digits);
  fclose(in);
  fclose(out);
  return 0;
}
