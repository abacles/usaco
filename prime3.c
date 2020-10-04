/*
  ID: abacles1
  LANG: C
  TASK: prime3
*/

#include <stdio.h>
#include <stdlib.h>

#define BOT 10000
#define TOP 99999

char prime[100000];
int pool[1000][5], psize = 0, start[10], sq[25], sum, firstnum;
int solutions[300][25], nsol = 0;

void row1(), col1(), dia1(), row2(), col2(), row3(), col3(), row4(), col4(), final();
int checkrcd(int, int, int);

void gen_primes()
{
  int i, j, k;
  for (i=0; i<=TOP; prime[i++]=1);
  prime[0] = prime[1] = 0;
  for (i=2; i*i<=TOP; i++)
    if (prime[i])
      for (j=i*i; j<=TOP; j+=i)
	prime[j] = 0;
  
  for (i=0; i<10; start[i++]=-1);
  for (i=BOT; i<=TOP; i++)
    if (prime[i])
      {
	for (k=0, j=i; j>0; j/=10)
	  k += j % 10;
	if (k == sum)
	  {
	    if (start[i/BOT] == -1)
	      start[i/BOT] = psize;
	    for (k=i, j=4; j>=0; k/=10, j--)
	      pool[psize][j] = k % 10;
	    psize++;
	  }
      }
}

void row1()
{
  int i, j;
  for (i=start[firstnum]; i<psize && pool[i][0] == firstnum; i++)
    if (pool[i][1] > 0 && pool[i][2] > 0 && pool[i][3] > 0)
      {
	for (j=0; j<5; sq[j] = pool[i][j], j++);
	col1();
      }
}

void col1()
{
  int i, j;
  for (i=start[firstnum]; i<psize && pool[i][0] == firstnum; i++)
    if (pool[i][1] > 0 && pool[i][2] > 0 && pool[i][3] > 0)
      {
	for (j=1; j<5; sq[5*j] = pool[i][j], j++);
	dia1();
      }
}

void dia1()
{
  int i, j;
  for (i=start[sq[20]]; i<psize && pool[i][0] == sq[20]; i++)
    if (pool[i][4] == sq[4])
      {
	for (j=1; j<4; sq[20-4*j] = pool[i][j], j++);
	row2();
      }
}

void row2()
{
  int i, j;
  for (i=start[sq[5]]; i<psize && pool[i][0] == sq[5]; i++)
    if (pool[i][3] == sq[8])
      {
	for (j=1; j<5; sq[5+j] = pool[i][j], j++);
	col2();
      }
}

void col2()
{
  int i;
  for (i=start[sq[1]]; i<psize && pool[i][0] == sq[1]; i++)
    if (pool[i][1] == sq[6] && pool[i][3] == sq[16])
      {
	sq[11] = pool[i][2], sq[21] = pool[i][4];
	row3();
      }
}

void row3()
{
  int i;
  for (i=start[sq[10]]; i<psize && pool[i][0] == sq[10]; i++)
    if (pool[i][1] == sq[11] && pool[i][2] == sq[12])
      {
	sq[13] = pool[i][3], sq[14] = pool[i][4];
	col3();
      }
}

void col3()
{
  int i;
  for (i=start[sq[2]]; i<psize && pool[i][0] == sq[2]; i++)
    if (pool[i][1] == sq[7] && pool[i][2] == sq[12])
      {
	sq[17] = pool[i][3], sq[22] = pool[i][4];
	row4();
      }
}

void row4()
{
  int i;
  for (i=start[sq[15]]; i<psize && pool[i][0] == sq[15]; i++)
    if (pool[i][1] == sq[16] && pool[i][2] == sq[17])
      {
	sq[18] = pool[i][3], sq[19] = pool[i][4];
	col4();
      }
}

void col4()
{
  int i;
  for (i=start[sq[3]]; i<psize && pool[i][0] == sq[3]; i++)
    if (pool[i][1] == sq[8] && pool[i][2] == sq[13] && pool[i][3] == sq[18])
      {
	sq[23] = pool[i][4];
	final();
      }
}

void final()
{
  int i;
  for (sq[24]=sum, i=4; i<24; sq[24]-=sq[i], i+=5);
  if (sq[24] <= 0 || sq[24] > 9)
    return;
  if (checkrcd(20, 25, 1) && checkrcd(4, 25, 5) && checkrcd(0, 25, 6))
    {
      for (i=0; i<25; i++)
	solutions[nsol][i] = sq[i];
      nsol++;
    }
}

int checkrcd(int i, int stop, int step)
{
  int digsum = 0, num = 0;
  for (; i<stop; i+=step)
    {
      digsum += sq[i];
      num = 10*num + sq[i];
    }
  return prime[num] && digsum == sum;
}

int cmp(const void *a, const void *b)
{
  int *sa = (int*)a, *sb = (int*)b, i;
  for (i=0; i<25; i++)
    if (sa[i] != sb[i])
      return (sa[i] < sb[i] ? -1:1);
  return 0;
}

int main()
{
  FILE *fin = fopen("prime3.in", "r"), *fout = fopen("prime3.out", "w");
  int i, j;
  fscanf(fin, "%d %d", &sum, &firstnum);
  gen_primes();
  row1();
  if (!nsol)
    fprintf(fout, "NONE\n");
  else
    {
      qsort(solutions, nsol, sizeof(int)*25, cmp);
      for (i=0; i<nsol; i++)
	{
	  for (j=0; j<25; j++)
	    {
	      fprintf(fout, "%d", solutions[i][j]);
	      if (j%5 == 4)
		fprintf(fout, "\n");
	    }
	  if (i != nsol-1)
	    fprintf(fout, "\n");
	}
    }
  fclose(fin), fclose(fout);
}
