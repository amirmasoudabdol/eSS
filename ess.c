#include "ess.h"



FILE *refSet_history_file;
FILE *best_sols_history_file;
FILE *freqs_matrix_file;
FILE *freq_mat_final_file;
FILE *prob_mat_final_file;
FILE *refSet_final_file;
FILE *stats_file;


/**
 * Initialize all the neccessary variable including the scatterSet and refSet formation.
 * @param eSSParams Contains all the variable needed by eSS
 * @param inp       (optional) Input struct containing the simulator input parameters
 * @param out       (optinoal) Output struct containing the simulator output parameters
 *                  `inp` and `out` use to send and recieve data to and from simulator (objective function)
 */
void init_eSS(eSSType *eSSParams, void *inp, void *out){
	
	init_sampleParams(eSSParams);

	init_essParams(eSSParams);

	init_report_files(eSSParams);

	init_scatterSet(eSSParams, inp, out);

	evaluate_Set(eSSParams, eSSParams->scatterSet, inp, out);

	print_Set(eSSParams, eSSParams->scatterSet);

	init_refSet(eSSParams, inp, out);

	quickSort_Set(eSSParams, eSSParams->refSet, 0, eSSParams->refSet->size - 1, 'c');	

	eSSParams->best = &(eSSParams->refSet->members[0]);

	print_Set(eSSParams, eSSParams->refSet);

	print_Ind(eSSParams, eSSParams->best);
}


/**
 * Main optimization loop
 * @param essProblem Contains all the variables needed by eSS
 * @param inp        Objective function `inp` struct
 * @param out        Objective function `out` struct
 */
void run_eSS(eSSType *essProblem, void *inp, void *out){


}