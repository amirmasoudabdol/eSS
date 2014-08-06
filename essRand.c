#include "ess.h"

double rndreal(double low, double high){

    return (low + (high-low) * ((double)rand() / RAND_MAX) );	
}


void random_Set(eSSType *eSSParams, Set *set, double *low, double *high){
	for (int i = 0; i < set->size; ++i)
	{
		random_Ind(eSSParams, &(set->members[i]), low, high);
	}
}

void random_Ind(eSSType *eSSParams, Individual *ind, double *low, double *high){

	for (int i = 0; i < eSSParams->n_Params; ++i){
		if (!eSSParams->logBound)
			ind->params[i] = rndreal(low[i], high[i]);
		else{
			// TODO: Still very buggy!
			double mx, mn, la;
			mn = low[i];
			mx = high[i];
			la = log10(mx) - log10(MIN(mn, -RAND_MAX));

          // determine if linear or log scale
          if ((mn < 0.0) || (mx <= 0.0))
            ind->params[i] = mn + rndreal(0,1) * (mx - mn);
          else
            {
              if (la < 1.8)
                ind->params[i] = mn + rndreal(0, 1) * (mx - mn);
              else
                ind->params[i] = pow(10.0, log10(mn)) + la * rndreal(0, 1);
            }
		}

		ind->n_not_randomized = 0;
	}
}