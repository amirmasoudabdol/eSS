
#define TEST_PROBLEM "Neumaier3"
#define N 10

#define PI 3.14159265359
#define SOL -210


void bounds(double lb[], double ub[])
/*Provide lower and upper bounds for each of N variables.
 Number of bounds is equal to N.*/
{
	int i;

	for (i=0; i<N; i++)
	{
		lb[i] = -1.0*N*N;
		ub[i] = 1.0*N*N;
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
	int i;
	double sum=0.0, obj1=0.0, obj2=0.0;

	for (i=0; i<N; i++)
	{
		obj1 += pow(x[i]-1.0,2);
	}
	for (i=1; i<N; i++)
	{
		obj2 += x[i]*x[i-1];
	}

	sum = obj1-obj2;

	return (sum);

}

double nelder_objfn(const gsl_vector *x, void *data){
	
	return objfn(x->data);
}

int levermed_objfn(const gsl_vector *x, void *data, gsl_vector *f){
	return 0;
}
