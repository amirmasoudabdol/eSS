#include "ess.h"



void goBeyond(eSSType *eSSParams, int parent_index,
						void *inp, void *out){

	bool improved;
	int gamma       = 1;
	int improvement = 1;

	// parent = eSSParams->refSet->members[parent_index];
	// child = eSSParams->childsSet->members[parent_index];
	individual parent;
	individual child;
	allocate_Ind(eSSParams, &parent);
	allocate_Ind(eSSParams, &child);
	copy_Ind(eSSParams, &parent, &(eSSParams->refSet->members[parent_index]));
	copy_Ind(eSSParams, &child, &(eSSParams->childsSet->members[parent_index]));

	double c1, c2;

	improved = false;
	for(;;) {

		for (int k = 0; k < eSSParams->n_Params; ++k){

			c1 = child.params[k] - (parent.params[k] - child.params[k]) / gamma;
			c2 = child.params[k];

			c1 = MAX(eSSParams->min_real_var[k], c1); c1 = MIN(eSSParams->max_real_var[k], c1);
			c2 = MAX(eSSParams->min_real_var[k], c2); c2 = MIN(eSSParams->max_real_var[k], c2);

			// Copying child to parent in time.
			parent.params[k] = child.params[k];
			child.params[k] = c1 + (c2 - c1) * rndreal(0, 1);
		}

		parent.cost = child.cost;

		evaluate_Individual(eSSParams, &child, inp, out);

		if ( child.cost < parent.cost )
		{
			// IMPROVE: Move the copy out of the for, so, there is only one
			// copy needed.
			copy_Ind(eSSParams, &(eSSParams->childsSet->members[parent_index]), &child);

			improved = true;
			improvement++;
			if ( 2 == improvement ){
				improvement = 0;
				gamma /= 2;
			}
			eSSParams->stats->n_successful_goBeyond++;
		}else{
			break;
		}

	}
	deallocate_Ind(eSSParams, &parent);
	deallocate_Ind(eSSParams, &child);

}