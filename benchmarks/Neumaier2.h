
#define TEST_PROBLEM "Neumaier2"
#define N 4

#define PI 3.14159265359
#define SOL 0.


void bounds(double lb[], double ub[])
/*Provide lower and upper bounds for each of N variables.
 Number of bounds is equal to N.*/
{
  lb[0] = 0;
  ub[0] = 1;
  lb[1] = 0;
  ub[1] = 2;
  lb[2] = 0;
  ub[2] = 3;
  lb[3] = 0;
  ub[3] = 4;

}

/*Test feasibility of x.  Return 1 if feasible, 0 if not.*/
int feasible(double x[])

{
	return 1;
}

/*Calculate objective function value of x[].*/
double objfn(double x[])
{
	int i,k;
	double sum=0.0, sum1=0.0;
	static double b[4] = {8.0, 18.0, 44.0, 114.0};

	for (k=0; k<N; k++)
	{
		sum1 = 0.;
		for (i=0; i<N; i++)
		{
			sum1+= pow(x[i],k+1);
		}
		sum+= pow(b[k]-sum1,2);
	}

	return (sum);

}

double nelder_objfn(const gsl_vector *x, void *data){
	
	return objfn(x->data);
}
