/*
 ID: abacles1
 LANG: C
 TASK: frameup
 */

#include <stdio.h>

struct rect
{
  int s, x, z, y;
} frames[26];

char wall[30][31], ontop[26][26] = {0}, seen[26] = {0};

int max(int a, int b)
{
  return a > b ? a : b;
}
int min(int a, int b)
{
  return a < b ? a : b;
}

void trace(int f, int h, int w)
{
  int i;
  for(i=frames[f].s;i<=frames[f].x;i++)
  {
    if(wall[i][frames[f].z] != 'A' + f)
      ontop[wall[i][frames[f].z]-'A'][f] = 1;
    if(wall[i][frames[f].y] != 'A' + f)
      ontop[wall[i][frames[f].y]-'A'][f] = 1;
  }
  for(i=frames[f].z;i<=frames[f].y;i++)
  {
    if(wall[frames[f].s][i] != 'A' + f)
      ontop[wall[frames[f].s][i]-'A'][f] = 1;
    if(wall[frames[f].x][i] != 'A' + f)
      ontop[wall[frames[f].x][i]-'A'][f] = 1;
  }
}

void dfs(FILE *f, char *prev, int prevlen, int totlen)
{
  int next[26], n = 0, temp[26], t, i, j;
  if(prevlen == totlen)
  {
    fprintf(f, "%s\n", prev);
    return;
  }
  for(i=0;i<26;i++)
  {
    for(j=0;j<26 && !ontop[i][j];j++);
    if(j == 26 && seen[i])
    {
      for(j=0;j<prevlen && prev[j]!='A'+i;j++);
      if(j == prevlen)
        next[n++] = i;
    }
  }
  for(i=0;i<n;i++)
  {
    prev[prevlen] = 'A' + next[i];
    prev[prevlen+1] = 0;
    t = 0;
    for(j=0;j<26;j++)
    {
      if(ontop[j][next[i]])
      {
        ontop[j][next[i]] = 0;
        temp[t++] = j;
      }
    }
    dfs(f, prev, prevlen+1, totlen);
    for(j=0;j<t;j++)
      ontop[temp[j]][next[i]] = 1;
  }
}

int main()
{
  FILE *in = fopen("frameup.in", "r"), *out = fopen("frameup.out", "w");
  int width, height, nframes = 0, i, j;
  char ordering[27] = "";
  fscanf(in, "%d %d", &height, &width);
  for(i=0;i<height;i++)
    fscanf(in, "%s", wall[i]);
  for(i=0;i<26;i++)
  {
    frames[i].s = height - 1;
    frames[i].x = frames[i].y = 0;
    frames[i].z = width - 1;
  }
  for(i=0;i<height;i++)
  {
    for(j=0;j<width;j++)
    {
      if(wall[i][j] != '.')
      {
        seen[wall[i][j]-'A'] = 1;
        frames[wall[i][j]-'A'].s = min(frames[wall[i][j]-'A'].s, i);
        frames[wall[i][j]-'A'].x = max(frames[wall[i][j]-'A'].x, i);
        frames[wall[i][j]-'A'].z = min(frames[wall[i][j]-'A'].z, j);
        frames[wall[i][j]-'A'].y = max(frames[wall[i][j]-'A'].y, j);
      }
    }
  }
  for(i=0;i<26;i++)
  {
    if(seen[i])
    {
      trace(i, height, width);
      nframes++;
    }
  }
  dfs(out, ordering, 0, nframes);
  fclose(in), fclose(out);
}
