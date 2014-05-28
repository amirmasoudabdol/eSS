#include "ess.h"

double rndreal(double low, double high){

    return (low + (high-low) * ((double)rand() / RAND_MAX) );	
}


void random_Set(eSSType *eSSParams, Set *set, double low, double high){
	for (int i = 0; i < set->size; ++i)
	{
		random_Ind(eSSParams, &(set->members[i]), low, high);
	}
}

void random_Ind(eSSType *eSSParams, individual *ind, double low, double high){

	for (int i = 0; i < eSSParams->n_Params; ++i)
	{
		ind->params[i] = rndreal(eSSParams->min_real_var[i], eSSParams->max_real_var[i]);
	}
}