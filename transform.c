/*
ID: abacles1
LANG: C
TASK: transform
*/

#include <stdio.h>
#include <stdlib.h>

char **createpat(int n)
{
  int i;
  char **new=malloc(sizeof(char *)*n);
  for(i=0;i<n;i++)
    new [i]=malloc(sizeof(char)*n);
  return new;
}

void freepat(int n,char **pat)
{
  int i;
  for(i=0;i<n;i++)
    free(pat [i]);
  free(pat);
}

void printpat(int n,char **pat)
{
  int i,j;
  for(i=0;i<n;i++)
    {
      for(j=0;j<n;j++)
	{
	  printf("%c",pat [i][j]);
	}
      printf("\n");
    }
}

int patcmp(int n,char **pati,char **patii)
{
  int i,j;
  for(i=0;i<n;i++)
    {
      for(j=0;j<n;j++)
	{
	  if(pati [i][j]!=patii [i][j])
	    return 0;
	}
    }
  return 1;
}

void rotate_cw(int n,char **pat,char **new)
{
  int i,j;
  for(i=0;i<n;i++)
    {
      for(j=0;j<n;j++)
	{
	  new [j][n-i-1]=pat [i][j];
	}
    }
}

void reflect(int n,char **pat,char **new)
{
  int i,j;
  for(i=0;i<n;i++)
    {
      for(j=0;j<n;j++)
	{
	  new [i][n-j-1]=pat [i][j];
	}
    }
}

int main()
{
  FILE *in=fopen("transform.in","r"),*out=fopen("transform.out","w");
  int dim;
  char **pimage,**image,**cmp;
  int i,j;
  fscanf(in,"%d",&dim);
  pimage=malloc(sizeof(char *)*dim);
  image=malloc(sizeof(char *)*dim);
  for(i=0;i<dim;i++)
    {
      pimage [i]=malloc(sizeof(char)*(dim+2));
      fscanf(in,"%s",pimage [i]);
    }
  for(i=0;i<dim;i++)
    {
      image [i]=malloc(sizeof(char)*(dim+2));
      fscanf(in,"%s",image [i]);
    }
  cmp=createpat(dim);
  rotate_cw(dim,pimage,cmp);
  /*90-degree rotation*/
  if(patcmp(dim,cmp,image))
    {
      fprintf(out,"1\n");
      goto END;
    }
  rotate_cw(dim,cmp,pimage);
  /*180-degree rotation*/
  if(patcmp(dim,pimage,image))
    {
      fprintf(out,"2\n");
      goto END;
    }
  rotate_cw(dim,pimage,cmp);
  /*270-degree rotation*/
  if(patcmp(dim,cmp,image))
    {
      fprintf(out,"3\n");
      goto END;
    }
  rotate_cw(dim,cmp,pimage);
  reflect(dim,pimage,cmp);
  /*Reflection*/
  if(patcmp(dim,cmp,image))
    {
      fprintf(out,"4\n");
      goto END;
    }
  rotate_cw(dim,cmp,pimage);
  /*Reflection and 90-degree rotation*/
  if(patcmp(dim,pimage,image))
    {
      fprintf(out,"5\n");
      goto END;
    }
  rotate_cw(dim,pimage,cmp);
  /*Reflection and 180-degree rotation*/
  if(patcmp(dim,cmp,image))
    {
      fprintf(out,"5\n");
      goto END;
    }
  rotate_cw(dim,cmp,pimage);
  /*Reflection and 270-degree rotation*/
  if(patcmp(dim,pimage,image))
    {
      fprintf(out,"5\n");
      goto END;
    }
  rotate_cw(dim,pimage,cmp);
  reflect(dim,cmp,pimage);
  /*No change*/
  if(patcmp(dim,pimage,image))
    {
      fprintf(out,"6\n");
      goto END;
    }
  fprintf(out,"7\n");
 END:
  freepat(dim,pimage);
  freepat(dim,image);
  freepat(dim,cmp);
  fclose(in);
  fclose(out);
  return 0;
}
