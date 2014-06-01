#include <math.h>


#define TEST_PROBLEM "Salomon"
#define N 5

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
  lb[2] = -100;
  ub[2] = 100;
  lb[3] = -100;
  ub[3] = 100;
  lb[4] = -100;
  ub[4] = 100;
 
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
  double sum=0;

  for (j=0; j<N; j++)
  { 
	  sum+=x[j]*x[j];
  }
  sum=sqrt(sum);
  sum = -cos(2.*PI*sum)+.1*sum+1.;

  // sum = (0.1*sqrt(x[1 - 1]*x[1 - 1] + x[2 - 1]*x[2 - 1] + x[3 - 1]*x[3 - 1] + x[4 - 1]*x[4 - 1] + x[5 - 1]*x[5 - 1]) - cos(6.28318530718*
  //    sqrt(x[1 - 1]*x[1 - 1] + x[2 - 1]*x[2 - 1] + x[3 - 1]*x[3 - 1] + x[4 - 1]*x[4 - 1] + x[5 - 1]*x[5 - 1])));

  return (sum);
}

double nelder_objfn(const gsl_vector *x, void *data){
  
  return objfn(x->data);
}
