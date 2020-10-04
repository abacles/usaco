/*
 ID: abacles1
 LANG: C
 TASK: rect1
 */

#include <stdio.h>

#define MAX(A, B) (A>B ? A:B)
#define MIN(A, B) (A<B ? A:B)

struct rect
{
  int n, s, e, w, c;
};

int rect_overlap(struct rect a, struct rect b)
{
  return !(a.n <= b.s || b.n <= a.s) && !(a.e <= b.w || b.e <= a.w);
}

int rect_set(struct rect *r, int n, int s, int e, int w, int c)
{
  r->n = n, r->s = s, r->e = e, r->w = w, r->c = c;
  return (r->n - r->s) * (r->e - r->w);
}

int paint(struct rect all[], int k, struct rect new)
{
  int i;
  for (i=0; i<k; i++)
  {
    if (rect_overlap(all[i], new))
    {
      if (new.n < all[i].n)
        rect_set(&all[k++], all[i].n, new.n, MIN(all[i].e, new.e), MAX(all[i].w, new.w), all[i].c);
      if (new.s > all[i].s)
        rect_set(&all[k++], new.s, all[i].s, MIN(all[i].e, new.e), MAX(all[i].w, new.w), all[i].c);
      if (new.e < all[i].e)
        rect_set(&all[k++], all[i].n, all[i].s, all[i].e, new.e, all[i].c);
      if (new.w > all[i].w)
        rect_set(&all[k++], all[i].n, all[i].s, new.w, all[i].w, all[i].c);
      all[i--] = all[--k];
    }
  }
  all[k++] = new;
  return k;
}

int main()
{
  FILE *fin = fopen("rect1.in", "r"), *fout = fopen("rect1.out", "w");
  int width, height, nrects, north, south, east, west, color, ccount[2501] = {0}, k = 1, i;
  struct rect canvas[5000], this;
  fscanf(fin, "%d %d %d", &width, &height, &nrects);
  rect_set(&canvas[0], height, 0, width, 0, 1);
  for (i=0; i<nrects; i++)
  {
    fscanf(fin, "%d %d %d %d %d", &west, &south, &east, &north, &color);
    this.n = north, this.s = south, this.e = east, this.w = west, this.c = color;
    k = paint(canvas, k, this);
  }
  for (i=0; i<k; i++)
    ccount[canvas[i].c] += (canvas[i].n - canvas[i].s) * (canvas[i].e - canvas[i].w);
  for (i=1; i<=2500; i++)
  {
    if (ccount[i])
      fprintf(fout, "%d %d\n", i, ccount[i]);
  }
  fclose(fin), fclose(fout);
}
