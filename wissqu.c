/*
  ID: abacles1
  LANG: C
  TASK: wissqu
*/

#include <stdio.h>

#define I(C) (C-'A')

char sq[4][5], moved[4][4] = {0};
int nbs[4][4][5], newcount[5] = {0}, solution[16][3], nsol = 0;

void mv(int i, int j, char c)
{
  int dx, dy, old = I(sq[i][j]);
  for (dy=-1; dy<=1; dy++)
    for (dx=-1; dx<=1; dx++)
      if (0 <= i+dy && i+dy < 4 && 0 <= j+dx && j+dx < 4)
	--nbs[i+dy][j+dx][old], ++nbs[i+dy][j+dx][I(c)];
  sq[i][j] = c;
}

void search(char cow, int n, FILE *f)
{
  int i, j, k;
  char tmp;
  if (n >= 16 || newcount[0] > 3 || newcount[1] > 3 || newcount[2] > 3 ||
      newcount[3] > 4 || newcount[4] > 3)
    return;
  newcount[I(cow)]++;
  solution[n][0] = I(cow);
  for (i=0; i<4; i++)
    for (j=0; j<4; j++)
      if (!nbs[i][j][I(cow)] && !moved[i][j])
	{
	  solution[n][1] = i;
	  solution[n][2] = j;
	  if (newcount[0] == 3 && newcount[1] == 3 && newcount[2] == 3 &&
	      newcount[3] == 4 && newcount[4] == 3)
	    {
	      if (nsol == 0)
		{
		  for (k=0; k<16; k++)
		    fprintf(f, "%c %d %d\n", 'A'+solution[k][0], solution[k][1]+1, solution[k][2]+1);
		}
	      nsol++;
	      goto SEARCH_END;
	    }
	  
	  tmp = sq[i][j];
	  mv(i, j, cow);
	  moved[i][j] = 1;

	  for (k=0; k<5; k++)
	    search('A'+k, n+1, f);

	  mv(i, j, tmp);
	  moved[i][j] = 0;
	}
 SEARCH_END:
  newcount[I(cow)]--;
}

int main()
{
  FILE *fin = fopen("wissqu.in", "r"), *fout = fopen("wissqu.out", "w");
  int i, j, dx, dy;
  for (i=0; i<4; i++)
    fscanf(fin, "%s", sq[i]);
  for (i=0; i<4; i++)
    for (j=0; j<4; j++)
      for (dy=-1; dy<=1; dy++)
	for (dx=-1; dx<=1; dx++)
	  if (0 <= i+dy && i+dy < 4 && 0 <= j+dx && j+dx < 4)
	    nbs[i][j][I(sq[i+dy][j+dx])]++;

  search('D', 0, fout);
  fprintf(fout, "%d\n", nsol);
  fclose(fin), fclose(fout);
}
