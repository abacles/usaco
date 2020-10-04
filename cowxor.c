/*
 ID: abacles1
 LANG: C
 TASK: cowxor
 */

#include <stdio.h>
#include <stdlib.h>

struct trie
{
  struct trie *children[2];
  int leaf;
};

struct trie *trie_new(int l)
{
  struct trie *v = malloc(sizeof(struct trie));
  v->children[0] = v->children[1] = NULL;
  v->leaf = l;
  return v;
}

void trie_free(struct trie *v)
{
  if (v->children[0])
    trie_free(v->children[0]);
  if (v->children[1])
    trie_free(v->children[1]);
  free(v);
}

void trie_insert(struct trie *v, int key, int val)
{
  int i, mask = 1<<21, bit;
  for (i=0; i<22; i++)
  {
    bit = (key & mask) != 0;
    if (!v->children[bit])
      v->children[bit] = trie_new(-1);
    v = v->children[bit];
    mask >>= 1;
  }
  v->leaf = val;
}

int trie_match(struct trie *v, int key)
{
  int i, mask = 1<<21, bit;
  for (i=0; i<22; i++)
  {
    bit = (key & mask) != 0;
    v = v->children[v->children[!bit] ? !bit:bit];
    mask >>= 1;
  }
  return v->leaf;
}

int main()
{
  FILE *fin = fopen("cowxor.in", "r"), *fout = fopen("cowxor.out", "w");
  int n, x[100000], pxor[100000], maxxor = -1, a, b, i, j;
  struct trie *root = trie_new(-1);
  fscanf(fin, "%d", &n);
  for (i=0; i<n; i++)
  {
    fscanf(fin, "%d", &x[i]);
    if (x[i] > maxxor)
    {
      maxxor = x[i];
      a = i-1; b = i;
    }
    if (i == 0)
      pxor[i] = x[i];
    else
    {
      pxor[i] = pxor[i-1] ^ x[i];
      j = trie_match(root, pxor[i]);
      if ((pxor[i] ^ pxor[j]) > maxxor)
      {
        maxxor = (pxor[i] ^ pxor[j]);
        a = j, b = i;
      }
    }
    trie_insert(root, pxor[i], i);
  }
  fprintf(fout, "%d %d %d\n", maxxor, a+2, b+1);
  fclose(fin), fclose(fout);
  trie_free(root);
}
