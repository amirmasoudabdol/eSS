#include "ess.h"
// #include "benchmarks/Ackleys.h"
// #include "benchmarks/AluffiPentini.h"		// Accurate!
// #include "benchmarks/BeckerLago.h"		// Accurate!
// #include "benchmarks/Bohachevsky1.h"		// Accurate!
// #include "benchmarks/Bohachevsky2.h"		// Accurate!
// #include "benchmarks/Branin.h"			// Accurate!
// #include "benchmarks/Camel3.h"			// Accurate!
// #include "benchmarks/Camel6.h"			// Accurate!
// #include "benchmarks/CosMix2.h"			// Accurate!
// #include "benchmarks/CosMix4.h"			// Accurate!
// #include "benchmarks/DekkersAarts.h"		// Accurate!
// #include "benchmarks/Easom.h"				// Accurate!
// #include "benchmarks/EMichalewicz.h"		// Accurate!
// #include "benchmarks/Expo.h"				// Accurate!
// #include "benchmarks/GoldPrice.h"			// Accurate!
// #include "benchmarks/Hartman3.h"			// Accurate!
// #include "benchmarks/Hartman6.h"			// Accurate!
// #include "benchmarks/Kowalik.h"			// Accurate!
// #include "benchmarks/LM1.h"					// Accurate!
// #include "benchmarks/LM2n10.h"			// Accurate!
// #include "benchmarks/LM2n5.h"				// Accurate!
// #include "benchmarks/MeyerRoth.h"			// Accurate!
// #include "benchmarks/MieleCantrell.h"		// Accurate!
// #include "benchmarks/ModRosenbrock.h"		// Accurate!
// #include "benchmarks/MultiGauss.h"		// Accurate!
// #include "benchmarks/Neumaier2.h"			// Accurate!
// #include "benchmarks/Neumaier3.h"			// Accurate!
// #include "benchmarks/Paviani.h"			// Accurate!
// #include "benchmarks/Periodic.h"			// Accurate!
// #include "benchmarks/PowellQ.h"			// Accurate!
// #include "benchmarks/Schaffer1.h"			// Accurate!
// #include "benchmarks/Schaffer2.h"			// Accurate!
// #include "benchmarks/Schubert.h"			// Accurate!
// #include "benchmarks/Shekel10.h"			// Accurate!
// #include "benchmarks/Shekel5.h"			// Accurate!
// #include "benchmarks/Shekel7.h"			// Accurate!
// #include "benchmarks/Shekelfox10.h"		// Accurate!
// #include "benchmarks/Shekelfox5.h"		// Accurate!
// #include "benchmarks/Wood.h"				// Accurate!
// #include "benchmarks/Zeldasine10.h"		// Accurate!
// #include "benchmarks/Zeldasine20.h"		// Accurate!
// #include "benchmarks/Gulf.h"				// Accurate!
// #include "benchmarks/Rosenbrock.h"		// Accurate!
// #include "benchmarks/Beale.h"				// Accurate!
// #include "benchmarks/McCormic.h"			// Accurate!
// #include "benchmarks/Hosaki.h"			// Accurate!
// #include "benchmarks/Schwefel.h"			// Accurate!
// #include "benchmarks/Griewank.h"			// Accurate!		// ...
// #include "benchmarks/Helical.h"			// Accurate!	// not many subsituation // There was a problem in function definition
// #include "benchmarks/PriceTransistor.h"	// Not accurate enough!

// #include "benchmarks/Salomon.h"			// Not accurate!	// not many subsituation
// #include "benchmarks/STChebychev9.h"		// Not Accurate!		// ...
// #include "benchmarks/STChebychev17.h"		// Not Accurate!		// ...
// #include "benchmarks/Rastrigin.h"			// Not Accurate!		// I got it with performing warm start in a good solutions set
// #include "benchmarks/Modlangerman.h"		// Not accurate!
// #include "benchmarks/Oddsquare.h"			// Not accurate!
// 

#include "benchmarks/expb.h"


/**
 * Initialize the sample parameters for optimization
 */
