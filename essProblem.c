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
// #include "benchmarks/LM2n5.h"				// Accurate!
// #include "benchmarks/LM2n10.h"			// Accurate!
// #include "benchmarks/MeyerRoth.h"			// Accurate!
// #include "benchmarks/MieleCantrell.h"		// Accurate!
#include "benchmarks/ModRosenbrock.h"		// Accurate!
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
// #include "benchmarks/Shekel7.h"			// Accurate! More iterations needed
// #include "benchmarks/Shekelfox10.h"		// NOT Accurate!
// #include "benchmarks/Shekelfox5.h"		// Accurate! More Iteration needed
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
// #include "benchmarks/Rastrigin.h"			// Accurate!		// I got it with performing warm start in a good solutions set
// #include "benchmarks/Modlangerman.h"		// Not accurate! Stuck!
// #include "benchmarks/Oddsquare.h"			// Not accurate! Stuck!
// 

// #include "benchmarks/expb.h"				// Accurate


/**
 * Initialize the sample parameters for optimization
 */
void init_sampleParams(eSSType *eSSParams){


#ifdef TEST_PROBLEM
	eSSParams->n_Params = N;
	eSSParams->sol = (double)SOL;
	printf("%s", KCYN);
	printf("\n---------------------------------");
	printf("\n %s:", (const char*)TEST_PROBLEM);
	printf("\n Analytic Solution: %lf \n", (double)SOL);
	printf("---------------------------------\n\n");
	printf("%s", KNRM);
#endif

	/**
	 * User Options
	 */
	eSSParams->logBound = 0;
	// eSSParams->maxeval;
	// eSSParams->maxtime;
	eSSParams->iterprint = 500;
	// eSSParams->plot;
	// eSSParams->weight;
	// eSSParams->tolc;
	// eSSParams->prob_bound;
	// eSSParams->strategy;
	eSSParams->inter_save = 1;
	// eSSParams->perform_warm_start = 0;
	eSSParams->perform_refSet_randomization = 1;
	eSSParams->n_randomization_Freqs = 1;

	eSSParams->goBeyond_freqs = 10;

	eSSParams->n_archiveSet = 100;

	eSSParams->set_std_Tol = 1e-3;

	eSSParams->equality_type = 1;
	// eSSParams->init_with_user_guesses = 1;

	/**
	 * Global Options
	 */
	// eSSParams->n_Params = 2;

	if (eSSParams->maxiter == 0)
		eSSParams->maxiter = 200;
	
	eSSParams->max_stuck = 20;

	eSSParams->perform_flatzone_check = 0;
	eSSParams->flatzone_Tol = 0.0001; 

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

	eSSParams->n_sub_regions = MIN(4, eSSParams->n_Params);

	eSSParams->n_scatterSet = MAX(10 * eSSParams->n_Params, 40);

	eSSParams->n_childsSet = eSSParams->n_refSet;

	eSSParams->n_candidateSet = eSSParams->n_refSet -1 ;

	// eSSParams->init_RefSet_Type;
	// eSSParams->combination_Type;
	// eSSParams->regeneration_Type;
	eSSParams->n_delete = eSSParams->n_refSet / 4;
	// eSSParams->intensification_Freqs;
	// eSSParams->diversification_Type;
	eSSParams->perform_cost_tol_stopping = 0;
	eSSParams->cost_Tol = 1e-3;
	eSSParams->dist_Tol= 1e-3;
	eSSParams->param_Tol = 5e-4;
	// eSSParams->stuck_Tol;
	eSSParams->perform_refSet_convergence_stopping = 0;
	eSSParams->refSet_convergence_Tol = 1e-4;

	/**
	 * Local Search Options
	 */
	// eSSParams->perform_LocalSearch = 1;
	if (eSSParams->local_SolverMethod == '0') eSSParams->local_SolverMethod = 'n';
	// eSSParams->local_minCostCriteria = ((double)SOL + 1) ;
	eSSParams->local_minCostCriteria = 30 ;
	eSSParams->local_maxIter = 500; 
	// eSSParams->local_Freqs;
	// eSSParams->local_SolverMethod;
	eSSParams->local_Tol = 1e-3;
	// eSSParams->local_IterPrint;
	eSSParams->local_N1 = 50;
	eSSParams->local_N2 = 25;
	// eSSParams->local_Balance;
	eSSParams->local_atEnd = 1;
	eSSParams->local_onBest_Only = 0;
	// eSSParams->local_merit_Filter;
	// eSSParams->local_distance_Filter;
	// eSSParams->local_th_merit_Factor;
	// eSSParams->local_max_distance_Factor;
	// eSSParams->local_wait_maxDist_limit;
	// eSSParams->local_wait_th_limit;

	eSSParams->compute_Ind_Stats = 1;
	eSSParams->compute_Set_Stats = 1;

}

/**
 * This will call the problem simulator to the cost function for the Individual.
 * The function should first copy ind->params to the inp->params and call the 
 * simulator like `simulator(inp, out)`, and finally write the `out` to `ind->cost`
 */
double objectiveFunction(eSSType *eSSParams, Individual *ind, void *inp, void *out){

	double cost    = 0;
	double penalty = 0;

	// #ifdef GSL_TESTFUNCTION
	// 	#ifdef LEVMER
	if (eSSParams->perform_LocalSearch){
		if (eSSParams->local_SolverMethod == 'l'){
				gsl_vector *ff = gsl_vector_alloc(40);
				gsl_vector_view x = gsl_vector_view_array(ind->params, 3);
				levermed_objfn(&x.vector, inp, ff);
				cost = gsl_blas_dnrm2(ff);
				gsl_vector_free(ff);
				return cost;
			}
		if (eSSParams->local_SolverMethod == 'n'){
			// #elif defined NELDER
				gsl_vector_view x = gsl_vector_view_array(ind->params, 3);
				return nelder_objfn(&x.vector, inp);
		}
	}
	else{
	// 		return objfn(&x.vector, inp);
	// 	#endif
	// #else
		cost = objfn(ind->params);
	}

	return (cost + penalty);
}




