/*Provide dimension of the problem.  Integer >= 1.*/
#define TEST_PROBLEM
#define N 2
/*Provide the diameter of the feasible region.*/
/*Provide maximum number of iterations.*/
#define MAXITER 100*N*N/*500*N */

#define PI 3.14159265359
#define SOL 0
#define X_SOL 3
#define Y_SOL 0.5

void bounds(double lb[], double ub[]);
int feasible(double x[]);
double objfn(double x[]);

void bounds(double lb[], double ub[])
/*Provide lower and upper bounds for each of N variables.
 Number of bounds is equal to N.*/
{
  lb[0] = -5;
  ub[0] = 5;
  lb[1] = -5;
  ub[1] = 5;

}

/*Test feasibility of x.  Return 1 if feasible, 0 if not.*/
int feasible(double x[])

{
	return 1;
}

/*Calculate objective function value of x[].*/
double objfn(double x[])
{
	return pow((1.5 - x[0] + x[0]*x[1]),2) 
			+ pow((2.25 - x[0] + x[0]*pow(x[1], 2)), 2)
				+ pow((2.625 - x[0] + x[0]*pow(x[1],3)), 2);

}