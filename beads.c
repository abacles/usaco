/*
ID: abacles1
LANG: C
TASK: beads
*/

#include <stdio.h>
#include <stdlib.h>

int connects(char *nl,int i,int direction)
{
  
}

int main()
{
  FILE *in=fopen("beads.in","r"),*out=fopen("beads.out","w");
  int beadcount,i,j,coll,maxcoll=0;
  char *necklace,*sspace,rcolor;
  fscanf(in,"%d",&beadcount);
  necklace=malloc(sizeof(char)*(beadcount+2));
  sspace=malloc(sizeof(char)*(beadcount*2+1));
  fscanf(in,"%s",necklace);
  for(i=0;necklace [i]!='\n' && necklace [i]!='\0';i++)
    {
      sspace [i]=necklace [i];
      sspace [i+beadcount]=necklace [i];
    }
  sspace [beadcount*2]='\0';
  for(i=0;sspace [i]!='\0';i++)
    {
      /*Break at ...i and i+1...*/
      coll=2; /*Automatically two beads are collected, beadcount>=3*/
      for(rcolor=sspace [i],j=i-1;j>=0 && rcolor=='w';j--)
	{
	  rcolor=sspace [j];
	}
      /*All 'w's will be handled nicely*/
      for(j=i-1;j>=0;j--)
	{
	  if(sspace [j]!=rcolor && sspace [j]!='w')
	      break;
	  coll++;
	}
      for(rcolor=sspace [i+1],j=i+2;j<beadcount*2 && rcolor=='w';j++)
	{
	  rcolor=sspace [j];
	}
      for(j=i+2;sspace [j]!='\0';j++)
	{
	  if(sspace [j]!=rcolor && sspace [j]!='w')
	    break;
	  coll++;
	}
      if(coll>beadcount)
	coll=beadcount;
      if(coll>maxcoll)
	maxcoll=coll;
    }
  fprintf(out,"%d\n",maxcoll);
  free(necklace);
  free(sspace);
  fclose(in);
  fclose(out);
  return 0;
}
