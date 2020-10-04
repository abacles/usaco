/*
ID: abacles1
LANG: C
TASK: maze1
*/

#include <stdio.h>
#include <stdlib.h>

#define MIN(A,B) (A<B ? A:B)
#define MAX(A,B) (A>B ? A:B)

char **maze;
int exits[2][2],efound = 0;

struct qnode
{
  int y,x;
  struct qnode *next;
};

struct qnode *push(struct qnode *tail,int ny,int nx,int *len)
{
  struct qnode *new = malloc(sizeof(struct qnode));
  new->y = ny;
  new->x = nx;
  new->next = NULL;
  if(tail)
    tail->next = new;
  (*len)++;
  return new;
}
struct qnode *pop(struct qnode *head,int *y,int *x,int *len)
{
  struct qnode *old = head;
  *y = old->y;
  *x = old->x;
  head = old->next;
  free(old);
  (*len)--;
  return head;
}

int worstcell(int h,int w)
{
  int e,i,j,cer,cec,dir[2] = {-1,1};
  int **dist[2],r,c,qlen,max = 0;
  struct qnode *qh,*qt;
  for(e=0;e<2;e++)
    {
      cer = exits[e][0];
      cec = exits[e][1];
      dist[e] = malloc(sizeof(int*)*h);
      for(i=0;i<h;i++)
	{
	  dist[e][i] = malloc(sizeof(int)*w);
	  for(j=0;j<w;j++)
	    dist[e][i][j] = 10000;
	}
      dist[e][(cer-1)/2][(cec-1)/2] = 0;
      qh = qt = malloc(sizeof(struct qnode));
      qh->y = cer;
      qh->x = cec;
      qh->next = NULL;
      qlen = 1;
      while(qlen > 0)
	{
	  qh = pop(qh,&r,&c,&qlen);
	  if(qlen == 0)
	    qh = qt = NULL;
	  for(i=0;i<2;i++)
	    {
	      if(((i==0 && r>1 && maze[r-1][c]==' ') || (i==1 && r<2*h-1 && maze[r+1][c]==' ')) && dist[e][(r-1+2*dir[i])/2][(c-1)/2] > 1+dist[e][(r-1)/2][(c-1)/2])
		{
		  dist[e][(r-1+2*dir[i])/2][(c-1)/2] = 1+dist[e][(r-1)/2][(c-1)/2];
		  qt = push(qt,r+2*dir[i],c,&qlen);
		  if(qh == NULL)
		    qh = qt;
		}
	    }
	  for(i=0;i<2;i++)
	    {
	      if(((i==0 && c>1 && maze[r][c-1]==' ') || (i==1 && c<2*w-1 && maze[r][c+1]==' ')) && dist[e][(r-1)/2][(c-1+2*dir[i])/2] > 1+dist[e][(r-1)/2][(c-1)/2])
		{
		  dist[e][(r-1)/2][(c-1+2*dir[i])/2] = 1+dist[e][(r-1)/2][(c-1)/2];
		  qt = push(qt,r,c+2*dir[i],&qlen);
		  if(qh == NULL)
		    qh = qt;
		}
	    }
	}
    }
  for(i=0;i<h;i++)
    {
      for(j=0;j<w;j++)
	max = MAX(max,MIN(dist[0][i][j],dist[1][i][j]));
    }
  for(e=0;e<2;e++)
    {
      for(i=0;i<h;i++)
	free(dist[e][i]);
      free(dist[e]);
    }
  return max + 1;
}

int main()
{
  FILE *in,*out;
  char ch;
  int height,width;
  int i,j;
  in = fopen("maze1.in","r");
  fscanf(in,"%d %d",&width,&height);
  fgetc(in);
  maze = malloc(sizeof(char*)*(2*height+1));
  for(i=0;i<2*height+1;i++)
    {
      maze[i] = malloc(sizeof(char)*(2*width+1+1));
      for(j=0;(ch=fgetc(in)) != '\n';j++)
	{
	  maze[i][j] = ch;
	  if(ch==' ' && (i==0 || i==2*height || j==0 || j==2*width))
	    {
	      exits[efound][0] = (i==0?1:i)==2*height?2*height-1:(i==0?1:i);
	      exits[efound][1] = (j==0?1:j)==2*width?2*width-1:(j==0?1:j);
	      efound++;
	    }
	}
      maze[i][j] = 0;
    }
  fclose(in);

  out = fopen("maze1.out","w");
  fprintf(out,"%d\n",worstcell(height,width));
  fclose(out);

  for(i=0;i<2*height+1;i++)
    free(maze[i]);
  free(maze);
  return 0;
}
