#include <math.h>
 
#define TEST_PROBLEM "Helical"
#define N 3

#define PI 3.14159265359
#define SOL 0 


void bounds(double lb[], double ub[])
/*Provide lower and upper bounds for each of N variables.
 Number of bounds is equal to N.*/
{
	int i;

	for (i=0; i<N; i++)
	{
		lb[i] = -10.0;
		ub[i] = 10.0;
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
	double sum=0., subsum=0., theta=0.;

	if (x[0]<=0.)
	{
		theta = (1.0/(2.0/PI))*atan2(x[1],x[0]);
	}
	if (x[0]>0.)
	{
		theta = (1.0/(2.0/PI))*atan2(x[1],x[0]) + 0.5;
	}

	subsum = pow(sqrt(x[0]*x[0] + x[1]*x[1]) - 1.0,2);
	sum = 100*(pow(x[1]-10*theta,2) + subsum) + x[2]*x[2];
          // printf("%f %f %f\n", theta, subsum, sum);

	return (sum);

}

double nelder_objfn(const gsl_vector *x, void *data){
	
	return objfn(x->data);
}

int levermed_objfn(const gsl_vector *x, void *data, gsl_vector *f){
	return 0;
}

