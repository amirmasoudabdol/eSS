
#define TEST_PROBLEM "Wood"
#define N 4

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
  lb[3] = -10;
  ub[3] = 10;

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
	
	sum = 100*pow((x[1]-x[0]*x[0]),2) + (1-x[0])*(1-x[0])
		+90*pow((x[3]-x[2]*x[2]),2) + (1-x[2])*(1-x[2])
		+10.1*(pow((x[1]-1),2)+pow((x[3]-1),2))
		+19.8*(x[1]-1)*(x[3]-1);
/*	sum = 100*(x[1]-x[0]*x[0]) + pow((1-x[0]),2) + 90*(x[3]-x[2]*x[2]) + pow((1-x[2]),2);
    sum = sum + 10.1*(pow((x[1]-1),2) + pow((x[3]-1),2)) + 19.8*(x[1]-1)*(x[3]-1);
*/
    return (sum);

}

double nelder_objfn(const gsl_vector *x, void *data){
	
	return objfn(x->data);
}
