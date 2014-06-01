
#define TEST_PROBLEM "Paviani"
#define N 10

#define PI 3.14159265359
#define SOL -45.7784


void bounds(double lb[], double ub[])
/*Provide lower and upper bounds for each of N variables.
 Number of bounds is equal to N.*/
{
	int i;

	for (i=0; i<N; i++)
	{
		lb[i] = 2;
		ub[i] = 10;
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
	double sum=0.0, sum1=0.0, prod1=1.0, prod=1.0;

	for (j=0; j<N; j++)
	{
		prod1 = prod1*x[j];
		sum1 = sum1 + pow((double) log(x[j]-2),2) + pow((double) log(10-x[j]),2);
	}

	prod = pow((double) prod1,0.2);
	sum = sum1-prod;

	return (sum);

}

double nelder_objfn(const gsl_vector *x, void *data){
	
	return objfn(x->data);
}
