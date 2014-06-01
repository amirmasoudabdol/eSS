
#define TEST_PROBLEM "Schubert"
#define N 2

#define PI 3.14159265359
#define SOL -186.7309


void bounds(double lb[], double ub[])
/*Provide lower and upper bounds for each of N variables.
 Number of bounds is equal to N.*/
{
  lb[0] = -10;
  ub[0] = 10;
  lb[1] = -10;
  ub[1] = 10;
  
}

/*Test feasibility of x.  Return 1 if feasible, 0 if not.*/
int feasible(double x[])

{
	return 1;
}

/*Calculate objective function value of x[].*/
double objfn(double x[])
{
	int i,j;
	double sum=0., prod=1.;


	for (i=0; i<N; i++)
	{
		sum = 0.;
		for (j=1; j<=5; j++)
			sum = sum + j*cos((j+1)*x[i]+j);
		prod = prod*sum;
	}
	
    return (prod);

}
