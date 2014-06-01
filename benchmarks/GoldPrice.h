
#define TEST_PROBLEM "GoldPrice"
#define N 2

#define PI 3.14159265359
#define SOL 3.0


void bounds(double lb[], double ub[])
/*Provide lower and upper bounds for each of N variables.
 Number of bounds is equal to N.*/
{
  lb[0] = -2;
  ub[0] = 2;
  lb[1] = -2;
  ub[1] = 2;

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

    sum = (1+(x[0]+x[1]+1)*(x[0]+x[1]+1)*(19-14*x[0]+3*x[0]*x[0]-14*x[1]+6*x[0]*x[1]+3*x[1]*x[1]));
	sum = sum*(30+(2*x[0]-3*x[1])*(2*x[0]-3*x[1])*(18-32*x[0]+12*x[0]*x[0]+48*x[1]-36*x[0]*x[1]+27*x[1]*x[1]));

	return (sum);

}

double nelder_objfn(const gsl_vector *x, void *data){
	
	return objfn(x->data);
}
