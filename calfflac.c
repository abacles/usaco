/*
 ID: abacles1
 LANG: C
 TASK: calfflac
 */

#include <stdio.h>

int main()
{
  FILE *fin = fopen("calfflac.in", "r"), *fout = fopen("calfflac.out", "w");
  char str[20001], letters[20001], ch;
  int pos[20000], len = 0, palin = 0, left, i, j, k;
  while ((ch = fgetc(fin)) != EOF)
    str[len++] = ch;
  str[len] = '\0';
  for (i=len=0; str[i]; i++)
  {
    if ('A' <= str[i] && str[i] <= 'Z')
    {
      pos[len] = i;
      letters[len++] = str[i] + 32;
    }
    else if ('a' <= str[i] && str[i] <= 'z')
    {
      pos[len] = i;
      letters[len++] = str[i];
    }
  }
  for (i=0; i<len; i++)
  {
    for (k=1; 0 <= i-k && i+k < len && letters[i-k] == letters[i+k]; k++);
    if (2*(k-1) + 1 > palin)
    {
      palin = 2*(k-1) + 1;
      left = i - k + 1;
    }
    for (k=0; 0 <= i-k && i+k+1 < len && letters[i-k] == letters[i+k+1]; k++);
    if (2*k > palin)
    {
      palin = 2*k;
      left = i - k + 1;
    }
  }
  fprintf(fout, "%d\n", palin);
  for (i=pos[left]; i <= pos[left+palin-1]; i++)
    fputc(str[i], fout);
  fputc('\n', fout);
  fclose(fin), fclose(fout);
}
