#include "ess.h"

/**
 * Request heap memory for all the variables needed based on their size.
 * So, the init_sampleParams should be called before.
 */
void init_essParams(eSSType *eSSParams){

	eSSParams->refSet = (Set*)malloc(sizeof(Set));
	eSSParams->refSet->size = eSSParams->n_RefSet;
	allocate_Set(eSSParams, eSSParams->refSet);

	eSSParams->diverseSet = (Set*)malloc(sizeof(Set));
	eSSParams->diverseSet->size = eSSParams->n_DiverseSet;
	allocate_Set(eSSParams, eSSParams->diverseSet);

	eSSParams->childsSet = (Set*)malloc(sizeof(Set));
	eSSParams->childsSet->size = eSSParams->n_childsSet;
	allocate_Set(eSSParams, eSSParams->childsSet);

	eSSParams->candidateSet = (Set*)malloc(sizeof(Set));
	eSSParams->candidateSet->size = eSSParams->n_candidateSet;
	allocate_Set(eSSParams, eSSParams->candidateSet);

}

void init_report_files(eSSType *eSSParams){
	char mode = 'w';
	if (eSSParams->is_warmStart)
		mode = 'a';
	ref_set_history_file   = fopen("ref_set_history_file.out", &mode);
	best_sols_history_file = fopen("best_sols_history_file.out", &mode);
	freqs_matrix_file      = fopen("freqs_matrix_history.out", &mode);
	stats_file			   = fopen("stats_file.csv", &mode);	
	// TODO: Check the mode
}


void init_stats(eSSType *eSSParams){

}

void init_scatterSet(eSSType *eSSParams, void* inp, void *out){

}

void init_refSet(eSSType *eSSParams, void* inp, void *out){


}
