
#define TEST_PROBLEM "MeyerRoth"
#define N 3

#define PI 3.14159265359
#define SOL 0.0019


void bounds(double lb[], double ub[])
/*Provide lower and upper bounds for each of N variables.
 Number of bounds is equal to N.*/
{
  lb[0] = -10;
  ub[0] = 10;
  lb[1] = -10;
  ub[1] = 10;
  lb[2] = -10;
  ub[2] = 10;

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
	double sum=0., num=0., den=0.;
	static double t[5] = {1., 2., 1., 2., .1};
	static double v[5] = {1., 1., 2., 2., 0.};
	static double y[5] = {.126, .219, .076, .126, .186};

	for (i=0; i<5; i++)
	{
		num = x[0]*x[2]*t[i];
		den = 1.+x[0]*t[i]+x[1]*v[i];
		sum+= pow(num/den-y[i],2);
	}


	return (sum);

}

double nelder_objfn(const gsl_vector *x, void *data){
	
	return objfn(x->data);
}
