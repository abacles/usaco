/*
ID: abacles1
LANG: C
TASK: combo
*/

#include <stdio.h>

int wrapadd(int orig,int add,int wrap)
{
  int raw=orig+add;
  while(raw>wrap)
    raw-=wrap;
  while(raw<=0)
    raw+=wrap;
  return raw;
}

int tolerate(int ex,int test,int max)
{
  if(test==wrapadd(ex,-2,max) || test==wrapadd(ex,-1,max) || test==ex || test==wrapadd(ex,1,max) || test==wrapadd(ex,2,max))
    return 1;
  else
    return 0;
}

int main()
{
  FILE *in=fopen("combo.in","r"),*out=fopen("combo.out","w");
  int max,possible=0;
  int farmer [3],master [3],curr [3];
  int i,j,k,iex=0,jex=0,kex=0;
  fscanf(in,"%d",&max);
  fscanf(in,"%d %d %d",&(farmer [0]),&(farmer [1]),&(farmer [2]));
  fscanf(in,"%d %d %d",&(master [0]),&(master [1]),&(master [2]));
  if(max>=5)
    possible=5*5*5;
  else
    possible=max*max*max;
  for(i=wrapadd(master [0],-2,max);tolerate(master [0],i,max) && iex<max;i=wrapadd(i,1,max))
    {
      jex=0;
      for(j=wrapadd(master [1],-2,max);tolerate(master [1],j,max) && jex<max;j=wrapadd(j,1,max))
	{
	  kex=0;
	  for(k=wrapadd(master [2],-2,max);tolerate(master [2],k,max) && kex<max;k=wrapadd(k,1,max))
	    {
	      if(!(tolerate(farmer [0],i,max) && tolerate(farmer [1],j,max) && tolerate(farmer [2],k,max)))
		possible++;
	      kex++;
	    }
	  jex++;
	}
      iex++;
    }
  fprintf(out,"%d\n",possible);
  /*printf("%d\n",possible);*/
  fclose(in);
  fclose(out);
  return 0;
}
