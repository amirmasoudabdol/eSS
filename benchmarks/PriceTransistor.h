#include <math.h>
/*Price's Transistor Modeling Problem*/

#define TEST_PROBLEM "PriceTransistor"
#define N 9

#define PI 3.14159265359
#define SOL 0 


void bounds(double lb[], double ub[])
/*Provide lower and upper bounds for each of N variables.
 Number of bounds is equal to N.*/
{
	int i;

	for (i=0; i<N; i++)
	{
		lb[i] = 0;
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
	int k;
	double sum=0.0, sumsqr=0.0, alpha, beta;
	static double g[5][4] = {
		{0.485, 0.752, 0.869, 0.982},
		{0.369, 1.254, 0.703, 1.455},
		{5.2095, 10.0677, 22.9274, 20.2153},
		{23.3037, 101.779, 111.461, 191.267},
		{28.5132, 111.8467, 134.3884, 211.4823}};

	for (k=0; k<4; k++)
	{
		alpha = (1.0-x[0]*x[1])*x[2]*(exp(x[4]*(g[0][k]-0.001*g[2][k]*x[6]-0.001*x[7]*g[4][k]))-1.0) - g[4][k] + g[3][k]*x[1];
		beta = (1.0-x[0]*x[1])*x[3]*(exp(x[5]*(g[0][k]-g[1][k]-0.001*g[2][k]*x[6]+g[3][k]*0.001*x[8]))-1.0)- g[4][k]*x[0] + g[3][k];
		sumsqr += alpha*alpha + beta*beta;
	}
	sum = pow(x[0]*x[2] - x[1]*x[3],2) + sumsqr;

	return (sum);

}

double nelder_objfn(const gsl_vector *x, void *data){
	
	return objfn(x->data);
}

