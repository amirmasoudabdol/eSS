#include "ess.h"
#include "benchmarks/GoldPrice.h"

/**
 * Initialize the sample parameters for optimization
 */
void init_sampleParams(eSSType *eSSParams){

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
	eSSParams->n_Params = 2;

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
	
	eSSParams->n_RefSet = ceil(1.0 + sqrt(1.0 + 40.0 * eSSParams->n_Params) / 2.0);
	if (eSSParams->n_RefSet %2 != 0)
		eSSParams->n_RefSet++;
	eSSParams->n_RefSet = MAX(eSSParams->n_RefSet, 20);

	eSSParams->n_subRegions = MIN(4, eSSParams->n_Params);

	eSSParams->n_scatterSet = MAX(10 * eSSParams->n_Params, 40);

	eSSParams->n_childsSet = eSSParams->n_RefSet - 1;

	eSSParams->n_candidateSet = eSSParams->n_RefSet * (eSSParams->n_RefSet - 1);

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

	cost = objfn(ind->params);

	return (cost + penalty);
}











