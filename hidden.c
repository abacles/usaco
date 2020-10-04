/*
  ID: abacles1
  LANG: C
  TASK: hidden
*/

#include <stdio.h>

void bucket_sort(int a[], int key[], int len, int v, int frontshift)
{
  int buckets[100000] = {0}, pos[100000], sorted[100000], i;
  for(i=0;i<len;i++)
    buckets[key[i]]++;
  for(i=1,pos[0]=0;i<v;i++)
    pos[i] = pos[i-1] + buckets[i-1];	
  for(i=0;i<len;i++)
    sorted[pos[key[(a[i]-frontshift+len)%len]]++] = (a[i]-frontshift+len) % len;
  for(i=0;i<len;i++)
    a[i] = sorted[i];
}

int cyclic_sort(char str[], int len)
{
  int order[100000], class[100000], newclass[100000], nclasses = 26, i, min, l;
  for(i=0;i<len;i++)
    {
      order[i] = i;
      class[i] = str[i] - 'a';
    }
  for(l=1;l<len;l*=2)
    {
      bucket_sort(order, class, len, nclasses+1, l/2);
      newclass[order[0]] = nclasses = 0;
      for(i=1;i<len;i++)
	{
	  if(class[order[i]] == class[order[i-1]] && class[(order[i]+l/2)%len] == class[(order[i-1]+l/2)%len])
	    newclass[order[i]] = nclasses;
	  else
	    newclass[order[i]] = ++nclasses;
	}
      for(i=0;i<len;i++)
	class[i] = newclass[i];
    }
  for(i=1,min=order[0]; i<len && class[order[i]]==class[order[i-1]]; i++)
    {
      if(order[i] < min)
	min = order[i];
    }
  return min;
}

int main()
{
  FILE *fin = fopen("hidden.in", "r"), *fout = fopen("hidden.out", "w");
  char str[100001], ch;
  int len, i;
  fscanf(fin, "%d", &len);
  for(i=0;i<len;i++)
    {
      while((ch=fgetc(fin)) == '\n');
      str[i] = ch;
    }
  str[len] = '\0';
  fprintf(fout, "%d\n", cyclic_sort(str, len));
  fclose(fin); fclose(fout);
}
