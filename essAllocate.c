#include "ess.h"

/**
 * Allocate memory for an individual
 */
void allocate_Ind(eSSType *eSSParams, individual *ind){

	ind->params = (double *)malloc(eSSParams->n_Params * sizeof(double));
	ind->means  = (double *)malloc(eSSParams->n_Params * sizeof(double));
	ind->stds   = (double *)malloc(eSSParams->n_Params * sizeof(double));
	ind->cost   = 0;
	ind->dist   = 0;
	
	ind->nStuck = 0;
}

/**
 * Deallocate memory for an individual
 */
void deallocate_Ind(eSSType *eSSParams, individual *ind){

	free(ind->params);
	free(ind->means);
	free(ind->stds);
}


/**
 * Allocate memory of a set
 */
void allocate_Set(eSSType *eSSParams, Set *set){

	set->members = (individual *)malloc(set->size * sizeof(individual));
	for (int i = 0; i < set->size; ++i)
	{
		allocate_Ind(eSSParams, &(set->members[i]));
	}
}

/**
 * Deallocate memory of a set
 */
void deallocate_Set(eSSType *eSSParams, Set *set){

	for (int i = 0; i < set->size; ++i)
	{
		deallocate_Ind(eSSParams, &(set->members[i]));
		free(&(set->members[i]));
	}
}


void deallocate_eSSParams(eSSType *eSSParams){

	deallocate_Set(eSSParams, eSSParams->refSet);
	free(eSSParams->refSet);

	deallocate_Set(eSSParams, eSSParams->diverseSet);
	free(eSSParams->diverseSet);

	deallocate_Set(eSSParams, eSSParams->childsSet);
	free(eSSParams->childsSet);

	deallocate_Set(eSSParams, eSSParams->candidateSet);
	free(eSSParams->candidateSet);

}