void init_sampleParams(eSSType *eSSParams){


#ifdef TEST_PROBLEM
	eSSParams->n_Params = N;
	printf("%s", KCYN);
	printf("\n---------------------------------");
	printf("\n Analytic Solution: %lf \n", (double)SOL);
	printf("---------------------------------\n\n");
	printf("%s", KNRM);
#endif

	/**
	 * User Options
	 */
	// eSSParams->log_bound;
	// eSSParams->maxeval;
	// eSSParams->maxtime;
	// eSSParams->iterprint;
	// eSSParams->plot;
	// eSSParams->weight;
	// eSSParams->tolc;
	// eSSParams->prob_bound;
	// eSSParams->strategy;
	// eSSParams->inter_save;

	/**
	 * Global Options
	 */
	// eSSParams->n_Params = 2;

	eSSParams->maxiter = 2;
	eSSParams->maxStuck = 20;

	eSSParams->min_real_var = (double *)malloc(eSSParams->n_Params * sizeof(double));
	eSSParams->max_real_var = (double *)malloc(eSSParams->n_Params * sizeof(double));
	for (int i = 0; i < eSSParams->n_Params; ++i)
	{
		eSSParams->min_real_var[i] = 0;
		eSSParams->max_real_var[i] = 0;
	}

#ifdef TEST_PROBLEM
	bounds(eSSParams->min_real_var, eSSParams->max_real_var);
#endif
	
	eSSParams->n_refSet = ceil(1.0 + sqrt(1.0 + 40.0 * eSSParams->n_Params) / 2.0);
	if (eSSParams->n_refSet %2 != 0)
		eSSParams->n_refSet++;
	eSSParams->n_refSet = MAX(eSSParams->n_refSet, 20);

	eSSParams->n_subRegions = MIN(4, eSSParams->n_Params);

	eSSParams->n_scatterSet = MAX(10 * eSSParams->n_Params, 40);

	eSSParams->n_childsSet = eSSParams->n_refSet;

	eSSParams->n_candidateSet = eSSParams->n_refSet -1 ;

	// eSSParams->init_RefSet_Type;
	// eSSParams->combination_Type;
	// eSSParams->regeneration_Type;
	// eSSParams->int delete;
	// eSSParams->intensification_Freqs;
	// eSSParams->diversification_Type;
	// eSSParams->cost_Tol;
	// eSSParams->dist_Tol;
	// eSSParams->param_Tol;
	// eSSParams->stuck_Tol;

	/**
	 * Local Search Options
	 */
	// eSSParams->perform_LocalSearch;
	eSSParams->local_method = 'l';
	// eSSParams->local_Freqs;
	// eSSParams->local_SolverMethod;
	// eSSParams->local_Tol;
	// eSSParams->local_IterPrint;
	// eSSParams->local_N1;
	// eSSParams->local_N2;
	// eSSParams->local_Balance;
	// eSSParams->local_atEnd;
	// eSSParams->local_onBest_Only;
	// eSSParams->local_merit_Filter;
	// eSSParams->local_distance_Filter;
	// eSSParams->local_th_merit_Factor;
	// eSSParams->local_max_distance_Factor;
	// eSSParams->local_wait_maxDist_limit;
	// eSSParams->local_wait_th_limit;

}

/**
 * This will call the problem simulator to the cost function for the individual.
 * The function should first copy ind->params to the inp->params and call the 
 * simulator like `simulator(inp, out)`, and finally write the `out` to `ind->cost`
 */
double objectiveFunction(eSSType *eSSParams, individual *ind, void *inp, void *out){

	double cost    = 0;
	double penalty = 0;

	#ifdef GSL_TESTFUNCTION
		gsl_vector *ff = gsl_vector_alloc(40);
		gsl_vector_view x = gsl_vector_view_array(ind->params, 3);
		objfn(&x.vector, inp, ff);
		// for (int i = 0; i < 40; ++i)
		// {
		// 	printf("%lf, ", gsl_vector_get(ff, i));
		// }
		cost = gsl_blas_dnrm2(ff);
		// printf("%g\n", cost);
		gsl_vector_free(ff);
		return cost;
	#else
		cost = objfn(ind->params);
	#endif

	return (cost + penalty);
}


// int gsl_objectiveFunction(const gsl_vector *x, void *data, gsl_vector *f){

// 	double cost = 0;
// 	double penalty = 0;


// 	// Copy x to a new double variable;
// 	// and call the objfn(d)

// 	return GSL_SUCCESS;
// }





