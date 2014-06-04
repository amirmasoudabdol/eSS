#include "ess.h"
// #include <string.h>
/**
 * Copy `src` to `dest` using `memcpy`
 */
void copy_Ind(eSSType *eSSParams, individual *dest, individual *src){
	
	memcpy(dest->params, src->params, eSSParams->n_Params*sizeof(double));
	// memcpy(dest->means, src->means, eSSParams->n_Params*sizeof(double));
	// memcpy(dest->stds, src->stds, eSSParams->n_Params*sizeof(double));
	dest->mean_cost   = src->mean_cost;
	dest->var_cost    = src->var_cost;
	dest->cost   = src->cost;
	dest->dist   = src->dist;
	dest->nStuck = src->nStuck;
}


/**
 * Return the min and min_index of an array
 */
double min(double* array, int len, int* min_index){

    double min = array[0];
    for (int i = 1; i < len; ++i) {
        if (min > array[i]) {
            min = array[i];
            *min_index = i;
        }
    }

    return min;
}

/**
 * Return the max and max_index of an array
 */
double max(double* array, int len, int* max_index){

    double max = array[0];
    for (int i = 1; i < len; ++i) {
        if (max < array[i]) {
            max = array[i];
            *max_index = i;
        }
    }

    return max;

}

double euclidean_distance(eSSType *eSSParams, individual *ind1, individual *ind2){

	double distance = 0;
	for (int i = 0; i < eSSParams->n_Params; ++i)
	{
		distance += (ind1->params[i] - ind2->params[i]) * (ind1->params[i] - ind2->params[i]);
	}
	return sqrt(distance);

}

void delete_and_shift(eSSType *eSSParams, Set *set, int set_size, int index_to_delete){

	for (int i = index_to_delete; i < set_size - 1; ++i)
	{
		copy_Ind(eSSParams, &(set->members[i]), &(set->members[i + 1]));
	}

}