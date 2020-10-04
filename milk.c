/*
ID: abacles1
LANG: C
TASK: milk
*/

#include <stdio.h>
#include <stdlib.h>

struct prov
{
  int price;
  long int supply;
};

int price_cmp(const void *a,const void *b)
{
  struct prov *aprov=(struct prov *)a,*bprov=(struct prov *)b;
  if(aprov->price<bprov->price)
    return -1;
  else if(aprov->price>bprov->price)
    return 1;
  else
    return 0;
}

int main()
{
  FILE *in=fopen("milk.in","r"),*out=fopen("milk.out","w");
  long int req,reqed=0,currreq,cost=0;
  int farmers;
  struct prov *suppliers;
  int i;
  fscanf(in,"%ld %d",&req,&farmers);
  suppliers=malloc(sizeof(struct prov)*farmers);
  for(i=0;i<farmers;i++)
    fscanf(in,"%d %ld",&(suppliers [i].price),&(suppliers [i].supply));
  qsort(suppliers,farmers,sizeof(struct prov),&price_cmp);
  for(i=0;reqed<req;i++)
    {
      if(reqed+suppliers [i].supply<=req)
	currreq=suppliers [i].supply;
      else
	currreq=req-reqed;
      cost+=suppliers [i].price*currreq;
      reqed+=currreq;
    }
  /*
  for(i=0;i<farmers;i++)
    {
      printf("%d %ld\n",suppliers [i].price,suppliers [i].supply);
    }
  */
  fprintf(out,"%ld\n",cost);
  free(suppliers);
  fclose(in);
  fclose(out);
  return 0;
}
