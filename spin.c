/*
ID: abacles1
LANG: C
TASK: spin
*/

#include <stdio.h>

int main()
{
  FILE *in = fopen("spin.in","r"),*out = fopen("spin.out","w");
  int speed[5],wcount[5],wstart[5][5],wext[5][5],pos,start,end,stc,sta;
  int i,j,k,time;
  for(i=0;i<5;i++)
    {
      fscanf(in,"%d %d",speed+i,wcount+i);
      for(j=0;j<wcount[i];j++)
	fscanf(in,"%d %d",&wstart[i][j],&wext[i][j]);
    }
  fclose(in);
  for(time=0;time<360;time++)
    {
      for(j=0;j<360;j++)
	{
	  sta = 1;
	  for(i=0;i<5;i++)
	    {
	      stc = 0;
	      pos = (time * speed[i]) % 360;
	      for(k=0;k<wcount[i];k++)
		{
		  start = (wstart[i][k] + pos) % 360;
		  end = start + wext[i][k];
		  if(start < 360 && end >= 360)
		    stc = stc || (start <= j || j <= end % 360);
		  else
		    stc = stc || (start <= j && j <= end);
		}
	      sta = sta && stc;
	    }
	  if(sta)
	    {
	      fprintf(out,"%d\n",time);
	      fclose(out);
	      return 0;
	    }
	}
    }
  fprintf(out,"none\n");
  fclose(out);
  return 0;
}
