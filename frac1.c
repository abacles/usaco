/*
ID: abacles1
LANG: C
TASK: frac1
*/

#include <stdio.h>
#include <stdlib.h>

#define CEILHALF(A) (A%2==0?A/2:A/2+1)

struct frac
{
  int numer;
  int denom;
};

int gcf(int a,int b)
{
  if(a==0 || b==0)
    return a+b;
  if(a > b)
    return gcf(a%b,b);
  return gcf(b%a,a);
}

int lcm(int a,int b)
{
  return (a/gcf(a,b))*b;
}

void simplify(struct frac *f)
{
  int factor;
  if(f->numer==1 || (f->denom - f->numer == 1))
    return;
  factor = gcf(f->numer,f->denom);
  f->numer /= factor;
  f->denom /= factor;
}

int compar(const void *a,const void *b)
{
  struct frac *fa = (struct frac *)a;
  struct frac *fb = (struct frac *)b;
  int cd = lcm(fa->denom,fb->denom);
  int newa = fa->numer * (cd/fa->denom);
  int newb = fb->numer * (cd/fb->denom);
  return newa - newb;
}

int main()
{
  FILE *in,*out;
  int maxdenom;
  struct frac *all;
  int i,j,count = 0;

  in = fopen("frac1.in","r");
  fscanf(in,"%d",&maxdenom);
  fclose(in);

  for(i=2;i<=maxdenom;i++)
    {
      for(j=1;j<CEILHALF(i);j++)
	count++;
    }
  
  all = malloc(sizeof(struct frac)*count);

  count = 0;
  for(i=2;i<=maxdenom;i++)
    {
      for(j=1;j<CEILHALF(i);j++)
	{
	  all[count].denom = i;
	  all[count].numer = j;
	  simplify(all+count);
	  count++;
	}
    }

  qsort(all,count,sizeof(struct frac),compar);

  out = fopen("frac1.out","w");
  fprintf(out,"0/1\n");
  for(i=0;i<count;i++)
    {
      if(i==0 || all[i].numer!=all[i-1].numer || all[i].denom!=all[i-1].denom)
	fprintf(out,"%d/%d\n",all[i].numer,all[i].denom);
    }
  if(maxdenom >= 2)
    fprintf(out,"1/2\n");
  for(i=count-1;i>=0;i--)
    {
      if(i==0 || all[i].numer!=all[i-1].numer || all[i].denom!=all[i-1].denom)
	fprintf(out,"%d/%d\n",all[i].denom-all[i].numer,all[i].denom);
    }
  fprintf(out,"1/1\n");

  fclose(out);
  free(all);
  return 0;
}
