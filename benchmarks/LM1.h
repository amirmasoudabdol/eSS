/*Levy and Montalvo Problem 1 */

#define TEST_PROBLEM "LM1"
#define N 3

#define PI 3.14159265359
#define SOL 0 


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
	int j;
	double sum=0., zw1, zw2;

	zw1 = 10*pow(sin(PI*(1+.25*(x[0]+1))),2);
	zw2 = pow(.25*(x[N-1]+1),2);

	for (j=0; j<(N-1); j++)
	{
		zw1 += pow(.25*(x[j]+1),2)*(1+pow(sin(PI*(.25*x[j+1])),2));
	}
	sum = PI/N*(zw1+zw2);

	return (sum);

}

double nelder_objfn(const gsl_vector *x, void *data){
	
	return objfn(x->data);
}

int levermed_objfn(const gsl_vector *x, void *data, gsl_vector *f){
	return 0;
}
