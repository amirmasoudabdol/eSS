#include <math.h> 
#define TEST_PROBLEM "Rastrigin"
#define N 10

#define PI 3.14159265359
#define SOL 0 


void bounds(double lb[], double ub[])
/*Provide lower and upper bounds for each of N variables.
 Number of bounds is equal to N.*/
{
  lb[0] = -512;
  ub[0] = 512;
  lb[1] = -512;
  ub[1] = 512;
  lb[2] = -512;
  ub[2] = 512;
  lb[3] = -512;
  ub[3] = 512;
  lb[4] = -512;
  ub[4] = 512;
  lb[5] = -512;
  ub[5] = 512;
  lb[6] = -512;
  ub[6] = 512;
  lb[7] = -512;
  ub[7] = 512;
  lb[8] = -512;
  ub[8] = 512;
  lb[9] = -512;
  ub[9] = 512;

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
	double sum=0.;

	for (j=0; j<N; j++)
	{
		sum+=x[j]*x[j]-10.*cos(2.*PI*x[j])+10.;
	}

	return (sum);

}

double nelder_objfn(const gsl_vector *x, void *data){
	
	return objfn(x->data);
}

int levermed_objfn(const gsl_vector *x, void *data, gsl_vector *f){
	return 0;
}
