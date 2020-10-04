/*
ID: abacles1
LANG: C
TASK: ride
*/

#include <stdio.h>

int main()
{
  FILE *in=fopen("ride.in","r"),*out=fopen("ride.out","w");
  char ufo [8],group [8];
  long int ufo_id=1,group_id=1;
  int i;
  fscanf(in,"%s",ufo);
  fscanf(in,"%s",group);
  for(i=0;ufo [i]!='\n' && ufo [i]!='\0';i++)
    ufo_id*=(ufo [i]-'A'+1);
  for(i=0;group [i]!='\n' && group [i]!='\0';i++)
    group_id*=(group [i]-'A'+1);
  if(ufo_id%47==group_id%47)
    fprintf(out,"GO\n");
  else
    fprintf(out,"STAY\n");
  fclose(in);
  fclose(out);
  return 0;
}
