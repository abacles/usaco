/*
ID: abacles1
LANG: C
TASK: contact
*/

#include <stdio.h>
#include <stdlib.h>

struct fsa
{
  struct fsa *next[2],*parent;
  int op;
};

struct occ
{
  int occc;
  struct fsa *bp;
} patt[10000];
int olen = 0;

struct fsa *newfsa()
{
  struct fsa *new = malloc(sizeof(struct fsa));
  new->op = olen;
  patt[olen].occc = 0;
  patt[olen].bp = new;
  olen++;
  new->parent = new->next[0] = new->next[1] = NULL;
  return new;
}

struct fsa *updatefsa(struct fsa *s,char n,int add)
{
  if(!s->next[n-'0'])
    {
      s->next[n-'0'] = newfsa();
      s->next[n-'0']->parent = s;
    }
  patt[s->next[n-'0']->op].occc += add;
  return s->next[n-'0'];
}

void freefsa(struct fsa *root)
{
  if(root->next[0])
    freefsa(root->next[0]);
  if(root->next[1])
    freefsa(root->next[1]);
  free(root);
}

int compare(const void *a,const void *b)
{ // might be a problem with casting
  return *(int*)b - *(int*)a;
}

int strcomp(const void *a,const void *b)
{
  char *sa = *(char**)a;
  char *sb = *(char**)b;
  int i,adv = 0;
  for(i=0;!(!sa[i] && !sb[i]);i++)
    {
      if(!sa[i])
	return -1;
      if(!sb[i])
	return 1;
      if(!adv && sa[i]<sb[i])
	adv = -1;
      else if(!adv && sb[i]<sa[i])
	adv = 1;
    }
  return adv;
}

int printpath(struct fsa *node,char *out)
{
  int len = 0;
  if(node->parent)
    {
      len += printpath(node->parent,out);
      out[len] = '0' + (node->parent->next[1] == node);
      len++;
    }
  return len;
}

void printhighest(int n,FILE *out)
{
  int i,j = 0,k,l;
  char **buff;
  qsort(patt,10000,sizeof(struct occ),compare);
  for(i=0;i<n && j<olen-1;i++)
    {
      if(!patt[j].occc)
	break;
      fprintf(out,"%d\n",patt[j].occc);
      for(k=j,j++;j<olen-1 && patt[j].occc != 0 && patt[j].occc == patt[j-1].occc;j++) {}
      buff = malloc(sizeof(char*)*(j-k));
      for(l=0;l<j-k;l++)
	{
	  buff[l] = malloc(sizeof(char)*13);
	  buff[l][printpath(patt[k+l].bp,buff[l])] = 0;
	}
      qsort(buff,j-k,sizeof(char*),strcomp);
      for(l=0;l<j-k;l++)
	{
	  fprintf(out,"%s",buff[l]);
	  if((l%6 == 5) || l == j-k-1)
	    fprintf(out,"\n");
	  else
	    fprintf(out," ");
	  free(buff[l]);
	}
      free(buff);
    }
}

int main()
{
  FILE *in = fopen("contact.in","r"),*out = fopen("contact.out","w");
  int minlen,maxlen,count;
  char seq[200001];
  struct fsa *start = newfsa(),*curr;
  int i,j;
  fscanf(in,"%d %d %d",&minlen,&maxlen,&count);
  for(i=0;fscanf(in,"%s",seq+i)!=EOF;i+=80) {}
  fclose(in);
  for(i=0;seq[i+minlen-1];i++)
    {
      curr = start;
      for(j=0;j<maxlen && seq[i+j];j++)
	curr = updatefsa(curr,seq[i+j],minlen<=j+1 && j+1<=maxlen);
    }
  // printf("done\n");
  printhighest(count,out);
  fclose(out);
  freefsa(start);
}
