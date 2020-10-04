/*
 ID: abacles
 LANG: C
 TASK: lgame
 */

#include <stdio.h>
#include <string.h>

int points[26] = {2, 5, 4, 4, 1, 6, 5, 5, 1, 7, 6, 3, 5, 2, 3, 5, 7, 2, 1, 2, 4, 6, 6, 7, 5, 7};

void tally(char *str, char cc[])
{
  int i;
  for(i=0;str[i];i++)
    cc[str[i]-'a']++;
}

int val(char *str)
{
  int v = 0, i;
  for(i=0;str[i];i++)
    v += points[str[i]-'a'];
  return v;
}

int main()
{
  FILE *in = fopen("lgame.in", "r"), *dict = fopen("lgame.dict", "r"), *out = fopen("lgame.out", "w");
  char given[8], have[26] = {0}, word[8], need[26], psb[10000][8], pts[10000];
  int npsb = 0, maxpts = 0, best[500][2], nbest = 0, i, j, k;
  fscanf(in, "%s", given);
  tally(given, have);
  while(fscanf(dict, "%s", word), word[0] != '.')
  {
    memset(need, 0, 26);
    tally(word, need);
    for(i=0;i<26 && have[i] >= need[i];i++);
    if(i == 26)
    {
      strcpy(psb[npsb], word);
      pts[npsb] = val(word);
      maxpts = pts[npsb] > maxpts ? pts[npsb] : maxpts;
      npsb++;
    }
  }
  for(i=0;i<npsb;i++)
  {
    if(pts[i] == maxpts)
    {
      best[nbest][0] = i;
      best[nbest++][1] = -1;
    }
    for(j=i;j<npsb;j++)
    {
      if(pts[i] + pts[j] >= maxpts)
      {
        memset(need, 0, 26);
        tally(psb[i], need), tally(psb[j], need);
        for(k=0;k<26 && have[k] >= need[k];k++);
        if(k == 26)
        {
          if(pts[i] + pts[j] > maxpts)
          {
            nbest = 0;
            maxpts = pts[i] + pts[j];
          }
          best[nbest][0] = i;
          best[nbest++][1] = j;
        }
      }
    }
  }
  fprintf(out, "%d\n", maxpts);
  for(i=0;i<nbest;i++)
  {
    if(best[i][1] == -1)
      fprintf(out, "%s\n", psb[best[i][0]]);
    else
      fprintf(out, "%s %s\n", psb[best[i][0]], psb[best[i][1]]);
  }
  fclose(in), fclose(dict), fclose(out);
}
