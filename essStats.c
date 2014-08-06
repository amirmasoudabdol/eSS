#include "ess.h"


void updateFrequencyMatrix(eSSType *eSSParams){

    for (int k = 0; k < eSSParams->refSet->size; ++k)
    {
        for (int i = 0; i < eSSParams->n_params; ++i)
        {
            for (int j = 0; j < eSSParams->n_sub_regions; ++j)
            {
                if (eSSParams->refSet->members[k].params[i] > eSSParams->min_boundary_matrix[i][j] && eSSParams->refSet->members[k].params[i] < eSSParams->max_boundary_matrix[i][j])
                {
                    eSSParams->stats->freqs_matrix[i][j]++;
                    break;
                }
            }
        }
    }
	
}

/**
 * Compute the statistics of the set like the mean and standard deviation of Individuals cost.
 * @param eSSParams 
 * @param set       
 */
void compute_SetStats(eSSType *eSSParams, Set *set ){

    // souble n = 0
    double Sum = 0;
    double Sum_sqr = 0;
 
    for (int i = 0; i < set->size; ++i)
    {
        // n = n + 1
        Sum = Sum + set->members[i].cost ; 
        Sum_sqr = Sum_sqr + set->members[i].cost*set->members[i].cost ; 
    }
 
    double variance = (Sum_sqr - (Sum*Sum)/set->size)/(set->size - 1);

    set->mean_cost = Sum / set->size;
    set->std_cost =  sqrt(variance);
}

void compute_Mean(eSSType *eSSParams, Individual *ind){


}

void compute_Std(eSSType *eSSParams, Individual *ind){


}

void update_IndsStats(eSSType *eSSParams, Set *set){

	for (int i = 0; i < set->size; ++i){
		update_IndStats(eSSParams, &(set->members[i]));
	}
}

/**
 * Update or reset the statistics of an Individual consisting its mean and variance.
 * @param eSSParams 
 * @param ind       
 */
void update_IndStats(eSSType *eSSParams, Individual *ind){
	
	if (ind->n_not_randomized == 0){
		ind->mean_cost = 0;
		ind->var_cost = 0;
	}else{
    	double prev_mean = ind->mean_cost;
    	ind->n_not_randomized++;
	    ind->mean_cost = ind->mean_cost + (ind->cost - ind->mean_cost) / ind->n_not_randomized;
	    ind->var_cost = ind->var_cost + (ind->cost - ind->mean_cost)*(ind->cost - prev_mean);


	}
}
