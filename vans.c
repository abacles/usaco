/*
  ID: abacles1
  LANG: C
  TASK: vans
*/

#include <stdio.h>
#include <stdlib.h>

#define BIG 1000000
#define MAX(A, B) (A>B ? A:B)

struct bignum
{
  int coef[200], len;
};

struct bignum *dp;

void print(FILE *f, struct bignum a)
{
  int i;
  fprintf(f, "%d", a.coef[a.len-1]);
  for(i=a.len-2; i>=0; i--)
    fprintf(f, "%06d", a.coef[i]);
  fprintf(f, "\n");
}

void add(struct bignum *a, struct bignum b)
{
  int i, carry = 0;
  for(i=0; i<MAX(a->len, b.len); i++)
    {
      if(i >= a->len) a->coef[i] = 0;
      if(i >= b.len) b.coef[i] = 0;
      a->coef[i] += b.coef[i] + carry;
      carry = a->coef[i] / BIG;
      a->coef[i] %= BIG;
    }
  a->len = MAX(a->len, b.len);
  if(carry)
    a->coef[(a->len)++] = carry;
}

struct bignum mult(int s, struct bignum a)
{
  int i, carry = 0, tmp;
  for(i=0; i<a.len; i++)
    {
      tmp = a.coef[i] * s + carry;
      carry = tmp / BIG;
      a.coef[i] = tmp % BIG;
    }
  while(carry)
    {
      a.coef[a.len++] = carry % BIG;
      carry /= BIG;
    }
  return a;
}

struct bignum nspaths(int n)
{
  int i, j;
  struct bignum p;
  p.coef[0] = 0; p.len = 1;
  if(n == 2)
    {
      p.coef[0] = 1;
      return p;
    }
  if(dp[n].len != 0)
    return dp[n];
  if(n > 3)
    add(&p, mult(3, nspaths(n-2)));
  for(i=2; i<n-2; i++)
    add(&p, mult(2*i, nspaths(n-i-1)));
  return dp[n] = p;
}

int main()
{
  FILE *fin = fopen("vans.in", "r"), *fout = fopen("vans.out", "w");
  int n, i;
  struct bignum paths;
  dp = malloc(sizeof(struct bignum) * 1001);
  paths.coef[0] = 0; paths.len = 1;
  for(i=0; i<1001; dp[i++].len=0);
  fscanf(fin, "%d", &n);
  for(i=0; i<n-1; i++)
    add(&paths, mult(i+1, nspaths(n-i)));
  paths = mult(2, paths);
  print(fout, paths);
  free(dp);
  fclose(fin), fclose(fout);
}
