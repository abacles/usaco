/*
  ID: abacles1
  LANG: C
  TASK: window
*/

#include <stdio.h>

#define MIN(A, B) (A < B ? A : B)
#define MAX(A, B) (A > B ? A : B)

struct window
{
  int l, r, t, b, height, exist;
};

int map(char ch)
{
  if('0' <= ch && ch <= '9') return ch - '0';
  else if('a' <= ch && ch <= 'z') return ch - 'a' + 10;
  return ch - 'A' + 36;
}

int overlap(int l1, int r1, int l2, int r2)
{
  return !(r1 <= l2 || l1 >= r2);
}

void rect(struct window *w, int t, int r, int b, int l)
{
  w->t = t; w->r = r; w->b = b; w->l = l;
}

double visible(struct window all[62], int this)
{
  struct window pieces[250];
  int npieces = 0, visible_area = 0, i, j;
  pieces[npieces++] = all[this];
  for(i=0;i<62;i++)
    {
      if(all[i].exist && all[i].height > all[this].height)
	{
	  for(j=0;j<npieces;j++)
	    {
	      if(overlap(pieces[j].l, pieces[j].r, all[i].l, all[i].r) &&
		 overlap(pieces[j].b, pieces[j].t, all[i].b, all[i].t))
		{
		  if(all[i].t < pieces[j].t)
		    rect(&pieces[npieces++], pieces[j].t, pieces[j].r,
			 all[i].t, pieces[j].l);
		  if(all[i].l > pieces[j].l)
		    rect(&pieces[npieces++], MIN(all[i].t, pieces[j].t),
			 all[i].l, MAX(all[i].b, pieces[j].b), pieces[j].l);
		  if(all[i].r < pieces[j].r)
		    rect(&pieces[npieces++], MIN(all[i].t, pieces[j].t),
			 pieces[j].r, MAX(all[i].b, pieces[j].b), all[i].r);
		  if(all[i].b > pieces[j].b)
		    rect(&pieces[npieces++], all[i].b, pieces[j].r,
			 pieces[j].b, pieces[j].l);
		  pieces[j--] = pieces[--npieces];
		}
	    }
	}
    }
  for(i=0;i<npieces;i++)
    visible_area += (pieces[i].t-pieces[i].b) * (pieces[i].r-pieces[i].l);
  return (double)visible_area / (all[this].t-all[this].b) / (all[this].r-all[this].l) * 100;
}

int main()
{
  FILE *in = fopen("window.in", "r"), *out = fopen("window.out", "w");
  char cmd, id;
  int x1, y1, x2, y2, top = 0, bot = 0, x, i;
  struct window interface[62];
  for(i=0;i<62;interface[i++].exist=0);
  while(fscanf(in, "%c(%c", &cmd, &id) != EOF)
    {
      x = map(id);
      if(fgetc(in) == ',')
	{
	  fscanf(in, "%d,%d,%d,%d)", &x1, &y1, &x2, &y2);
	  rect(&interface[x], MAX(y1, y2), MAX(x1, x2),
	       MIN(y1, y2), MIN(x1, x2));
	  interface[x].exist = 1;
	}
      if(cmd == 'w' || cmd == 't')
	interface[x].height = ++top;
      else if(cmd == 'b')
	interface[x].height = --bot;
      else if(cmd == 'd')
	interface[x].exist = 0;
      else if(cmd == 's')
	fprintf(out, "%.3f\n", visible(interface, x));
      fgetc(in);
    }
  fclose(in), fclose(out);
}
