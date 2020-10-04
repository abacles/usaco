/*
  ID: abacles1
  LANG: C
  TASK: camelot
*/

#include <stdio.h>
#include <stdlib.h>

#define INF 100000000

struct lnode
{
  int a;
  struct lnode *next;
};

struct qnode
{
  int elem;
  struct qnode *next;
};

int rcount,ccount;
struct lnode *adjlist[780];
int dist[780][780];
int pickup[780];
int kingpos;
int knightpos[779],knightcount = 0;

struct lnode *lladd(int connect)
{
  struct lnode *new = malloc(sizeof(struct lnode));
  new->a = connect;
  new->next = NULL;
  return new;
}
void llappend(int pos,int connect)
{
  struct lnode *e;
  for(e=adjlist[pos];e->next;e=e->next) {}
  e->next = lladd(connect);
}
void llfree(struct lnode *alist)
{
  struct lnode *next;
  while(alist)
    {
      next = alist->next;
      free(alist);
      alist = next;
    }
}

struct qnode *qpush(struct qnode *tail,int n)
{
  struct qnode *new = malloc(sizeof(struct qnode));
  new->elem = n;
  new->next = NULL;
  if(tail)
    tail->next = new;
  return new;
}
struct qnode *qpop(struct qnode *head,int *val)
{
  struct qnode *newhead = head->next;
  *val = head->elem;
  free(head);
  return newhead;
}

int code(char col,int row)
{
  return (col - 'A') * 30 + row;
}
int numcode(int row,int col)
{
  return col * 30 + row;
}

int inboard(int r,int c)
{
  return 0 <= r && r < rcount && 0 <= c && c < ccount;
}

int abs(int n)
{
  return n < 0 ? -n : n;
}

int king_move(int dr,int dc)
{
  int kr = abs(kingpos % 30 - dr),kc = abs(kingpos / 30 - dc);
  if(kr > kc)
    return kr;
  return kc;
}

int knights_move(int dest)
{
  int i,c = 0;
  for(i=0;i<knightcount;i++)
    c += dist[knightpos[i]][dest];
  return c;
}

void bfs(int pos)
{
  struct qnode *head,*tail;
  struct lnode *e;
  int node,i,j,t=0;
  int wking[780];
  for(i=0;i<780;i++)
    {
      dist[pos][i] = INF;
      wking[i] = INF;
    }
  head = tail = qpush(NULL,pos);
  dist[pos][pos] = 0;
  wking[pos] = king_move(pos%30,pos/30);
  while(head)
    {
      head = qpop(head,&node);
      if(!head)
	tail = NULL;
      if(king_move(node%30,node/30) + dist[pos][node] < wking[node])
	wking[node] = king_move(node%30,node/30) + dist[pos][node];
      for(e=adjlist[node]->next;e;e=e->next)
	{
	  if(wking[node] + 1 < wking[e->a])
	    wking[e->a] = wking[node] + 1;
	  if(dist[pos][node] + 1 < dist[pos][e->a])
	    {
	      dist[pos][e->a] = dist[pos][node] + 1;
	      tail = qpush(tail,e->a);
	      if(!head)
		head = tail;
	      t++;
	    }
	}
    }
  for(i=0;i<780;i++)
    {
      if(wking[i] - dist[pos][i] < pickup[i])
	pickup[i] = wking[i] - dist[pos][i];
    }
}

int main()
{
  FILE *in = fopen("camelot.in","r"),*out = fopen("camelot.out","w");
  int row;
  char col;
  int i,j,c,mincost = INF;
  fscanf(in,"%d %d\n",&rcount,&ccount);
  fscanf(in,"%c %d\n",&col,&row);
  kingpos = code(col,row-1);
  for(;fscanf(in,"%c %d",&col,&row) != EOF;fgetc(in))
    knightpos[knightcount++] = code(col,row-1);
  fclose(in);
  for(i=0;i<780;i++)
    {
      pickup[i] = INF;
      adjlist[i] = lladd(-1);
    }

  for(i=0;i<rcount;i++)
    {
      for(j=0;j<ccount;j++)
	{
	  if(inboard(i-2,j+1))
	    llappend(numcode(i,j),numcode(i-2,j+1));
	  if(inboard(i-1,j+2))
	    llappend(numcode(i,j),numcode(i-1,j+2));
	  if(inboard(i+1,j+2))
	    llappend(numcode(i,j),numcode(i+1,j+2));
	  if(inboard(i+2,j+1))
	    llappend(numcode(i,j),numcode(i+2,j+1));
	  if(inboard(i+2,j-1))
	    llappend(numcode(i,j),numcode(i+2,j-1));
	  if(inboard(i+1,j-2))
	    llappend(numcode(i,j),numcode(i+1,j-2));
	  if(inboard(i-1,j-2))
	    llappend(numcode(i,j),numcode(i-1,j-2));
	  if(inboard(i-2,j-1))
	    llappend(numcode(i,j),numcode(i-2,j-1));
	}
    }
  for(i=0;i<knightcount;i++)
    bfs(knightpos[i]);

  for(i=0;i<rcount;i++)
    {
      for(j=0;j<ccount;j++)
	{
	  c = knights_move(numcode(i,j)) + pickup[numcode(i,j)];
	  if(c < mincost)
	    mincost = c;
	  if(knightcount == 0)
	    {
	      mincost = king_move(i,j);
	      continue;
	    }
	}
    }

  fprintf(out,"%d\n",mincost);
  fclose(out);

  for(i=0;i<780;i++)
    llfree(adjlist[i]);
}
