/*
  ID: abacles1
  LANG: C
  TASK: rockers
*/

#include <stdio.h>

int next(int *a,int len,int count)
{
  int i;
  for(i=0;i<len;i++)
    {
      a[i] = !a[i];
      if(a[i])
	return count + 1;
      count--;
    }
  return -1;
}

int fit(int len,int *s,int *w,int cap,int n)
{
  int i,j = 0,f = 0;
  for(i=0;i<len;i++)
    {
      if(s[i])
	{
	  f += w[i];
	  if(f > cap)
	    {
	      j++;
	      f = w[i];
	      if(j == n || f > cap)
		return 0;
	    }
	}
    }
  return 1;
}

int main()
{
  FILE *in = fopen("rockers.in","r"),*out = fopen("rockers.out","w");
  int songs,cap,discs,durations[20],maxlen = 0,len = 0,i,sel[20] = {0};
  fscanf(in,"%d %d %d",&songs,&cap,&discs);
  for(i=0;i<songs;i++) fscanf(in,"%d",&durations[i]);
  while((len = next(sel,songs,len)) >= 0)
    {
      if(fit(songs,sel,durations,cap,discs) && len > maxlen)
	maxlen = len;
    }
  fprintf(out,"%d\n",maxlen);
  fclose(out);
}
