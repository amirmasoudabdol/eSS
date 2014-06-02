
#define TEST_PROBLEM "LM2n5"
#define N 5

#define PI 3.14159265359
#define SOL 0 


void bounds(double lb[], double ub[])
/*Provide lower and upper bounds for each of N variables.
 Number of bounds is equal to N.*/
{
  lb[0] = -5;
  ub[0] = 5;
  lb[1] = -5;
  ub[1] = 5;
  lb[2] = -5;
  ub[2] = 5;
  lb[3] = -5;
  ub[3] = 5;
  lb[4] = -5;
  ub[4] = 5;
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
	double sum=0., zw1, zw2;

	zw1 = pow(sin(3*PI*x[0]),2);
	zw2 = pow(x[N-1]-1,2)*(1+pow(sin(2*PI*x[N-1]),2));

	for (j=0; j<(N-1); j++)
	{
		zw1 += pow(x[j]-1,2)*(1+pow(sin(3*PI*x[j+1]),2));
	}
	sum = .1*(zw1+zw2);

	return (sum);

}

double nelder_objfn(const gsl_vector *x, void *data){
	
	return objfn(x->data);
}

int levermed_objfn(const gsl_vector *x, void *data, gsl_vector *f){
	return 0;
}
