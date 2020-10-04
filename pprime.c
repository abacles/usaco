/*
ID: abacles1
LANG: C
TASK: pprime
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int prime(long int n)
{
  int maxfactor = (int)sqrt(n);
  int i;
  for(i=2;i<=maxfactor;i++)
    {
      if(n%i == 0)
	return 0;
    }
  return 1;
}

int palindrome(long int n)
{
  long int rev=0,orig=n;
  while(n > 0)
    {
      rev = rev*10 + n%10;
      n /= 10;
    }
  return rev==orig;
}

void bump(char *n,int bil,int bir)
{
  int i,len;
  if(n[bil] != '9')
    {
      n[bil]++;
      if(bil != bir)
	n[bir]++;
    }
  else
    {
      if(bil == 0) /* all 9s */
	{
	  len = strlen(n);
	  n[0] = '1';
	  for(i=0;i<len-1;i++)
	    n[i+1] = '0';
	  n[len] = '1';
	  n[len+1] = '\0';
	}
      else
	{
	  n[bil]='0';
	  n[bir]='0';
	  bump(n,bil-1,bir+1);
	}
    }
}

long int nextpalin(long int c)
{
  char *repr = malloc(sizeof(char)*10);
  long int new;
  int digits;
  sprintf(repr,"%ld",c);
  digits = strlen(repr);
  if(digits%2 == 0)
    bump(repr,digits/2-1,digits/2);
  else
    bump(repr,digits/2,digits/2);
  new = atoi(repr);
  free(repr);
  return new;
}

int main()
{
  FILE *in,*out;
  long int min,max;
  long int i;

  in = fopen("pprime.in","r");
  fscanf(in,"%ld %ld",&min,&max);
  fclose(in);

  out = fopen("pprime.out","w");
  for(i=min;i<=max;)
    {
      if(palindrome(i))
	{
	  if(prime(i))
	    fprintf(out,"%ld\n",i);
	  i = nextpalin(i);
	}
      else
        i++;
    }

  fclose(out);
  return 0;
}
