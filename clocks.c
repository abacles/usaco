/*
  ID: abacles1
  LANG: C
  TASK: clocks
*/

#include <stdio.h>

int clocks[9], moves[9][6] = {{4, 0, 1, 3, 4},
			      {3, 0, 1, 2},
			      {4, 1, 2, 4, 5},
			      {3, 0, 3, 6},
			      {5, 1, 3, 4, 5, 7},
			      {3, 2, 5, 8},
			      {4, 3, 4, 6, 7},
			      {3, 6, 7, 8},
			      {4, 4, 5, 7, 8}};
int sol[27], minsteps = 30, csol[30];

int midnight()
{
  int i;
  for (i=0; i<9; i++)
    if (clocks[i] != 12 && clocks[i] != 0)
      return 0;
  return 1;
}

void search(int v, int s)
{
  int i, j;
  if (midnight() && s < minsteps)
    {
      for (i=0; i<s; i++)
	sol[i] = csol[i];
      minsteps = s;
      return;
    }
  if (s >= 27 || v >= 9)
    return;
  for (i=0; i<4; i++)
    {
      for (j=1; j<=moves[v][0]; j++)
	clocks[moves[v][j]] = (clocks[moves[v][j]] + 3) % 12;
      csol[s+i] = v;
      search(v+1, s+(i+1)%4);
    }
}

int main()
{
  FILE *fin = fopen("clocks.in", "r"), *fout = fopen("clocks.out", "w");
  int i;
  for (i=0; i<9; i++)
    fscanf(fin, "%d", &clocks[i]);
  search(0, 0);
  for (i=0; i<minsteps; i++)
    fprintf(fout, "%d%c", sol[i]+1, i<minsteps-1 ? ' ':'\n');
  fclose(fin), fclose(fout);
}
