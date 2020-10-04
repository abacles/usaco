/*
ID: abacles1
LANG: C
TASK: twofive
*/

#include <stdio.h>

int mem[6][6][6][6][6];
char word[26];

void clear_mem()
{
  int i, j, k, l, m;
  for(i=0; i<6; i++)
    for(j=0; j<6; j++)
      for(k=0; k<6; k++)
	for(l=0; l<6; l++)
	  for(m=0; m<6; m++)
	    mem[i][j][k][l][m] = -1;
  mem[5][5][5][5][5] = 1;
}

int fill(int a, int b, int c, int d, int e)
{
  /* if you go in order, next letter always = a+b+c+d+e; any spot is ok */
  int f = 0, next = 'A' + (a+b+c+d+e);
  if(mem[a][b][c][d][e] >= 0)
    return mem[a][b][c][d][e];
  if(a < 5 && (word[a] == ' ' || word[a] == next))
    f += fill(a+1, b, c, d, e);
  if(b < a && (word[5+b] == ' ' || word[5+b] == next))
    f += fill(a, b+1, c, d, e);
  if(c < b && (word[10+c] == ' ' || word[10+c] == next))
    f += fill(a, b, c+1, d, e);
  if(d < c && (word[15+d] == ' ' || word[15+d] == next))
    f += fill(a, b, c, d+1, e);
  if(e < d && (word[20+e] == ' ' || word[20+e] == next))
    f += fill(a, b, c, d, e+1);
  return mem[a][b][c][d][e] = f;
}

int w2n(char w[])
{
  int c = 0, i, j;
  for(i=0; i<25; word[i++] = ' ');
  for(i=0; i<25; i++)
    {
      for(j=0; j<w[i]-'A'; j++)
	{
	  word[i] = 'A' + j;
	  clear_mem();
	  c += fill(0, 0, 0, 0, 0);
	}
      word[i] = w[i];
    }
  return c + 1;
}

void n2w(int m)
{
  int c = 0, i, j, tmp;
  for(i=0; i<25; word[i++] = ' ');
  for(i=0; i<25; i++)
    {
      for(j=0; ; j++)
	{
	  word[i] = 'A' + j;
	  clear_mem();
	  c += (tmp = fill(0, 0, 0, 0, 0));
	  if(c >= m)
	    break;
	}
      c -= tmp;
    }
  word[25] = '\0';
}

int main()
{
  FILE *fin = fopen("twofive.in", "r"), *fout = fopen("twofive.out", "w");
  char mode, w[26];
  int m;
  clear_mem();
  fscanf(fin, "%c", &mode);
  if(mode == 'W')
    {
      fscanf(fin, "%s", w);
      fprintf(fout, "%d\n", w2n(w));
    }
  else
    {
      fscanf(fin, "%d", &m);
      n2w(m);
      fprintf(fout, "%s\n", word);
    }
  fclose(fin), fclose(fout);
}
