/*Easom Problem */
/*Provide dimension of the problem.  Integer >= 1.*/
#define TEST_PROBLEM
#define N 2
/*Provide the diameter of the feasible region.*/
/*Provide maximum number of iterations.*/
#define MAXITER 100*N*N/*500*N */

#define PI 3.14159265359
#define SOL -1

void bounds(double lb[], double ub[]);
int feasible(double x[]);
double objfn(double x[]);

void bounds(double lb[], double ub[])
/*Provide lower and upper bounds for each of N variables.
 Number of bounds is equal to N.*/
{
  lb[0] = -10;
  ub[0] = 10;
  lb[1] = -10;
  ub[1] = 10;

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

	sum = -cos(x[0])*cos(x[1])*exp(-pow(x[0]-PI,2)-pow(x[1]-PI,2));

	return (sum);

}
