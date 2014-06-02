
#define TEST_PROBLEM "DekkersAarts"
#define N 2

#define PI 3.14159265359
#define SOL -24776.5138


void bounds(double lb[], double ub[])
/*Provide lower and upper bounds for each of N variables.
 Number of bounds is equal to N.*/
{
  lb[0] = -20;
  ub[0] = 20;
  lb[1] = -20;
  ub[1] = 20;

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

	sum = 100000.*x[0]*x[0] + x[1]*x[1] - pow((x[0]*x[0]+x[1]*x[1]),2) +pow((x[0]*x[0]+x[1]*x[1]),4)/100000;

	return (sum);

}

double nelder_objfn(const gsl_vector *x, void *data){
	
	return objfn(x->data);
}

int levermed_objfn(const gsl_vector *x, void *data, gsl_vector *f){
	return 0;
}
