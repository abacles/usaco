/*
 ID: abacles1
 LANG: C
 TASK: milk4
 */

#include <stdio.h>
#include <stdlib.h>

int comp(const void *va, const void *vb)
{
  int a = *(int*)va, b = *(int*)vb;
  return a - b;
}

int fillable(int buckets[], int perm[], int nbuckets, int milk)
{
  char canfill[20001] = {0};
  int i, j;
  canfill[0] = 1;
  for(i=0;i<=milk-buckets[perm[0]];i++)
  {
    if(canfill[i])
    {
      for(j=0;j<nbuckets;j++)
      {
        if(i + buckets[perm[j]] < milk)
          canfill[i+buckets[perm[j]]] = 1;
        else if(i + buckets[perm[j]] == milk)
          return 1;
      }
    }
  }
  return 0;
}

int next(int a[], int len, int max)
{
  int i, j;
  for(i=len-1;i>=0;i--)
  {
    if(a[i]+len-i-1 < max)
    {
      a[i]++;
      for(j=1;i+j<len;j++)
        a[i+j] = a[i] + j;
      return 1;
    }
  }
  return 0;
}

int main()
{
  FILE *in = fopen("milk4.in", "r"), *out = fopen("milk4.out", "w");
  int buckets[10000], perm[10000], nbuckets, milk, i, j;
  fscanf(in, "%d%d", &milk, &nbuckets);
  for(i=0;i<nbuckets;i++)
    fscanf(in, "%d", &buckets[i]);
  qsort(buckets, nbuckets, sizeof(int), comp);
  for(i=1;i<=nbuckets;i++)
  {
    for(j=0;j<i;j++)
      perm[j] = j;
    do
    {
      if(fillable(buckets, perm, i, milk))
      {
        fprintf(out, "%d", i);
        for(j=0;j<i;j++)
          fprintf(out, " %d", buckets[perm[j]]);
        fprintf(out, "\n");
        return 0;
      }
    } while(next(perm, i, nbuckets-1));
  }
  fclose(in), fclose(out);
}

