/*
ID: abacles1
LANG: C
TASK: ttwo
*/

#include <stdio.h>

int main()
{
  FILE *in,*out;
  char maze[12][12],visited[100][100][4][4];
  int i,j,k,l,cx,cy,fx,fy,ccx=0,ccy=-1,cfx=0,cfy=-1,temp;
  in = fopen("ttwo.in","r");
  for(i=1;i<=10;i++)
    {
      fscanf(in,"%s",maze[i]+1);
      maze[0][i] = maze[11][i] = maze[i][0] = maze[i][11] = '*';
      for(j=1;j<=10;j++)
	{
	  if(maze[i][j] == 'C')
	    {
	      cy = i;
	      cx = j;
	    }
	  else if(maze[i][j] == 'F')
	    {
	      fy = i;
	      fx = j;
	    }
	}
    }
  fclose(in);
  maze[0][0] = maze[0][11] = maze[11][0] = maze[11][11] = '+';

  for(i=0;i<100;i++)
    {
      for(j=0;j<100;j++)
        {
	  for(k=0;k<4;k++)
	    {
	      for(l=0;l<4;l++)
		visited[i][j][k][l] = 0;
	    }
	}
    }

  for(i=0;!visited[10*(cy-1)+cx-1][10*(fy-1)+fx-1][(5+ccx+2*ccy)%5-1][(5+cfx+2*cfy)%5-1];i++)
    {
      visited[10*(cy-1)+cx-1][10*(fy-1)+fx-1][(5+ccx+2*ccy)%5-1][(5+cfx+2*cfy)%5-1] = 1;
      if(maze[cy+ccy][cx+ccx] == '*')
	{
	  temp = ccy;
	  ccy = ccx;
	  ccx = -temp;
	}
      else
	{
	  cx += ccx;
	  cy += ccy;
	}
      if(maze[fy+cfy][fx+cfx] == '*')
	{
	  temp = cfy;
	  cfy = cfx;
	  cfx = -temp;
	}
      else
	{
	  fx += cfx;
	  fy += cfy;
	}
      if(cx==fx && cy==fy)
	{
	  out = fopen("ttwo.out","w");
	  fprintf(out,"%d\n",i+1);
	  fclose(out);
	  return 0;
	}
    }

  out = fopen("ttwo.out","w");
  fprintf(out,"0\n");
  printf("%d %d %d %d\n",cy,cx,fy,fx);
  fclose(out);
  return 0;
}
