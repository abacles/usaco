/*
ID: abacles1
LANG: C
TASK: wormhole
*/

#include <stdio.h>
#include <stdlib.h>

struct point
{
  long long int x;
  long long int y;
};

struct wh
{
  struct point a;
  struct point b;
};

int n;
int loopcount=0;
long long int max;
struct point *whs;
struct wh *conns;

int haswormhole(long long int xpos,long long int ypos)
{
  int i;
  for(i=0;i<n;i++)
    {
      if(xpos==whs [i].x && ypos==whs [i].y)
	return i;
    }
  return -1;
}

int nearest(long long int xpos,long long int ypos)
{
  int i;
  int closest_x=-1,best=-1;
  for(i=0;i<n;i++)
    {
      if((ypos==whs [i].y) && (xpos<whs [i].x)  && (closest_x==-1 || whs [i].x<closest_x))
	{
	  closest_x=whs [i].x;
	  best=i;
	}
    }
  return best;
}

int infinite(int orig,long long int cxpos,long long int cypos,long long int maxx)
{
  int i;
  int cwh,loops=0;
  while(cxpos<=maxx)
    {
      cxpos++;
      if((cwh=haswormhole(cxpos,cypos))!=-1)
	{
	  if(cwh==orig)
	    return 1;
	  for(i=0;i<n/2;i++)
	    {
	      if(conns [i].a.x==cxpos && conns [i].a.y==cypos)
		{
		  if(orig==-1)
		    loops+=infinite(cwh,conns [i].b.x,conns [i].b.y,maxx);
		  else
		    loops+=infinite(orig,conns [i].b.x,conns [i].b.y,maxx);
		  return loops;
		}
	      else if(conns [i].b.x==cxpos && conns [i].b.y==cypos)
		{
		  if(orig==-1)
		    loops+=infinite(cwh,conns [i].a.x,conns [i].a.y,maxx);
		  else
		    loops+=infinite(orig,conns [i].a.x,conns [i].a.y,maxx);
		  return loops;
		}
	    }
	}
      else
	{
	  if((cwh=nearest(cxpos,cypos))!=-1)
	    cxpos=whs [cwh].x-1;
	  else
	    return loops;
	}
    }
  return loops;
}

void coor_copy(struct point *to,struct point *from)
{
  to->x=from->x;
  to->y=from->y;
}

void enum_matchings(int len,struct point *holes)
{
  int i;
  struct point temp;
  if(len<2)
    {
      for(i=0;i<n/2;i++)
	{
	  conns [i].a.x=holes [i*2].x;
	  conns [i].a.y=holes [i*2].y;
	  conns [i].b.x=holes [i*2+1].x;
	  conns [i].b.y=holes [i*2+1].y;
	  /*printf("%lld, %lld -> %lld, %lld\n",conns [i].a.x,conns [i].a.y,conns [i].b.x,conns [i].b.y);*/
	}
      /*printf("\n");*/
      for(i=0;i<n;i++)
	{
	  if(infinite(-1,whs [i].x-1,whs [i].y,max))
	    {
	      loopcount++;
	      break;
	    }
	}
      return;
    }
  for(i=0;i<len-1;i++)
    {
      coor_copy(&temp,&(holes [i]));
      coor_copy(&(holes [i]),&(holes [len-2]));
      coor_copy(&(holes [len-2]),&temp);
      enum_matchings(len-2,holes);
      coor_copy(&(holes [len-2]),&(holes [i]));
      coor_copy(&(holes [i]),&temp);
    }
}

int main()
{
  FILE *in=fopen("wormhole.in","r"),*out=fopen("wormhole.out","w");
  int whcount;
  struct point *wormholes;
  int loops=0;
  int i;
  fscanf(in,"%d",&whcount);
  wormholes=malloc(sizeof(struct point)*whcount);
  conns=malloc(sizeof(struct wh)*(whcount/2));
  for(i=0;i<whcount;i++)
    {
      fscanf(in,"%lld %lld",&(wormholes [i].x),&(wormholes [i].y));
      if(wormholes [i].x>max)
	max=wormholes [i].x;
    }
  n=whcount;
  whs=wormholes;
  enum_matchings(whcount,wormholes);
  loops=loopcount;
  fprintf(out,"%d\n",loops);
  /*printf("%d\n",loops);*/
  free(wormholes);
  free(conns);
  fclose(in);
  fclose(out);
  return 0;
}
