/*
ID: abacles1
LANG: C
TASK: prefix
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stknode
{
  int val;
  struct stknode *prev;
};

struct stack
{
  struct stknode *tail;
  int len;
};

struct fsa
{
  int id;
  int leaf;
  struct fsa *children[26];
};

struct stack *newstk(int initval)
{
  struct stack *new = malloc(sizeof(struct stack));
  struct stknode *head = malloc(sizeof(struct stknode));
  head->val = initval;
  head->prev = NULL;
  new->tail = head;
  new->len = 1;
  return new;
}

void push(struct stack *stk,int newval)
{
  struct stknode *newtail = malloc(sizeof(struct stknode));
  newtail->val = newval;
  newtail->prev = stk->tail;
  stk->tail = newtail;
  (stk->len)++;
}

int pop(struct stack *stk)
{
  struct stknode *oldtail;
  int tailval;
  if(stk->len == 0)
    {
      free(stk);
      return -1;
    }
  oldtail = stk->tail;
  tailval = oldtail->val;
  stk->tail = oldtail->prev;
  free(oldtail);
  (stk->len)--;
  return tailval;
}

void clearstk(struct stack *stk)
{
  while(pop(stk) > 0) {}
}

struct fsa *newfsanode(int nid)
{
  struct fsa *newnode = malloc(sizeof(struct fsa));
  int i;
  newnode->id = nid;
  newnode->leaf = 0;
  for(i=0;i<26;i++)
    (newnode->children)[i] = NULL;
  return newnode;
}

struct fsa *buildfsa(char strpatt[200][11],int pattcount)
{
  struct fsa *fsaroot = newfsanode(0);
  struct fsa *fsacurr;
  int nextid = 1,i,j;
  for(i=0;i<pattcount;i++)
    {
      fsacurr = fsaroot;
      for(j=0;strpatt[i][j];j++)
	{
	  if(!((fsacurr->children)[strpatt[i][j]-'A']))
	    {
	      (fsacurr->children)[strpatt[i][j]-'A'] = newfsanode(nextid);
	      nextid++;
	    }
	  fsacurr = (fsacurr->children)[strpatt[i][j]-'A'];
	}
      fsacurr->leaf = 1;
    }
  return fsaroot;
}

void freefsa(struct fsa *root)
{
  int i;
  for(i=0;i<26;i++)
    {
      if((root->children)[i])
	freefsa((root->children)[i]);
    }
  free(root);
}

int matchfsa(struct fsa *patt,char *str,int len)
{
  int i;
  for(i=0;i<len;i++)
    {
      if(!(patt->children)[str[i]-'A'])
	return 0;
      patt = (patt->children)[str[i]-'A'];
    }
  return patt->leaf;
}

int main()
{
  FILE *in,*out;
  char patt[200][11],buff[11],seq[200001],ch,reached[200001];
  int plen[10] = {0},pcount,slen,bestreach = 0,start,l;
  struct stack *proc = newstk(0);
  struct fsa *pattroot,*pattsearch;
  
  in = fopen("prefix.in","r");
  buff[0] = 0;
  for(pcount=0;buff[0] != '.';pcount++)
    {
      fscanf(in,"%s",buff);
      strcpy(patt[pcount],buff);
      plen[strlen(buff)-1] = 1;
    }
  pcount--;
  for(slen=0;(ch=fgetc(in))!=EOF;)
    {
      if(ch != '\n')
	{
	  seq[slen] = ch;
	  reached[slen] = 0;
	  slen++;
	}
    }
  reached[slen] = seq[slen] = 0;
  fclose(in);

  pattroot = buildfsa(patt,pcount);

  reached[0] = 1;
  while(bestreach < slen && (start=pop(proc)) >= 0)
    {
      pattsearch = pattroot;
      for(l=10;l>0;l--)
	{
	  if(!plen[l-1])
	    continue;
	  if(start+l<=slen && matchfsa(pattsearch,seq+start,l) && !reached[start+l])
	    {
	      if(start+l == slen)
		{
		  clearstk(proc);
		  bestreach = slen;
		  break;
		}
	      reached[start+l] = 1;
	      bestreach = start+l > bestreach ? start+l : bestreach;
	      push(proc,start+l);
	    }
	}
    }

  freefsa(pattroot);

  out = fopen("prefix.out","w");
  fprintf(out,"%d\n",bestreach);
  fclose(out);

  // printf("%d\n",bestreach);
  
  return 0;
}
