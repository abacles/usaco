/*
  ID: abacles1
  LANG: C
  TASK: picture
*/

#include <stdio.h>
#include <stdlib.h>

#define HEAP_PARENT(I) ((I-1)/2)
#define HEAP_LCHILD(I) (2*I+1)
#define HEAP_RCHILD(I) (2*I+2) 
#define MIN(A, B) (A<B ? A:B)
#define MAX(A, B) (A>B ? A:B) 

struct heap
{
  int key, val;
};

struct point
{
  int pos, id;
};

void heap_swap(struct heap h[], int i, int j)
{
  struct heap temp = h[i];
  h[i] = h[j]; h[j] = temp;
}

void heap_pop(struct heap h[], int *hsize)
{
  int i, j;
  h[0] = h[--(*hsize)];
  for(i = 0; HEAP_LCHILD(i) < *hsize; i = j)
    {
      if(HEAP_RCHILD(i) >= *hsize || h[HEAP_LCHILD(i)].key < h[HEAP_RCHILD(i)].key)
	j = HEAP_LCHILD(i);
      else j = HEAP_RCHILD(i);
      if(h[i].key < h[j].key) break;
      heap_swap(h, i, j);
    }
}

void heap_push(struct heap h[], int *hsize, int k, int v)
{
  int i;
  h[*hsize].key = k; h[*hsize].val = v;
  for(i = (*hsize)++; i > 0 && h[i].key < h[HEAP_PARENT(i)].key; i = HEAP_PARENT(i))
    heap_swap(h, i, HEAP_PARENT(i));
}

int cmp(const void *va, const void *vb)
{
  int a = ((struct point*)va)->pos, b = ((struct point*)vb)->pos;
  if(a == b) return 0;
  return a < b ? -1 : 1;
}

int segment_touch(int l1, int r1, int l2, int r2)
{
  return !(r1 < l2 || r2 < l1);
}

int segment_overlap(int l1, int r1, int l2, int r2)
{
  return !(r1 <= l2 || r2 <= l1);
}

int proc_edges(struct point keypoints[], int from, int to, int side[], struct heap active[], int nactive, int b[], int t[])
{
  int segbot[5000], segtop[5000], nsegments = 0, i, j, k = 0;
  for(i=from;i<to;i++)
    {
      if(keypoints[i].pos == side[keypoints[i].id])
	{
	  segbot[nsegments] = b[keypoints[i].id]; segtop[nsegments] = t[keypoints[i].id];
	  nsegments++;
	}
    }
  for(i=0;i<nsegments;i++)
    {
      for(j=i+1;j<nsegments;j++)
	{
	  if(segment_touch(segbot[i], segtop[i], segbot[j], segtop[j]))
	    {
	      segbot[i] = MIN(segbot[i], segbot[j]); segtop[i] = MAX(segtop[i], segtop[j]);
	      segbot[j] = segbot[nsegments-1]; segtop[j] = segtop[nsegments-1];
	      nsegments--; j--;
	    }
	}
    }
  for(i=0;i<nactive;i++)
    {
      for(j=0;j<nsegments;j++)
	{
	  if(segment_overlap(segbot[j], segtop[j], b[active[i].val], t[active[i].val]))
	    {
	      if(b[active[i].val] > segbot[j])
		{
		  segbot[nsegments] = segbot[j]; segtop[nsegments] = b[active[i].val];
		  nsegments++;
		}
	      if(t[active[i].val] < segtop[j])
		{
		  segbot[nsegments] = t[active[i].val]; segtop[nsegments] = segtop[j];
		  nsegments++;
		}
	      segbot[j] = segbot[nsegments-1]; segtop[j] = segtop[nsegments-1];
	      nsegments--; j--;
	    }
	}
    }
  for(i=0;i<nsegments;i++)
    k += segtop[i] - segbot[i];
  return k;
}

int sweeper(int n, int l[], int r[], int b[], int t[])
{
  struct heap active[5000];
  struct point keypoints[10000];
  int nactive = 0, totlen = 0, i, j, k;
  for(i=0;i<n;i++)
    {
      keypoints[2*i].pos = l[i]; keypoints[2*i+1].pos = r[i];
      keypoints[2*i].id = keypoints[2*i+1].id = i;
    }
  qsort(keypoints, 2*n, sizeof(struct point), cmp);
  for(i=0;i<2*n;i=j)
    {
      for(j = i+1; j < 2*n && keypoints[j].pos == keypoints[i].pos; j++);
      totlen += proc_edges(keypoints, i, j, l, active, nactive, b, t);
      for(k=i;k<j;k++)
	{
	  if(keypoints[k].pos == l[keypoints[k].id])
	    heap_push(active, &nactive, r[keypoints[k].id], keypoints[k].id);
	  else
	    heap_pop(active, &nactive);
	}
      totlen += proc_edges(keypoints, i, j, r, active, nactive, b, t);
    }
  return totlen;
}

int main()
{
  FILE *fin = fopen("picture.in", "r"), *fout = fopen("picture.out", "w");
  int n, left[5000], right[5000], top[5000], bot[5000], perim, i;
  fscanf(fin, "%d", &n);
  for(i=0;i<n;i++)
    fscanf(fin, "%d %d %d %d", &left[i], &bot[i], &right[i], &top[i]);
  perim = sweeper(n, left, right, bot, top) + sweeper(n, bot, top, left, right);
  fprintf(fout, "%d\n", perim);
  fclose(fin); fclose(fout);
}
