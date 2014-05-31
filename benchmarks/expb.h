#include <math.h>
#include <gsl/gsl_vector.h>
/*Provide dimension of the problem.  Integer >= 1.*/
#define TEST_PROBLEM
#define N 3
/*Provide the diameter of the feasible region.*/
/*Provide maximum number of iterations.*/
#define MAXITER 100*N*N/*500*N */

#define PI 3.14159265359
#define SOL 0

// void bounds(double lb[], double ub[]);
// int feasible(double x[]);
// int objfn(const gsl_vector *x, void *data, gsl_vector *f);

void bounds(double lb[], double ub[])
/*Provide lower and upper bounds for each of N variables.
 Number of bounds is equal to N.*/
{
  lb[0] = -6;
  ub[0] = 6;
  lb[1] = -2;
  ub[1] = 2;
  lb[2] = -2;
  ub[2] = 2;

}

/*Test feasibility of x.  Return 1 if feasible, 0 if not.*/
int feasible(double x[])

{
	return 1;
}

/*Calculate objective function value of x[].*/
int objfn(const gsl_vector *x, void *data, gsl_vector *f)
{
	printf("hi, ");
	const double y[] = {6.01339, 5.51538, 5.26109, 4.77746, 4.45135, 
							3.9049, 3.50439, 3.415, 3.24274, 3.1222, 2.83763, 
							2.5347, 2.43917, 2.38083, 2.31609, 2.06083, 1.94568,
							1.91413, 1.75951, 1.66507, 1.73793, 1.57552, 1.52507,
							1.40961, 1.39521, 1.41689, 1.37604, 1.26095, 1.28963,
							1.42267, 1.22829, 1.19918, 1.18999, 0.930076, 1.22461,
							1.14738, 1.114, 1.19512, 1.26958, 1.06198};
	const double sigma[] =  {0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
							 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
							 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
							 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
							 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1};

  double A = gsl_vector_get (x, 0);
  double lambda = gsl_vector_get (x, 1);
  double b = gsl_vector_get (x, 2);
	// double sumq = 0;

	int i; int n = 40;
	for (i = 0; i < n; i++)
	{
		/* Model Yi = A * exp(-lambda * i) + b */
		double t = i;
		double Yi = A * exp (-lambda * t) + b;
      	gsl_vector_set (f, i, (Yi - y[i])/sigma[i]);
		// sumq += gsl_vector_get (f, i)* gsl_vector_get (f, i);
	}	

  	printf("% 15.8f % 15.8f % 15.8f --> %g\n", A, lambda, b, gsl_blas_dnrm2(f));
	// return sqrt(sumq/40);
	return 0;
}
