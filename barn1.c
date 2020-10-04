/*
ID: abacles1
LANG: C
TASK: barn1
*/

#include <stdio.h>
#include <stdlib.h>

/*#define DEBUG 1*/

struct stall
{
  int cow;
  int board;
};

void print_state(struct stall barn [],int size)
{
  int i;
  for(i=0;i<size;i++)
    {
      if(barn [i].board)
	printf("_");
      else
	printf(" ");
    }
  printf("\n");
  for(i=0;i<size;i++)
    {
      if(barn [i].cow)
	printf("M");
      else
	printf("O");
    }
  printf("\n");
}

void remove_longest_gap(struct stall barn [],int size)
{
  int currgap=0,cgs,cge,maxgap=0,mgs,mge;
  int i;
  for(i=0;i<size;i++)
    {
      if(!barn [i].cow && barn [i].board)
	{
	  if(currgap==0)
	    cgs=i;
	  currgap++;
	}
      else
	{
	  cge=i; /*Exclusive*/
	  if(currgap>maxgap)
	    {
	      maxgap=currgap;
	      mgs=cgs;
	      mge=cge;
	    }
	  currgap=0;
	}
    }
#ifdef DEBUG
  printf("[%d, %d)\n",mgs,mge);
#endif
  for(i=mgs;i<mge;i++)
    barn [i].board=0;
}

int main()
{
  FILE *in=fopen("barn1.in","r"),*out=fopen("barn1.out","w");
  int maxboards,stalls,filled,boards_used=0,tboardlen=0;
  int *occupied;
  struct stall *barn;
  int i,first_board=-1,last_board=-1;
  fscanf(in,"%d %d %d",&maxboards,&stalls,&filled);
  occupied=malloc(sizeof(int)*filled);
  barn=malloc(sizeof(struct stall)*stalls);
  for(i=0;i<stalls;i++)
    {
      barn [i].cow=0;
      barn [i].board=0;
    }
  for(i=0;i<filled;i++)
    {
      fscanf(in,"%d",&(occupied [i]));
      barn [occupied [i]-1].cow=1;
      if(occupied [i]-1<first_board || first_board==-1)
	first_board=occupied [i]-1;
      if(occupied [i]-1>last_board || last_board==-1)
	last_board=occupied [i]-1;
    }
  for(i=first_board;i<=last_board;i++)
    barn [i].board=1;
#ifdef DEBUG
  printf("[%d, %d]\n",first_board,last_board);
  print_state(barn,stalls);
#endif
  for(boards_used=1;boards_used<maxboards;boards_used++)
    {
      remove_longest_gap(barn,stalls);
#ifdef DEBUG
      print_state(barn,stalls);
#endif
    }
  for(i=0;i<stalls;i++)
    {
      if(barn [i].board)
	tboardlen++;
    }
  fprintf(out,"%d\n",tboardlen);
#ifdef DEBUG
  printf("%d\n",tboardlen);
#endif
  free(occupied);
  free(barn);
  fclose(in);
  fclose(out);
  return 0;
}
