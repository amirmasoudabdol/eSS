#include "ess.h"

/**
 * Allocate memory for an Individual
 */
void allocate_Ind(eSSType *eSSParams, Individual *ind){

	ind->params = (double *)malloc(eSSParams->n_params * sizeof(double));
	// ind->params_means  = (double *)malloc(eSSParams->n_params * sizeof(double));
	// ind->params_vars   = (double *)malloc(eSSParams->n_params * sizeof(double));
	ind->mean_cost   = 0;
	ind->var_cost    = 0;
	ind->cost   = 0;
	ind->dist   = 0;

	ind->n_not_randomized = 0;
	ind->n_stuck = 0;
}

/**
 * Deallocate memory for an Individual
 */
void deallocate_Ind(eSSType *eSSParams, Individual *ind){

	free(ind->params);
	// free(ind->means);
	// free(ind->stds);
}


/**
 * Allocate memory of a set
 */
void allocate_Set(eSSType *eSSParams, Set *set){

	set->members = (Individual *)malloc(set->size * sizeof(Individual));
	for (int i = 0; i < set->size; ++i)
		allocate_Ind(eSSParams, &(set->members[i]));

	set->params_means = (double *)malloc(eSSParams->n_params * sizeof(double));
}

/**
 * Deallocate memory of a set
 */
void deallocate_Set(eSSType *eSSParams, Set *set){

	for (int i = 0; i < set->size; ++i)
		deallocate_Ind(eSSParams, &(set->members[i]));

	free(set->members);
	free(set->params_means);
}


void deallocate_eSSParams(eSSType *eSSParams){

	deallocate_Set(eSSParams, eSSParams->refSet);
	free(eSSParams->refSet);

	deallocate_Set(eSSParams, eSSParams->scatterSet);
	free(eSSParams->scatterSet);

	deallocate_Set(eSSParams, eSSParams->childsSet);
	free(eSSParams->childsSet);

	deallocate_Set(eSSParams, eSSParams->candidateSet);
	free(eSSParams->candidateSet);

	eSSParams->archiveSet->size = 100;
	deallocate_Set(eSSParams, eSSParams->archiveSet);
	free(eSSParams->archiveSet);

	deallocate_Set(eSSParams, eSSParams->localSearchCandidateSet);
	free(eSSParams->localSearchCandidateSet);

	free(eSSParams->min_real_var);
	free(eSSParams->max_real_var);

	/**
	 * Deallocating the stats struct
	 */
	for (int i = 0; i < eSSParams->n_params; ++i)
	{
		free(eSSParams->stats->freqs_matrix[i]);
		free(eSSParams->stats->probs_matrix[i]);

		// Deallocation min/max_boundary_matrices
		free(eSSParams->min_boundary_matrix[i]);
		free(eSSParams->max_boundary_matrix[i]);
	}
	free(eSSParams->min_boundary_matrix);
	free(eSSParams->max_boundary_matrix);

	free(eSSParams->stats->freqs_matrix);
	free(eSSParams->stats->probs_matrix);
	free(eSSParams->stats);
}







