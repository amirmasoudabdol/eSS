
#define TEST_PROBLEM "Schaffer1"
#define N 2

#define PI 3.14159265359
#define SOL 0 


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
	double sum=0.,num=0.,den=0.;

	num = pow((sin(sqrt(x[0]*x[0]+x[1]*x[1]))),2) - 0.5;
	den = pow((1+.001*(x[0]*x[0]+x[1]*x[1])),2);
	sum = 0.5 + num/den;

	return (sum);

}

double nelder_objfn(const gsl_vector *x, void *data){
	
	return objfn(x->data);
}


// FIXME: Something fishy happening here, when I use this function,
// although I don't compute the distance the distance property has value
// which shoudln't!