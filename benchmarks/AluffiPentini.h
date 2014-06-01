
#define TEST_PROBLEM "AluffiPentini"
#define N 2

#define PI 3.14159265359
#define SOL -0.3523


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

	sum = .25*pow(x[0],4) -.5*x[0]*x[0] + .1*x[0] +.5*x[1]*x[1];

	return (sum);

}

double nelder_objfn(const gsl_vector *x, void *data){
	
	return objfn(x->data);
}
