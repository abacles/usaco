/*
  ID: abacles1
  LANG: C
  TASK: theme
*/

#include <stdio.h>

int main()
{
  FILE *in = fopen("theme.in", "r"), *out = fopen("theme.out", "w");
  int nnotes, notes[5000], diffs[4999], longest = 0, i, j, k;
  fscanf(in, "%d", &nnotes);
  for(i=0;i<nnotes;i++) fscanf(in, "%d", &notes[i]);
  for(i=1;i<nnotes;diffs[i-1]=notes[i]-notes[i-1],i++);
  for(i=0;i+longest+1<nnotes;i++)
    {
      for(j=nnotes-longest-1;j>i+longest;j--)
	{
	  for(k=0;i+k+1<j && j+k<nnotes && diffs[i+k]==diffs[j+k];k++);
	  longest = k+1>longest ? k+1 : longest;
	}
    }
  fprintf(out, "%d\n", longest>=5 ? longest : 0);
  fclose(in), fclose(out);
}
