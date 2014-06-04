#include <math.h>

#define TEST_PROBLEM "Schaffer2"
#define N 2

#define PI 3.14159265359
#define SOL 0.0012


void bounds(double lb[], double ub[])
/*Provide lower and upper bounds for each of N variables.
 Number of bounds is equal to N.*/
{
  lb[0] = -100;
  ub[0] = 100;
  lb[1] = -100;
  ub[1] = 100;

}

/*Test feasibility of x.  Return 1 if feasible, 0 if not.*/
int feasible(double x[])

{
	return 1;
}

/*Calculate objective function value of x[].*/
double objfn(double x[])
{
	double sum=0., prod1=0., prod2=0.;

	prod1 = pow(x[0]*x[0]+x[1]*x[1],0.25);
	prod2 = pow(50*(x[0]*x[0]+x[1]*x[1]),0.1);
	sum = prod1*(sin(sin(prod2))+1.0);

	return (sum);

}

double nelder_objfn(const gsl_vector *x, void *data){
	
	return objfn(x->data);
}

int levermed_objfn(const gsl_vector *x, void *data, gsl_vector *f){
	return 0;
}
