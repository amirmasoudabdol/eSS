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

/**
 * Find the closest memeber of a set to `ind` and return it's index
 * @param  eSSParams 
 * @param  set       Set to look for a closest member in it
 * @param  set_size  Size of the set, it can be smaller than the actuall set size
 * @param  ind       `individual` that we are interested in its closest member to it
 * @param  ind_index Index of the `ind` if it is already in the set.
 * @return           index of the closest member of a set to `ind`
 */
int closest_member(eSSType *eSSParams, Set *set, int set_size, individual *ind, int ind_index){
	double dist;
	double min;
	int min_index;

	if (ind_index == set_size - 1 ){
		min = euclidean_distance(eSSParams, ind, &(set->members[set_size - 2]));
		min_index = set_size - 2;
	}
	else if (ind_index == 0){
		min = euclidean_distance(eSSParams, ind, &(set->members[1]));
		min_index = 1;		
	}
	else{
		min = euclidean_distance(eSSParams, ind, &(set->members[ind_index - 1]));
		min_index = ind_index - 1;		
	}


	for (int i = 0; i < set_size; ++i)
	{
		if ( i != ind_index ){
			
			dist = euclidean_distance(eSSParams, ind, &(set->members[i]));
			if (dist < min ){
				min = dist;
				min_index = i;
			}
		}
	}
	return min_index;
}

bool is_equal_dist(eSSType *eSSParams, individual *ind1, individual *ind2){

	bool isEqual = false;
	if ( euclidean_distance(eSSParams, ind1, ind2) < eSSParams->dist_Tol )
		isEqual |= 1;	

	return isEqual;
}
	
bool is_equal_pairwise(eSSType *eSSParams, individual *ind1, individual *ind2){

	for (int i = 0; i < eSSParams->n_Params; ++i)
	{
		if (fabs(ind1->params[i] - ind2->params[i]) < eSSParams->param_Tol){
			return true;
		}
	}
	return false;
}

/*
	Check if the individual exist in the set
 */
int is_exist(eSSType *eSSParams, Set *set, individual *ind){

	int index = -1;
	for (int i = 0; i < set->size; ++i)
	{
		/**
		 * Check the value of eSSParams->equality_type, if its 0 then consider the euclidean_distance as a measurment
		 * otherwise, check the pairwise equality of parameters.
		 */
		if ( true == 
				(eSSParams->equality_type == 0 ? 
					is_equal_dist(eSSParams, &(set->members[i]), ind) : is_equal_pairwise(eSSParams, &(set->members[i]), ind)))
		{
			index = i;
			break;
		}

	}

	return index;
}

/**
 * Check to see if the individual is located in the flatzone or not! Is there any individual available in the set with similar cost.
 * @param  eSSParams 
 * @param  set       
 * @param  ind       
 * @return           `true` if the individual located in the flatzone
 */
bool is_in_flatzone(eSSType *eSSParams, Set *set, individual *ind){

	bool isInFlatzone = false;

	/**
	 * 	The loop doesn't check the last item since it is the best sol and 
	 * 	every good solution in comparison to that is in flatzone coverd by that!
	 */
	for (int i = 0; i < set->size; ++i)
	{
		if (ind->cost < set->members[i].cost + ( set->members[i].cost * eSSParams->flatzone_Tol) 
				&& ind->cost > set->members[i].cost - (set->members[i].cost * eSSParams->flatzone_Tol))
		{
			eSSParams->stats->n_flatzone_detected++;
			isInFlatzone = true;
			break;
		}

	}
	return isInFlatzone;
}