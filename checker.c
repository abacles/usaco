/*
  ID: abacles1
  LANG: C
  TASK: checker
*/

#include <stdio.h>

int n, sol[13], used[13] = {0}, topdiag[25] = {0}, botdiag[25] = {0}, tot = 0;

void search(int row, FILE *f)
{
  int i;
  if (row == n)
    {
      if (++tot <= 3)
	for (i=0; i<n; i++)
	  fprintf(f, "%d%c", sol[i]+1, i<n-1 ? ' ':'\n');
      return;
    }
  for (i=0; i<n; i++)
    if (!used[i] && !topdiag[row+i] && !botdiag[n-row-1+i])
      {
	sol[row] = i;
	used[i] = 1;
	topdiag[row+i] = 1;
	botdiag[n-row-1+i] = 1;
	
	search(row+1, f);
	
	used[i] = 0;
	topdiag[row+i] = 0;
	botdiag[n-row-1+i] = 0;
      }
}

int main()
{
  FILE *fin = fopen("checker.in", "r"), *fout = fopen("checker.out", "w");
  fscanf(fin, "%d", &n);
  search(0, fout);
  fprintf(fout, "%d\n", tot);
  fclose(fin), fclose(fout);
}
