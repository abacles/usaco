/*
ID: abacles1
LANG: C
TASK: ratios
*/

#include <stdio.h>

int coeff[3][3];

int divide(int a,int b)
{
  if(!a)
    return 0;
  return a/b;
}

int mod(int a,int b)
{
  if(!a)
    return 0;
  return a%b;
}

int eq(int a,int b,int c)
{
  if(a == b && b == c)
    return 1;
  if(a == 0 && b == c || b == 0 && a == c || c == 0 && a ==b )
    return 1;
  return 0;
}

int det2(int m11,int m12,int m21,int m22)
{
  return (m11 * m22 - m12 * m21);
}

int det3()
{
  return (coeff[0][0]*coeff[1][1]*coeff[2][2] +
	  coeff[0][1]*coeff[1][2]*coeff[2][0] +
	  coeff[0][2]*coeff[1][0]*coeff[2][1] -
	  coeff[0][2]*coeff[1][1]*coeff[2][0] -
	  coeff[0][0]*coeff[1][2]*coeff[2][1] -
	  coeff[0][1]*coeff[1][0]*coeff[2][2]);
}

int inv_coeff()
{
  int det = det3();
  int cofact[3][3];
  int i,j;
  cofact[0][0] = det2(coeff[1][1],coeff[1][2],coeff[2][1],coeff[2][2]);
  cofact[0][1] = -det2(coeff[1][0],coeff[1][2],coeff[2][0],coeff[2][2]);
  cofact[0][2] = det2(coeff[1][0],coeff[1][1],coeff[2][0],coeff[2][1]);
  cofact[1][0] = -det2(coeff[0][1],coeff[0][2],coeff[2][1],coeff[2][2]);
  cofact[1][1] = det2(coeff[0][0],coeff[0][2],coeff[2][0],coeff[2][2]);
  cofact[1][2] = -det2(coeff[0][0],coeff[0][1],coeff[2][0],coeff[2][1]);
  cofact[2][0] = det2(coeff[0][1],coeff[0][2],coeff[1][1],coeff[1][2]);
  cofact[2][1] = -det2(coeff[0][0],coeff[0][2],coeff[1][0],coeff[1][2]);
  cofact[2][2] = det2(coeff[0][0],coeff[0][1],coeff[1][0],coeff[1][1]);
  for(i=0;i<3;i++)
    {
      for(j=0;j<3;j++)
	coeff[j][i] = cofact[i][j];
    }
  return det;
}

int main()
{
  FILE *in = fopen("ratios.in","r"),*out = fopen("ratios.out","w");
  int goal[3],mix[3][3],div;
  int i,j,k,min[3]={100,100,100},minrat=-1,cst[3],curr[3],fail;
  fscanf(in,"%d %d %d",&goal[0],&goal[1],&goal[2]);
  for(i=0;i<3;i++)
    fscanf(in,"%d %d %d",&mix[i][0],&mix[i][1],&mix[i][2]);
  fclose(in);
  for(i=0;i<3;i++)
    {
      coeff[i][0] = goal[i];
      for(j=1;j<3;j++)
	coeff[i][j] = -mix[j][i];
    }
  div = inv_coeff();
  if(!div)
    {
      for(i=0;i<100;i++)
	{
	  for(j=0;j<100;j++)
	    {
	      curr[0] = mix[1][0]*i+mix[2][0]*j;
	      curr[1] = mix[1][1]*i+mix[2][1]*j;
	      curr[2] = mix[1][2]*i+mix[2][2]*j;
	      if((mod(curr[0],goal[0])==0 && mod(curr[1],goal[1])==0 && mod(curr[2],goal[2])==0) && eq(divide(curr[0],goal[0]),divide(curr[1],goal[1]),divide(curr[2],goal[2])))
		{
		  if(i+j > 0 && i+j < min[1]+min[2])
		    {
		      min[0] = 0;
		      min[1] = i;
		      min[2] = j;
		      if(goal[0]==0)
			minrat = curr[1] / goal[1];
		      else if(goal[1]==0)
			minrat = curr[2] / goal[2];
		      else
			minrat = curr[0] / goal[0];
		    }
		}
	    }
	}
      goto OUTPUT;
    }
  for(i=0;i<3;i++)
    for(j=0;j<3;j++)
      printf("%d%c",coeff[i][j],j==2?'\n':' ');
  for(i=0;i<100;i++)
    {
      for(j=0;j<3;j++)
	cst[j] = i * mix[0][j];
      fail = 0;
      for(j=0;j<3;j++)
	{
	  if(!((coeff[j][0]*cst[0] + coeff[j][1]*cst[1] + coeff[j][2]*cst[2])%div == 0))
	    {
	      fail = 1;
	      break;
	    }
	  curr[j] = (coeff[j][0]*cst[0] + coeff[j][1]*cst[1] + coeff[j][2]*cst[2]) / div;
	}
      if(!fail && curr[0]>=0 && curr[1]>=0 && curr[2]>0)
	{
	  if(i+curr[0]+curr[1] < min[0]+min[1]+min[2])
	    {
	      min[0] = i;
	      min[1] = curr[1];
	      min[2] = curr[2];
	      minrat = curr[0];
	    }
	}
    }
 OUTPUT:
  if(minrat > 0)
    fprintf(out,"%d %d %d %d\n",min[0],min[1],min[2],minrat);
  else
    fprintf(out,"NONE\n");
  fclose(out);
}
