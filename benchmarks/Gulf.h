/*Provide dimension of the problem.  Integer >= 1.*/
#define TEST_PROBLEM
#define N 3
/*Provide the diameter of the feasible region.*/
/*Provide maximum number of iterations.*/
#define MAXITER 100*N*N/*500*N */

#define PI 3.14159265359
#define SOL 0 

void bounds(double lb[], double ub[]);
int feasible(double x[]);
double objfn(double x[]);

void bounds(double lb[], double ub[])
/*Provide lower and upper bounds for each of N variables.
 Number of bounds is equal to N.*/
{
  lb[0] = .1;
  ub[0] = 100;
  lb[1] = 0;
  ub[1] = 25.6;
  lb[2] = 0;
  ub[2] = 5.;

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
	double sum=0.,subsum=0.,u;

	for (j=0; j<99; j++)
	{
		u=25.+pow(-50*log(.01*j),.66666);
		subsum=exp(-pow(u-x[1],x[2])/x[0])-0.01*j; 
		sum+= pow(subsum,2);
                  //                  printf("j %d %f %f\n", j,u,subsum);
	}

	return (sum);

}
