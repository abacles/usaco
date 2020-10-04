/*
  ID: abacles1
  LANG: C
  TASK: rectbarn
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX(A, B) (A>B ? A:B)
#define MIN(A, B) (A<B ? A:B)

int main()
{
  FILE *fin = fopen("rectbarn.in", "r"), *fout = fopen("rectbarn.out", "w");
  int r, c, n, a, b, area = 0, i, j;
  short up[2][3000], left[2][3000], right[2][3000];
  char *map[3000];
  fscanf(fin, "%d %d %d", &r, &c, &n);
  for(i=0; i<r; i++)
    map[i] = calloc(c, sizeof(char));
  for(i=0; i<n; i++)
    {
      fscanf(fin, "%d %d", &a, &b);
      map[a-1][b-1] = 1;
    }
  for(i=0; i<r; i++)
    {
      a = b = -1;
      for(j=0; j<c; j++)
	{
	  if(map[i][j])
	    {
	      up[i%2][j] = 0;
	      left[i%2][j] = -1;
	      right[i%2][j] = c;
	      a = j;
	    }
	  else
	    {
	      up[i%2][j] = i > 0 ? (up[(i-1)%2][j] + 1) : (1);
	      left[i%2][j] = i > 0 ? MAX(a, left[(i-1)%2][j]) : a;
	      if(b <= j)
		for(b=j+1; b<c && !map[i][b]; b++);
	      right[i%2][j] = i > 0 ? MIN(b, right[(i-1)%2][j]) : b;
	    }
	  if(up[i%2][j] * (right[i%2][j]-left[i%2][j]-1) > area)
	    area = up[i%2][j] * (right[i%2][j]-left[i%2][j]-1);
	}
    }
  fprintf(fout, "%d\n", area);
  fclose(fin), fclose(fout);
  for(i=0; i<r; i++)
    free(map[i]);
}
