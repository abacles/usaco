/*
  ID: abacles1
  LANG: C
  TASK: cryptcow
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CARD 1000000

char yes[] = "Begin the Escape execution at the Break of Dawn";
char fss_visited[2900] = {0};
char *fss_lookup[2900];

long long bigprime = 1000000007, x = 263;

struct hnode
{
  char str[76];
  struct hnode *next;
} **table;

int map(char ch)
{
  if ('A' <= ch && ch <= 'Z')
    return ch - 'A' + 1;
  else if ('a' <= ch && ch <= 'z')
    return ch - 'a' + 27;
  return 0;
}

char *fastss(char *haystack, char *needle)
{
  int x = map(needle[0])*53+map(needle[1]);
  char prefix[3] = "";
  if (!fss_visited[x])
    {
      strncat(prefix, needle, 2);
      fss_visited[x] = 1;
      fss_lookup[x] = strstr(haystack, prefix);
    }
  if (fss_lookup[x] == NULL)
    return NULL;
  return strstr(fss_lookup[x], needle);
}

int hash(char s[], int m)
{
  long long h = 0;
  int i;
  for(i=strlen(s)-1;i>=0;i--)
    h = ((h*x) % bigprime + s[i]) % bigprime;
  return (int)(h % m);
}

int update(char s[], int m)
{
  int h = hash(s, m);
  struct hnode *n;
  for(n=table[h];n;n=n->next)
    {
      if(!strcmp(s, n->str))
	return 0;
    }
  n = malloc(sizeof(struct hnode));
  strcpy(n->str, s);
  n->next = table[h];
  table[h] = n;
  return 1;
}

void makeset(int m)
{
  int i;
  table = malloc(sizeof(struct hnode*) * m);
  for(i=0;i<m;i++)
    table[i] = NULL;
}

void destroyset(int m)
{
  struct hnode *n, *this;
  int i;
  for(i=0;i<m;i++)
    {
      n = table[i];
      while(n)
	{
	  this = n;
	  n = n->next;
	  free(this);
	}
    }
  free(table);
}

int escape(char s[], int len)
{
  int cpos[75], opos[75], wpos[75], cc = 0, oc = 0, wc = 0, i, j, k;
  char dcode[73], sub[76];
  // printf("Checking [%s]...\n", s);
  for (i=j=0; s[i]; i++)
    {
      if (s[i] == 'C')
	cpos[cc++] = i;
      else if (s[i] == 'O')
	opos[oc++] = i;
      else if (s[i] == 'W')
	wpos[wc++] = i;
      else
	{
	  sub[j++] = s[i];
	  continue;
	}
      if (j > 0)
	{
	  sub[j] = '\0';
	  if (j > 1 && fastss(yes, sub) == NULL)
	    return 0;
	  j = 0;
	}
    }
  if (cc != oc || oc != wc)
    return 0;
  if (cc == 0)
    return strcmp(s, yes) == 0;
  if (opos[0] < cpos[0] || wpos[0] < cpos[0] || cpos[cc-1] > wpos[wc-1] || opos[oc-1] > wpos[wc-1])
    return 0;
  if (strncmp(&s[wpos[wc-1]+1], &yes[47-(len-(wpos[wc-1]+1))], len-(wpos[wc-1]+1)) != 0)
    return 0;
  if (!update(s, CARD))
    return 0;
  for (j=0; j<oc; j++)
    {
      for (i=0; i<cc && cpos[i]<opos[j]; i++)
	{
	  for (k=wc-1; k>=0 && wpos[k]>opos[j]; k--)
	    {
	      strncpy(dcode, s, cpos[i]);
	      strncpy(&dcode[cpos[i]], &s[opos[j]+1], wpos[k]-(opos[j]+1));
	      strncpy(&dcode[cpos[i]+wpos[k]-(opos[j]+1)], &s[cpos[i]+1], opos[j]-(cpos[i]+1));
	      strncpy(&dcode[wpos[k]-2], &s[wpos[k]+1], len-(wpos[k]+1));
	      dcode[len-3] = '\0';
	      if (escape(dcode, len-3))
		return 1;
	    }
	}
    }
  return 0;
}

int main()
{
  FILE *fin = fopen("cryptcow.in", "r"), *fout = fopen("cryptcow.out", "w");
  char msg[76];
  int i;
  for (i=0; (msg[i] = fgetc(fin)) != '\n'; i++);
  msg[i] = '\0';
  makeset(CARD);
  if (escape(msg, i))
    fprintf(fout, "%d %d\n", 1, (i-47) / 3);
  else
    fprintf(fout, "0 0\n");
  destroyset(CARD);
  fclose(fin), fclose(fout);
}
