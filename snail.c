/*
ID: abacles1
LANG: C
TASK: snail
*/

#include <stdio.h>

int dfs(char map[200][200], int size, int i, int j, int di, int dj)
{
  char copy[200][200];
  int step = 0, left = 0, right = 0, k, l;
  /* printf("%d %d ", i, j); */
  for(;0<=i+di&&i+di<size&&0<=j+dj&&j+dj<size&&!map[i+di][j+dj];map[i][j]=2,i+=di,j+=dj,step++);
  /* printf("> %d %d\n", i, j); */
  if(step && !(0<=i+di&&i+di<size&&0<=j+dj&&j+dj<size&&map[i+di][j+dj] == 2))
    {
      for(k=0;k<size;k++)
	{
	  for(l=0;l<size;l++)
	    copy[k][l] = map[k][l];
	}
      left = dfs(copy, size, i, j, dj, di);
      for(k=0;k<size;k++)
	{
	  for(l=0;l<size;l++)
	    copy[k][l] = map[k][l];
	}
      right = dfs(copy, size, i, j, -dj, -di);
      step += left > right ? left : right;
    }
  return step;
}

int main()
{
  FILE *in = fopen("snail.in", "r"), *out = fopen("snail.out", "w");
  char square[200][200] = {0}, square2[200][200] = {0}, col;
  int size, nbarriers, i, j;
  fscanf(in, "%d %d", &size, &nbarriers);
  for(i=0;i<nbarriers;i++)
    {
      fgetc(in);
      fscanf(in, "%c%d", &col, &j);
      square2[j-1][col-'A'] = square[j-1][col-'A'] = 1;
    }
  i = dfs(square, size, 0, 0, 1, 0);
  j = dfs(square2, size, 0, 0, 0, 1);
  fprintf(out, "%d\n", (i > j ? i : j) + 1);
  fclose(in), fclose(out);
}
