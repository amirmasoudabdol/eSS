#include "ess.h"

#ifdef GSL_TESTFUNCTION
int levmer_localSearch(eSSType *eSSParams, individual *ind, void *inp, void *out){

	const gsl_multifit_fdfsolver_type *T;
	gsl_multifit_fdfsolver *s;
	int status;
	unsigned int i, iter = 0;
	const size_t n = 40;
	const size_t p = 3;


	gsl_matrix *covar = gsl_matrix_alloc (p, p);
	gsl_multifit_function_fdf f;
	print_Ind(eSSParams, ind);
	// gsl_vector_view x = gsl_vector_view_array (x_init, p);
	gsl_vector_view x = gsl_vector_view_array (ind->params, p);
	gsl_vector_fprintf(stdout, &x.vector, "%f");
	const gsl_rng_type * type;
	gsl_rng * r;


	gsl_rng_env_setup();

	type = gsl_rng_default;
	r = gsl_rng_alloc (type);

	f.f = &objfn;
	f.df = NULL; 
	f.fdf = NULL; 
	f.n = 40;		
	f.p = 3;		


	T = gsl_multifit_fdfsolver_lmsder;
	s = gsl_multifit_fdfsolver_alloc (T, n, p);
	gsl_multifit_fdfsolver_set (s, &f, &x.vector);


	printf("Start...\n");
	do
	{
		iter++;
		status = gsl_multifit_fdfsolver_iterate (s);
	
		printf ("iter: %3u x = % 15.8f % 15.8f % 15.8f "
		  "|f(x)| = %g\n",
		  iter,
		  gsl_vector_get (s->x, 0), 
		  gsl_vector_get (s->x, 1),
		  gsl_vector_get (s->x, 2), 
		  gsl_blas_dnrm2 (s->f));

		printf ("status = %s\n", gsl_strerror (status));

		if (status)
			break;

		status = gsl_multifit_test_delta (s->dx, s->x,
			1e-4, 1e-4);
	}
	while (status == GSL_CONTINUE && iter < 500);

	gsl_multifit_covar (s->J, 0.0, covar);

// #define FIT(i) gsl_vector_get(s->x, i)
// #define ERR(i) sqrt(gsl_matrix_get(covar,i,i))

// 	{ 
// 		double chi = gsl_blas_dnrm2(s->f);
// 		double dof = n - p;
// 		double c = GSL_MAX_DBL(1, chi / sqrt(dof)); 

// 		printf("chisq/dof = %g\n",  pow(chi, 2.0) / dof);

// 		printf ("A      = %.5f +/- %.5f\n", FIT(0), c*ERR(0));
// 		printf ("lambda = %.5f +/- %.5f\n", FIT(1), c*ERR(1));
// 		printf ("b      = %.5f +/- %.5f\n", FIT(2), c*ERR(2));
// 	}

// 	printf ("status = %s\n", gsl_strerror (status));

	gsl_multifit_fdfsolver_free (s);
	gsl_matrix_free (covar);
	gsl_rng_free (r);
	return 0;

}
#endif
