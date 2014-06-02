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

	if (!eSSParams->warmStart)
	{
		init_scatterSet(eSSParams, inp, out);

		evaluate_Set(eSSParams, eSSParams->scatterSet, inp, out);

		init_refSet(eSSParams, inp, out);

		quickSort_Set(eSSParams, eSSParams->refSet, 0, eSSParams->refSet->size - 1, 'c');

		write_Set(eSSParams, eSSParams->refSet, refSet_history_file, 0);

		eSSParams->best = &(eSSParams->refSet->members[0]);

		print_Set(eSSParams, eSSParams->refSet);

		write_Ind(eSSParams, eSSParams->best, best_sols_history_file, 0);
	}else{
		init_warmStart(eSSParams);
	}


}


/**
 * Main optimization loop
 * @param essProblem Contains all the variables needed by eSS
 * @param inp        Objective function `inp` struct
 * @param out        Objective function `out` struct
 */
void run_eSS(eSSType *eSSParams, void *inp, void *out){


	int label[eSSParams->n_refSet];
	
	int candidate_index;

	for (int iter = 0; iter < eSSParams->maxiter; ++iter)
	{
		for (int i = 0; i < eSSParams->n_refSet; ++i)
		{
			// This will generate a new recombinedSet around the refSet[i] and put it into the recombinedSet
			// IMP: It could also send the best one only!
			candidate_index = recombine(eSSParams, &(eSSParams->refSet->members[i]), i, inp, out);

			if (-1 != candidate_index){
				
				eSSParams->stats->n_successful_recombination++;

				label[i] = 1;
				copy_Ind(eSSParams, &(eSSParams->childsSet->members[i]), &(eSSParams->candidateSet->members[candidate_index]));

				goBeyond(eSSParams, i, inp, out);

				if ( (eSSParams->perform_LocalSearch && !eSSParams->local_onBest_Only) 
					 && ( (iter > eSSParams->local_N1) || ( iter % eSSParams->local_N2 ) ) )
				{
					if (eSSParams->childsSet->members[i].cost < eSSParams->local_min_criteria ){
						if (eSSParams->local_method == 'n'){
							neldermead_localSearch(eSSParams, &(eSSParams->childsSet->members[i]), inp, out);
							eSSParams->stats->n_local_search_performed++;
						}else if (eSSParams->local_method == 'l'){
							levmer_localSearch(eSSParams, &(eSSParams->childsSet->members[i]), inp, out);
							eSSParams->stats->n_local_search_performed++;
						}
					}
				}
			}

		}


		for (int i = 0; i < eSSParams->n_refSet; ++i)
		{
			if (label[i] == 1){
				copy_Ind(eSSParams, &(eSSParams->refSet->members[i]), &(eSSParams->childsSet->members[i]));
				eSSParams->refSet->members[i].nStuck = 0;
				label[i] = 0;
			}else{
				eSSParams->refSet->members[i].nStuck++;
				if (eSSParams->refSet->members[i].nStuck > eSSParams->maxStuck ){
					random_Ind(eSSParams, &(eSSParams->refSet->members[i]), 
										eSSParams->min_real_var, eSSParams->max_real_var);

					evaluate_Individual(eSSParams, &(eSSParams->refSet->members[i]), inp, out);

					eSSParams->stats->n_Stuck++;
				}
			}
		}
		
		quickSort_Set(eSSParams, eSSParams->refSet, 0, eSSParams->n_refSet - 1, 'c');

		if (eSSParams->perform_LocalSearch && eSSParams->local_onBest_Only)
		{
			neldermead_localSearch(eSSParams, eSSParams->best, inp, out);
			eSSParams->stats->n_local_search_performed++;
		}

		if (iter % eSSParams->inter_save == 0){
			write_Set(eSSParams, eSSParams->refSet, refSet_history_file, iter);
			write_Ind(eSSParams, eSSParams->best, best_sols_history_file, iter);
		}

		if ( fabs( eSSParams->refSet->members[0].cost - fabs(eSSParams->refSet->members[eSSParams->n_refSet - 1].cost)) < 0.0001 ){
			printf("converged after %d iteration!\n", iter);
			break;
		}

	}

	printf("Final refSet: \n");
	print_Set(eSSParams, eSSParams->refSet);

	printf("bestSol: \n");
	print_Ind(eSSParams, eSSParams->best);
	print_Stats(eSSParams);

	if (eSSParams->perform_LocalSearch && eSSParams->local_atEnd && !eSSParams->local_onBest_Only)
	{
		printf("Perforimg the last local search\n");
		neldermead_localSearch(eSSParams, eSSParams->best, inp, out);
		printf("Final Result: \n");
		print_Ind(eSSParams, eSSParams->best);
	}

	refSet_final_file     = fopen("ref_set_final.csv", "w");
	write_Set(eSSParams, eSSParams->refSet, refSet_final_file, -1);
	write_Ind(eSSParams, eSSParams->best, best_sols_history_file, eSSParams->maxiter);	

#ifdef GSL_TESTFUNCTION
	#ifdef LEVMER
		levmer_localSearch(eSSParams, eSSParams->best, inp, out);
	#elif defined NELDER
		neldermead_localSearch(eSSParams, eSSParams->best, inp, out);
	#endif
#endif
	
	// printf("%f\n", );
}








