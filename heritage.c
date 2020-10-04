/*
  ID: abacles1
  LANG: C
  TASK: heritage
*/

#include <stdio.h>
#include <stdlib.h>

struct tnode
{
  char id;
  struct tnode *left,*right;
};

struct tnode *newnode()
{
  struct tnode *new = malloc(sizeof(struct tnode));
  new->left = NULL;
  new->right = NULL;
  return new;
}

void build_tree(char io[],char po[],struct tnode *t)
{
  char root = po[0],lookup[26] = {0};
  int i,j;
  t->id = root;
  for(i=0;io[i];i++)
    {
      if(io[i] == root)
	break;
    }
  io[i] = '.';
  for(j=i-1;j>=0 && io[j]!='.';j--)
    lookup[io[j]-'A'] = 1;
  for(j=0;po[j];j++)
    {
      if(lookup[po[j]-'A'])
	{
	  t->left = newnode();
	  build_tree(io,po+j,t->left);
	  break;
	}
    }
  for(j=0;j<26;j++) lookup[j] = 0;
  for(j=i+1;io[j] && io[j]!='.';j++)
    lookup[io[j]-'A'] = 1;
  for(j=0;po[j];j++)
    {
      if(lookup[po[j]-'A'])
	{
	  t->right = newnode();
	  build_tree(io,po+j,t->right);
	  break;
	}
    }
}

void postord(struct tnode *t,FILE *o)
{
  if(t->left)
    postord(t->left,o);
  if(t->right)
    postord(t->right,o);
  fprintf(o,"%c",t->id);
  free(t);
}

int main()
{
  FILE *in = fopen("heritage.in","r"),*out = fopen("heritage.out","w");
  char inord[27],preord[27];
  struct tnode *tree = newnode();
  fscanf(in,"%s%s",inord,preord);
  fclose(in);
  build_tree(inord,preord,tree);
  postord(tree,out);
  fprintf(out,"\n");
  fclose(out);
}
