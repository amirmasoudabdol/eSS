#include <math.h>


#define TEST_PROBLEM "Zeldasine10"
#define N 10

#define PI 3.14159265359
#define SOL -3.5


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

double nelder_objfn(const gsl_vector *x, void *data){
	
	return objfn(x->data);
}

int levermed_objfn(const gsl_vector *x, void *data, gsl_vector *f){
	return 0;
}
