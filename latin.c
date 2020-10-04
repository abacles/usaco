/*
  ID: abacles1
  LANG: C
  TASK: latin
*/

#include <stdio.h>

int row[7], col[7], ones;

int fac(int x)
{
  if (x <= 1)
    return 1;
  return x * fac(x-1);
}

long long search(int size, int i)
{
  int row_orig, col_orig, r = i/size, c = i%size, x, k, tmp;
  long long count = 0;
  if (c == 0 && r == size-1)
    return 1;
  else if (c == 0)
    return search(size, i+1);
  if (!(x = row[r] & col[c]))
    return 0;
  row_orig = row[r];
  col_orig = col[c];
  for (k=0; k<size; k++)
    {
      if ((1 << k) & x)
	{
	  row[r] &= ~(1 << k);
	  col[c] &= ~(1 << k);
	  
	  if (i < 2*size && k == c+1)
	    {
	      tmp = count + (size-k) * search(size, i+1);
	      row[r] = row_orig;
	      col[c] = col_orig;
	      return tmp;
	    }

	  count += search(size, i+1);
	  
	  row[r] = row_orig;
	  col[c] = col_orig;
	}
    }
  return count;
}

int main()
{
  FILE *fin = fopen("latin.in", "r"), *fout = fopen("latin.out", "w");
  int n, i, j;
  fscanf(fin, "%d", &n);
  ones = (1 << n) - 1;
  for (i=1; i<n; i++)
    col[i] = row[i] = (1 << i) ^ ones;
  row[0] = col[0] = 0;
  fprintf(fout, "%lld\n", search(n, n) * fac(n-1));
  fclose(fin), fclose(fout);
}
