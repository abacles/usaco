/*
 ID: abacles1
 LANG: C
 TASK: job
 */

#include <stdio.h>

int work(int n, int nmach, int mach[], int time[])
{
  int max = 0, min, pd, mtime[30], i;
  for(i=0;i<nmach;i++) mtime[i] = 0;
  for(pd=0;pd<n;pd++)
  {
    for(min=-1,i=0;i<nmach;i++)
    {
      if(min==-1 || mtime[min] + mach[min] > mtime[i] + mach[i])
        min = i;
    }
    time[pd] = mtime[min] += mach[min];
    if(time[pd] > max) max = time[pd];
  }
  return max;
}

void sort(int a[], int len, int dir)
{
  int i, j, temp;
  for(i=0;i<len;i++)
  {
    for(j=i+1;j<len;j++)
    {
      if(dir * (a[j]-a[i]) < 0)
      {
        temp = a[i];
        a[i] = a[j];
        a[j] = temp;
      }
    }
  }
}

int main()
{
  FILE *in = fopen("job.in","r"), *out = fopen("job.out","w");
  int njobs, nmacha, nmachb, macha[30], machb[30], i, max = 0;
  int adone[1000], bstart[1000];
  fscanf(in,"%d %d %d",&njobs,&nmacha,&nmachb);
  for(i=0;i<nmacha;i++) fscanf(in,"%d",&macha[i]);
  for(i=0;i<nmachb;i++) fscanf(in,"%d",&machb[i]);
  fprintf(out,"%d ",work(njobs,nmacha,macha,adone));
  work(njobs,nmachb,machb,bstart);
  sort(adone,njobs,1);
  sort(bstart,njobs,-1);
  for(i=0;i<njobs;i++)
  {
    if(adone[i] + bstart[i] > max)
      max = adone[i] + bstart[i];
  }
  fprintf(out,"%d\n",max);
  fclose(in), fclose(out);
}
