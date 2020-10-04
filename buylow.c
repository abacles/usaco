/*
 ID: abacles1
 LANG: C
 TASK: buylow
 */

#include <stdio.h>
#include <stdlib.h>

#define BASE 1000000

struct bignum
{
  int val;
  struct bignum *higher;
};

struct bignum *small(int v)
{
  struct bignum *new = malloc(sizeof(struct bignum));
  new->val = v;
  new->higher = NULL;
  return new;
}

void print(FILE *f, struct bignum *n)
{
  struct bignum *digs[20];
  int i;
  for(i=0;n;digs[i++]=n,n=n->higher);
  fprintf(f, "%d", digs[--i]->val);
  for(i--;i>=0;i--)
    fprintf(f, "%06d", digs[i]->val);
}

void add(struct bignum *a, struct bignum *b)
{
  int carry = 0;
  for(;b;a=a->higher, b=b->higher)
  {
    a->val += b->val + carry;
    carry = a->val / BASE;
    a->val %= BASE;
    if(!a->higher && (b->higher || carry))
      a->higher = small(0);
  }
  if(carry)
    a->val = carry;
}

void bigfree(struct bignum *n)
{
  if(n->higher)
    bigfree(n->higher);
  free(n);
}

int main()
{
  FILE *in = fopen("buylow.in", "r"), *out = fopen("buylow.out", "w");
  int ndays, prices[5001], rlen[5001], i, j, clen, prev;
  struct bignum *nseq[5001], *cnseq;
  fscanf(in, "%d", &ndays);
  for(i=0;i<ndays;i++)
    fscanf(in, "%d", &prices[i]);
  prices[ndays] = 0;
  for(i=0;i<=ndays;i++)
  {
    clen = 1;
    cnseq = small(1);
    prev = 0;
    for(j=i-1;j>=0;j--)
    {
      if(prices[j] > prices[i])
      {
        if(rlen[j] + 1 > clen)
        {
          clen = rlen[j] + 1;
          bigfree(cnseq);
          cnseq = small(0);
        }
        if(rlen[j] + 1 == clen && prices[j] != prev)
        {
          add(cnseq, nseq[j]);
          prev = prices[j];
        }
      }
    }
    rlen[i] = clen;
    nseq[i] = cnseq;
  }
  fprintf(out, "%d ", rlen[ndays]-1);
  print(out, nseq[ndays]);
  fprintf(out, "\n");
  for(i=0;i<ndays;i++)
    bigfree(nseq[i]);
  fclose(in), fclose(out);
}
