
#define TEST_PROBLEM "CosMix2"
#define N 2

#define PI 3.14159265359
#define SOL -0.2


void bounds(double lb[], double ub[])
/*Provide lower and upper bounds for each of N variables.
 Number of bounds is equal to N.*/
{
  lb[0] = -1.;
  ub[0] = 1.;
  lb[1] = -1.;
  ub[1] = 1.;

}

/*Test feasibility of x.  Return 1 if feasible, 0 if not.*/
int feasible(double x[])

{
	return 1;
}

/*Calculate objective function value of x[].*/
double objfn(double x[])
{
	int i;
	double sum1=0., sum2=0., sum=0.;


	for (i=0; i<N; i++)
	{
		sum1 = sum1 + cos(5*PI*x[i]);
		sum2 = sum2 + pow(x[i],2);
	}
	sum = 0.1*sum1 - sum2;
	return (-sum);

}

double nelder_objfn(const gsl_vector *x, void *data){
	
	return objfn(x->data);
}
