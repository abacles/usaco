/*
  ID: abacles1
  LANG: C
  TASK: shopping
*/

#include <stdio.h>
#include <stdlib.h>

#define INF 25000

int offcount,prodcount;
int options[104][6] = {0}; // [i][0] = price, [i][2:] = count
int optcount = 0;
int code[1000] = {0},cnext = 1;
int cart[5] = {0};
int costs[6][6][6][6][6];

void print_options()
{
  int i,j,inv[6];
  for(i=0;i<1000;i++)
    {
      if(code[i])
	inv[code[i]] = i;
    }
  printf("%d options available:\n",optcount);
  for(i=0;i<optcount;i++)
    {
      for(j=1;j<6;j++)
	{
	  if(options[i][j])
	    printf("%dx item #%d, ",options[i][j],inv[j]);
	}
      printf("@ $%d\n",options[i][0]);
    }
}

int calculate()
{
  int i,j,k,l,m,n,best;
  costs[0][0][0][0][0] = 0;
  for(i=0;i<=cart[0];i++)
    {
      for(j=0;j<=cart[1];j++)
	{
	  for(k=0;k<=cart[2];k++)
	    {
	      for(l=0;l<=cart[3];l++)
		{
		  for(m=0;m<=cart[4];m++)
		    {
		      if(!(i + j + k + l + m))
			continue;
		      best = INF;
		      for(n=0;n<optcount;n++)
			{
			  if(i>=options[n][1] && j>=options[n][2] &&
			     k>=options[n][3] && l>=options[n][4] &&
			     m>=options[n][5] &&
			     costs[i-options[n][1]][j-options[n][2]][k-options[n][3]][l-options[n][4]][m-options[n][5]] + options[n][0] < best)
			    best = costs[i-options[n][1]][j-options[n][2]][k-options[n][3]][l-options[n][4]][m-options[n][5]] + options[n][0];
			}
		      costs[i][j][k][l][m] = best;
		    }
		}
	    }
	}
    }
  return costs[cart[0]][cart[1]][cart[2]][cart[3]][cart[4]];
}

int main()
{
  FILE *in = fopen("shopping.in","r"),*out = fopen("shopping.out","w");
  int i,j,k,l;
  fscanf(in,"%d",&offcount);
  for(i=0;i<offcount;i++)
    {
      for(fscanf(in,"%d",&j);j>0;j--)
	{
	  fscanf(in,"%d %d",&k,&l);
	  if(!code[k])
	    code[k] = cnext++;
	  options[optcount][code[k]] = l;
	}
      fscanf(in,"%d",&options[optcount++][0]);
    }
  fscanf(in,"%d",&prodcount);
  for(i=0;i<prodcount;i++)
    {
      fscanf(in,"%d %d %d",&j,&k,&options[optcount][0]);
      if(!code[j])
	code[j] = cnext++;
      cart[code[j]-1] = k;
      options[optcount++][code[j]] = 1;
    }
  // print_options();
  fprintf(out,"%d\n",calculate());
  fclose(out);
}
