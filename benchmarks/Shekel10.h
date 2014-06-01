#include <math.h>


#define TEST_PROBLEM "Shekel10"
#define N 4

#define PI 3.14159265359
#define SOL -10.5264


void bounds(double lb[], double ub[])
/*Provide lower and upper bounds for each of N variables.
 Number of bounds is equal to N.*/
{
  lb[0] = 0;
  ub[0] = 10;
  lb[1] = 0;
  ub[1] = 10;
  lb[2] = 0;
  ub[2] = 10;
  lb[3] = 0;
  ub[3] = 10;
      
}

/*Test feasibility of x.  Return 1 if feasible, 0 if not.*/
int feasible(double x[])

{
	return 1;
}

/*Calculate objective function value of x[].*/
double objfn(double x[])
{
	int i,j;
	double den,sum=0.;
	static double a[10][4] = {
		{4, 4, 4, 4},{1, 1, 1, 1},
		{8, 8, 8, 8},{6, 6, 6, 6},
		{3, 7, 3, 7},{2, 9, 2, 9},
		{5, 5, 3, 3},{8, 1, 8, 1},
		{6, 2, 6, 2},{7, 3.6, 7, 3.6}};
	static double c[10]={.1,.2,.2,.4,.4,.6,.3,.7,.5,.5};
	
	for (i=0; i<10; i++) {
		den = 0.;
		for (j=0; j<N; j++) {
			den = den + pow((x[j]-a[i][j]),2);
		}
		sum = sum - 1.0/(den + c[i]);
	}

	return sum;
}
	



