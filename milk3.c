/*
ID: abacles1
LANG: C
TASK: milk3
*/

#include <stdio.h>
#include <stdlib.h>

int abs(int a)
{
  return (a<0)?-a:a;
}

int min(int a,int b)
{
  return (a<b)?a:b;
}

void sort(int a [],int len)
{
  int i,j,temp;
  for(i=0;i<len;i++)
    {
      for(j=i+1;j<len;j++)
	{
	  if(a[i] > a[j])
	    {
	      temp = a [i];
	      a [i] = a [j];
	      a [j] = temp;
	    }
	}
    }
}

int exist(int new,int a [],int len)
{
  int i;
  for(i=0;i<len;i++)
    {
      if(a[i] == new)
	return 1;
    }
  return 0;
}

int spill(int amount,int bcup,int ccup)
{
  if(ccup-amount > bcup || amount > ccup)
    return 1;
  return 0;
}

int main()
{
  FILE *in,*out;
  int a,b,c;
  int total;
  int *poss,found = 0;
  int i,j,k;

  in = fopen("milk3.in","r");
  fscanf(in,"%d %d %d",&a,&b,&c);
  fclose(in);

  total = c;
  poss = malloc(sizeof(int)*(min(b,c)+1));

  poss [found] = c;
  found++;
  if(!spill(a,b,c) && c>a)
    {
      poss [found] = a;
      found++;
    }
  if(c>=b)
    {
      poss [found] = c-b;
      found++;
    }
  else
    {
      poss [found] = 0;
      found++;
    }
  for(i=0;i<found;i++)
    {
      /* original: 0 y x */
      /* new: 0 something x-a y-a x+a y+a x-abs(a-b) x+abs(a-b) y+b */
      if(!spill(poss[i]-a,b,c) && poss[i]>=a)
	{
	  if(!exist(poss[i]-a,poss,found))
	    {
	      poss [found] = poss [i]-a;
	      found++;
	    }
	}
      if(!spill(total-poss[i]-a,b,c) && total-poss[i]>=a)
	{
	  if(!exist(total-poss[i]-a,poss,found))
	    {
	      poss [found] = total-poss [i]-a;
	      found++;
	    }
	}
      if(!spill(poss[i]+a,b,c) && total-poss[i]>=a)
	{
	  if(!exist(poss[i]+a,poss,found))
	    {
	      poss [found] = poss [i]+a;
	      found++;
	    }	  
	}
      if(!spill(total-poss[i]+a,b,c) && poss[i]>=a)
	{
	  if(!exist(total-poss[i]+a,poss,found))
	    {
	      poss [found] = total-poss [i]+a;
	      found++;
	    }
	}
      if(!spill(poss[i]+abs(a-b),b,c) && total-poss[i]<=a && poss[i]>=b)
	{
	  if(!exist(poss[i]+abs(a-b),poss,found))
	    {
	      poss [found] = poss[i]+abs(a-b);
	      found++;
	    }
	}
      if(!spill(poss[i]-abs(a-b),b,c) && total-poss[i]<=a && poss[i]>=b)
	{
	  if(!exist(poss[i]-abs(a-b),poss,found))
	    {
	      poss [found] = poss[i]-abs(a-b);
	      found++;
	    }
	}
      if(!spill(total-poss[i]+b,b,c) && total-poss[i]+b<=a && poss[i]>=b)
	{
	  if(!exist(total-poss[i]+b,poss,found))
	    {
	      poss [found] = total-poss[i]+b;
	      found++;
	    }
	}
    }

  sort(poss,found);

  out = fopen("milk3.out","w");

  for(i=0;i<found;i++)
    {
      fprintf(out,"%d",poss [i]);
      if(i < found-1)
	fprintf(out," ");
    }
  fprintf(out,"\n");
  
  fclose(out);
  free(poss);
  return 0;
}
