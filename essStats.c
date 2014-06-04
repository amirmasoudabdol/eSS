#include "ess.h"


void updateFrequencyMatrix(eSSType *eSSParams){

	
}


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

void compute_Mean(eSSType *eSSParams, individual *ind){


}

void compute_Std(eSSType *eSSParams, individual *ind){


}

void update_SetStats(eSSType *eSSParams, Set *set){

	for (int i = 0; i < set->size; ++i){
		update_IndStats(eSSParams, &(set->members[i]));
	}
}

void update_IndStats(eSSType *eSSParams, individual *ind){
	
	if (ind->n_notRandomized == 0){
		ind->mean_cost = 0;
		ind->var_cost = 0;
	}else{
    	double prev_mean = ind->mean_cost;
    	ind->n_notRandomized++;
	    ind->mean_cost = ind->mean_cost + (ind->cost - ind->mean_cost) / ind->n_notRandomized;
	    ind->var_cost = ind->var_cost + (ind->cost - ind->mean_cost)*(ind->cost - prev_mean);


	}
}
