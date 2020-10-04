/*
  ID: abacles
  LANG: C
  TASK: game1
*/

#include <stdio.h>

int board[100];
int scores[101][101][2] = {0};

int turn(int passed)
{
  return passed % 2;
}

void calc(int size)
{
  int i,j,t;
  for(i=1;i<=size;i++)
    {
      for(j=0;j<=size-i;j++)
	{
	  if(scores[j+1][j+i][turn(size-i)] + board[j] > scores[j][j+i-1][turn(size-i)] + board[j+i-1])
	    {
	      scores[j][j+i][turn(size-i)] = scores[j+1][j+i][turn(size-i)] + board[j];
	      scores[j][j+i][!turn(size-i)] = scores[j+1][j+i][!turn(size-i)];
	    }
	  else
	    {
	      scores[j][j+i][turn(size-i)] = scores[j][j+i-1][turn(size-i)] + board[j+i-1];
	      scores[j][j+i][!turn(size-i)] = scores[j][j+i-1][!turn(size-i)];
	    }
	}
    }
}

int main()
{
  FILE *in = fopen("game1.in","r"),*out = fopen("game1.out","w");
  int boardsize,i;
  fscanf(in,"%d",&boardsize);
  for(i=0;i<boardsize;i++)
    fscanf(in,"%d",&board[i]);
  fclose(in);
  calc(boardsize);
  fprintf(out,"%d %d\n",scores[0][boardsize][0],scores[0][boardsize][1]);
  fclose(out);
}
