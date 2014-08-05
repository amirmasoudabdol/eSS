#include "ess.h"

/**
 * Recombined `ind` with `ind_index` in the refSet with all the other members of refSet
 * and return the index of the best recombined solution that outperform its parent.
 * `-1` means there was not such a solution exist.
 * @param  eSSParams 
 * @param  ind       parent individual
 * @param  ind_index index of the parent individual
 * @param  bestInd   
 * @param  inp       
 * @param  out       
 * @return           index of the best candidate that outperform its parent.
 */
int recombine(eSSType *eSSParams, individual *ind, int ind_index,/* individual *bestInd,*/
					 void *inp, void *out){

	double c1;
	double c2;
	double d;
	double alpha, beta;

	int p = 0;
	int best_index = -1;
	for (int j = 0; j < eSSParams->n_refSet; ++j)
	{
		if ( j != ind_index ){

			alpha = ( ind_index < j ) ? 1 : -1;
			beta = abs(j - ind_index);

			for (int k = 0; k < eSSParams->n_Params; ++k)
			{
				d = eSSParams->refSet->members[j].params[k] - eSSParams->refSet->members[ind_index].params[k];
				c1 = eSSParams->refSet->members[ind_index].params[k] - d * ( 1 + alpha * beta);
				c2 = eSSParams->refSet->members[ind_index].params[k] + d * ( 1 + alpha * beta);
				
				c1 = MAX(eSSParams->min_real_var[k], c1); c1 = MIN(eSSParams->max_real_var[k], c1);
				c2 = MAX(eSSParams->min_real_var[k], c2); c2 = MIN(eSSParams->max_real_var[k], c2);

				eSSParams->candidateSet->members[p].params[k] = c1 + (c2 - c1) * rndreal(0, 1);
			}

			evaluate_Individual(eSSParams, &(eSSParams->candidateSet->members[p]), inp, out);
			eSSParams->candidateSet->members[p].dist   = 0;
			eSSParams->candidateSet->members[p].mean_cost   = 0;
			eSSParams->candidateSet->members[p].var_cost    = 0;
			eSSParams->candidateSet->members[p].nStuck = 0;

			if ( eSSParams->candidateSet->members[p].cost < eSSParams->refSet->members[ind_index].cost )
				best_index = p;
			
			p++;
		}
	}

	return best_index;

}