/*
  ID: abacles1
  TASK: charrec
  LANG: C
*/

#include <stdio.h>

int main()
{
  FILE *fin = fopen("charrec.in", "r"), *fout = fopen("charrec.out", "w"), *ffont = fopen("font.in", "r");
  int nlines, error[1200][27][20], dp[1201], match[1201], prev[1201], yhat[60], i, j, k, l, e;
  char font[27][20][21], text[1200][21];
  fscanf(ffont, "%d", &nlines);
  for(i=0;i<27;i++)
    {
      for(j=0;j<20;j++)
	fscanf(ffont, "%s", font[i][j]);
    }
  fscanf(fin, "%d", &nlines);
  for(i=0;i<nlines;i++)
    {
      fscanf(fin, "%s", text[i]);
      for(j=0;j<27;j++)
	{
	  for(k=0;k<20;k++)
	    {
	      for(l=error[i][j][k]=0;l<20;l++)
		error[i][j][k] += text[i][l] != font[j][k][l];
	    }
	}
    }
  for(i=0;i<=nlines;dp[i++]=-1);
  dp[0] = 0;
  for(i=19;i<=nlines;i++)
    {
      if(dp[i-19] >= 0 || (i >= 20 && dp[i-20] >= 0) || (i >= 21 && dp[i-21] >= 0))
	{
	  for(j=0;j<27;j++)
	    {
	      if(i >= 19 && dp[i-19] >= 0)
		{
		  for(l=0;l<20;l++)
		    {
		      for(k=e=0;k<19;k++)
			e += error[i-19+k][j][k<l?k:k+1];
		      if(e + dp[i-19] < dp[i] || dp[i] == -1)
			{
			  dp[i] = e + dp[i-19];
			  match[i] = j;
			  prev[i] = i - 19;
			}	
		    }
		}
	      if(i >= 20 && dp[i-20] >= 0)
		{
		  for(k=e=0;k<20;k++)
		    e += error[i-20+k][j][k];
		  if(e + dp[i-20] < dp[i] || dp[i] == -1)
		    {
		      dp[i] = e + dp[i-20];
		      match[i] = j;
		      prev[i] = i - 20;
		    }
		}
	      if(i >= 21 && dp[i-21] >= 0)
		{
		  for(l=0;l<21;l++)
		    {
		      for(k=e=0;k<20;k++)
			e += error[i-21+(k<l?k:k+1)][j][k];
		      if(e + dp[i-21] < dp[i] || dp[i] == -1)
			{
			  dp[i] = e + dp[i-21];
			  match[i] = j;
			  prev[i] = i - 21;
			}	
		    }
		}
	    }
	}
    }
  for(i=nlines,j=0;i;i=prev[i])
    yhat[j++] = match[i];
  while(--j >= 0)
    fputc(yhat[j] ? 'a'+yhat[j]-1 : ' ', fout);
  fputc('\n', fout);
  fclose(fin); fclose(fout); fclose(ffont);
}
