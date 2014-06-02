
#define TEST_PROBLEM "MieleCantrell"
#define N 4

#define PI 3.14159265359
#define SOL 0 


void bounds(double lb[], double ub[])
/*Provide lower and upper bounds for each of N variables.
 Number of bounds is equal to N.*/
{
  lb[0] = -1;
  ub[0] = 1;
  lb[1] = -1;
  ub[1] = 1;
  lb[2] = -1;
  ub[2] = 1;
  lb[3] = -1;
  ub[3] = 1;

}

/*Test feasibility of x.  Return 1 if feasible, 0 if not.*/
int feasible(double x[])

{
	return 1;
}

/*Calculate objective function value of x[].*/
double objfn(double x[])
{
	double sum=0., sum1=0., sum2=0.;

	sum1 = pow(exp(x[0])-x[1],4) + 100.*pow(x[1]-x[2],6);
	sum2 = pow(tan(x[2]-x[3]),4) + pow(x[0],8);

	sum = sum1+sum2;

	return (sum);

}

double nelder_objfn(const gsl_vector *x, void *data){
	
	return objfn(x->data);
}

int levermed_objfn(const gsl_vector *x, void *data, gsl_vector *f){
	return 0;
}
