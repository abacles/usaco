/*
 ID: abacles1
 LANG: C
 TASK: shuttle
 */

#include <stdio.h>

int count = 0;

int lineup(int b[], int s)
{
  int i;
  for(i=0;i<s;i++)
  {
    if(b[!(s%2) + i*2] != 2 || b[!(s%2) + i*2 + 1] != 1)
      return 0;
  }
  return 1;
}

int done(int b[], int s)
{
  int i;
  for(i=0;i<s;i++)
  {
    if(b[i] != 2 || b[s+1+i] != 1)
      return 0;
  }
  return 1;
}

void shift(FILE *f, int b[], int s, int which, int repeat, int step, int i)
{
  int dir = (which == 1 ? 1 : -1);
  for(;0<=i && i<=2*s && 0<=i+dir*step && i+dir*step<=2*s;i+=(repeat?-dir:dir))
  {
    if(b[i] == which && !b[i+dir*step] && (!repeat || b[i+dir] != which))
    {
      if(count)
        fprintf(f, " ");
      fprintf(f, "%d", i+1);
      if(++count == 20)
      {
        fprintf(f, "\n");
        count = 0;
      }
      b[i] = 0;
      b[i+dir*step] = which;
      if(!repeat)
        return;
    }
  }
}

int main()
{
  FILE *in = fopen("shuttle.in", "r"), *out = fopen("shuttle.out", "w");
  int size, board[25] = {0}, turn, i;
  fscanf(in, "%d", &size);
  for(i=0;i<size;board[i]=1,board[size+1+i]=2,i++);
  for(turn=1;!lineup(board, size);turn=3-turn)
  {
    shift(out, board, size, turn, 0, 1, turn==1 ? 0 : 2*size);
    shift(out, board, size, 3-turn, 1, 2, 3-turn==1 ? 2*size-2 : 2);
  }
  for(turn=1;!done(board, size);turn=3-turn)
  {
    shift(out, board, size, turn, 0, 1, turn==1 ? 0 : 2*size);
    shift(out, board, size, turn, 1, 2, turn==1 ? 2*size-2 : 2);
  }
  if(count)
    fprintf(out, "\n");
  fclose(in), fclose(out);
}
