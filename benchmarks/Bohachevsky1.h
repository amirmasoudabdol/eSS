
#define TEST_PROBLEM "Bohachevsky1"
#define N 2

#define PI 3.14159265359
#define SOL 0 


void bounds(double lb[], double ub[])
/*Provide lower and upper bounds for each of N variables.
 Number of bounds is equal to N.*/
{
  lb[0] = -50;
  ub[0] = 50;
  lb[1] = -50;
  ub[1] = 50;

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

	sum = pow(x[0],2) + 2.*x[1]*x[1] - .3*cos(3*PI*x[0]) -.4*cos(4*PI*x[1]) + .7;

	return (sum);

}

double nelder_objfn(const gsl_vector *x, void *data){
	
	return objfn(x->data);
}

int levermed_objfn(const gsl_vector *x, void *data, gsl_vector *f){
	return 0;
}
