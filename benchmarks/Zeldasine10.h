#include <math.h>

/*Provide dimension of the problem.  Integer >= 1.*/
#define TEST_PROBLEM
#define N 10
/*Provide the diameter of the feasible region.*/
/*Provide maximum number of iterations.*/
#define MAXITER 100*N*N/*500*N */

#define PI 3.14159265359
#define SOL -3.5

void bounds(double lb[], double ub[]);
int feasible(double x[]);
double objfn(double x[]);

void bounds(double lb[], double ub[])
/*Provide lower and upper bounds for each of N variables.
 Number of bounds is equal to N.*/
{
	int i;

	for (i=0; i<N; i++)
	{
		lb[i] = 0;
		ub[i] = PI;
	}
 
}

/*Test feasibility of x.  Return 1 if feasible, 0 if not.*/
int feasible(double x[])

{
	return 1;
}

/*Calculate objective function value of x[].*/
double objfn(double x[])
{
	int j;
	double sum=0., prod1=1., prod2=1.;
	double A=2.5, B=5., z=PI/6;

	for (j=0; j<N; j++)
	{
		prod1 *= sin(x[j]-z);
		prod2 *= sin(B*(x[j]-z));
	}
	sum = -(A*prod1 + prod2);

	return (sum);

}
