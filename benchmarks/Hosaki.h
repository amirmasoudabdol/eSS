/*Provide dimension of the problem.  Integer >= 1.*/
#define TEST_PROBLEM
#define N 2
/*Provide the diameter of the feasible region.*/
/*Provide maximum number of iterations.*/
#define MAXITER 100*N*N/*500*N */

#define PI 3.14159265359
#define SOL -2.3458

void bounds(double lb[], double ub[]);
int feasible(double x[]);
double objfn(double x[]);

void bounds(double lb[], double ub[])
/*Provide lower and upper bounds for each of N variables.
 Number of bounds is equal to N.*/
{
  lb[0] = 0;
  ub[0] = 5;
  lb[1] = 0;
  ub[1] = 6;
}

/*Test feasibility of x.  Return 1 if feasible, 0 if not.*/
int feasible(double x[])

{
	return 1;
}

/*Calculate objective function value of x[].*/
double objfn(double x[])
{
	double sum=0.;

	sum = (1. - 8.*x[0] + 7.*x[0]*x[0] - 7./3*x[0]*x[0]*x[0] + 1./4*x[0]*x[0]*x[0]*x[0]);
	sum = sum*x[1]*x[1]*exp(-x[1]);
	return (sum);

}
