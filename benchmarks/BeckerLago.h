#include <math.h>

#define TEST_PROBLEM "BeckerLago"
#define N 2

#define PI 3.14159265359
#define SOL 0

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
	
	sum = pow(fabs(x[0])-5.,2) + pow(fabs(x[1])-5.,2);

	return (sum);

}

double nelder_objfn(const gsl_vector *x, void *data){

	return objfn(x->data);
}

int levermed_objfn(const gsl_vector *x, void *data, gsl_vector *f){
	return 0;
}