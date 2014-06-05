#include "ess.h"



FILE *refSet_history_file;
FILE *best_sols_history_file;
FILE *freqs_matrix_file;
FILE *freq_mat_final_file;
FILE *prob_mat_final_file;
FILE *refSet_final_file;
FILE *stats_file;
FILE *ref_set_stats_history_file;
FILE *user_initial_guesses_file;

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

	print_Inputs(eSSParams);

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
		printf("Perform Warm Start...\n");

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

	int n_currentUpdated;

	int archive_index = 0;

	for (eSSParams->iter = 1; eSSParams->iter < eSSParams->maxiter; ++eSSParams->iter)
	{
		n_currentUpdated = 0;
		for (int i = 0; i < eSSParams->n_refSet; ++i)
		{
			/**
			 * Generate a candidate set by combining the `i` member of the refSet and returning
			 * the best candidate with respect to it's cost.
			 */
			candidate_index = recombine(eSSParams, &(eSSParams->refSet->members[i]), i, inp, out);

			if (-1 != candidate_index){
				
				eSSParams->stats->n_successful_recombination++;

				label[i] = 1;
				n_currentUpdated++;

				copy_Ind(eSSParams, &(eSSParams->childsSet->members[i]), &(eSSParams->candidateSet->members[candidate_index]));

				/**
				 * goBeyond for already selected candidate from recombinedSet which is copied to 
				 * the childsSet too. Note that the goBeyond function works with childsSet so it 
				 * need the `i` as a index not the `candidate_index`
				 */
				if (eSSParams->goBeyond_Freqs != 0 && (eSSParams->iter % eSSParams->goBeyond_Freqs == 0))
					goBeyond(eSSParams, i, inp, out);


				/**
				 * Check if the local search is activated and it is not activated only for best
				 * sol, if so, then check if it's a right moment to run the local search based on
				 * n1, and n2 values.
				 * Note that the local search won't apply here if it meant to apply only on best
				 * sol.
				 */
				if ( (eSSParams->perform_LocalSearch && !eSSParams->local_onBest_Only) 
					 && ( (eSSParams->iter > eSSParams->local_N1) || ( eSSParams->iter % eSSParams->local_N2 ) ) )
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


		/**
		 * Update the refSet individual based on the indexes flagged in `label`, if the nStuck is
		 * greater than the n_Stuck then the individual will add to the archiveSet and then randomizes and n_notRandomized and all it's statistics will set to zero.
		 */
		for (int i = 0; i < eSSParams->n_refSet; ++i)
		{
			if (label[i] == 1){
				eSSParams->refSet->members[i].n_notRandomized++;

				copy_Ind(eSSParams, &(eSSParams->refSet->members[i]), &(eSSParams->childsSet->members[i]));
				eSSParams->refSet->members[i].nStuck = 0;
				label[i] = 0;
			}else{
				eSSParams->refSet->members[i].nStuck++;
				if (eSSParams->refSet->members[i].nStuck > eSSParams->maxStuck ){
					/* Add the stuck individual to the archiveSet */

					if (archive_index == 100)
						archive_index = 0;

					copy_Ind(eSSParams, &(eSSParams->archiveSet->members[archive_index]), &(eSSParams->refSet->members[i]));
					archive_index++;

					random_Ind(eSSParams, &(eSSParams->refSet->members[i]), 
										eSSParams->min_real_var, eSSParams->max_real_var);

					evaluate_Individual(eSSParams, &(eSSParams->refSet->members[i]), inp, out);

					/* Store number of all the stuck parameters. */
					eSSParams->stats->n_Stuck++;
					eSSParams->refSet->members[i].n_notRandomized = 0;
					eSSParams->refSet->members[i].nStuck = 0;
					label[i] = 0;
				}
			}
		}
		
		quickSort_Set(eSSParams, eSSParams->refSet, 0, eSSParams->n_refSet - 1, 'c');

		/**
		 * Apply the local search on the best solution
		 */
		if (eSSParams->perform_LocalSearch && eSSParams->local_onBest_Only)
		{
			neldermead_localSearch(eSSParams, eSSParams->best, inp, out);
			eSSParams->stats->n_local_search_performed++;
		}

		if (eSSParams->iter % eSSParams->inter_save == 0){
			write_Set(eSSParams, eSSParams->refSet, refSet_history_file, eSSParams->iter);
			write_Ind(eSSParams, eSSParams->best, best_sols_history_file, eSSParams->iter);
		}

		/**
		 * Check if the best solution found is enough to the predicted solution. Usually this is
		 * not a good way to check the convergence of stochastic method but it the problem wasn't
		 * a multi-models problem then it saves a lot of unnecessary iterations.
		 */
		if (eSSParams->perform_cost_tol_stopping && 
			 	fabs( eSSParams->best->cost - eSSParams->sol ) < eSSParams->cost_Tol ){
			printf("%s\n", KRED);
			printf("Best Solutions converged after %d iterations\n", eSSParams->iter);
			printf("%s\n", KNRM);
			break;
		}

		/**
		 * Check the difference between the cost of best solution and worst solution in the 
		 * refSet. This might not always be the indication of the convergence but it might be 
		 * the indication of saturated referenceSet.
		 */
		if ( eSSParams->perform_refSet_convergence_stopping && 
				fabs( eSSParams->refSet->members[0].cost - fabs(eSSParams->refSet->members[eSSParams->n_refSet - 1].cost)) < eSSParams->refSet_convergence_Tol ){
			printf("Converged or Stuck after %d iteration!\n", eSSParams->iter);
			break;
		}

		/**
		 * Compute the mean and standard deviation of the set in order to decide if the 
		 * randomization should be applied or not.
		 */
		
		if (eSSParams->compute_Set_Stats){

			compute_SetStats(eSSParams, eSSParams->refSet);

			fprintf(ref_set_stats_history_file, "%lf\t%lf\n", eSSParams->refSet->mean_cost, eSSParams->refSet->std_cost);

			if (eSSParams->perform_refSet_randomization && 
					eSSParams->refSet->std_cost < 1e-3 && n_currentUpdated < (eSSParams->n_refSet / 4)){
				/**
				 * Check if the standard deviation of the set is small and the number of 
				 * updatedMembers is less than 1/4 of the n_refSet then randomize the refSet.
				 * After randomization all the n_notRandomized values of refSet individual will
				 * set to 0.
				 */
				for (int i = eSSParams->refSet->size - 1; i > eSSParams->refSet->size - eSSParams->n_delete; --i)
				{
					random_Ind(eSSParams, &(eSSParams->refSet->members[i]), eSSParams->min_real_var, eSSParams->max_real_var);
					evaluate_Individual(eSSParams, &(eSSParams->refSet->members[i]), inp, out);
				}
				quickSort_Set(eSSParams, eSSParams->refSet, 0, eSSParams->refSet->size - 1, 'c');
				printf("refSet Randomized\n");
			}
		}	

		update_SetStats(eSSParams, eSSParams->refSet);

		write_Stats(eSSParams, stats_file);
	}

	printf("Final refSet: \n");
	print_Set(eSSParams, eSSParams->refSet);

	printf("bestSol: \n");
	print_Ind(eSSParams, eSSParams->best);
	print_Stats(eSSParams);

	if (eSSParams->perform_LocalSearch && eSSParams->local_atEnd && !eSSParams->local_onBest_Only)
	{
		printf("Perforimg the last local search\n");
		if (eSSParams->local_method == 'l')
			neldermead_localSearch(eSSParams, eSSParams->best, inp, out);
		else
			levmer_localSearch(eSSParams, eSSParams->best, inp, out);
	
		printf("Final Result: \n");
		print_Ind(eSSParams, eSSParams->best);
	}

	refSet_final_file     = fopen("ref_set_final.csv", "w");
	write_Set(eSSParams, eSSParams->refSet, refSet_final_file, -1);
	write_Ind(eSSParams, eSSParams->best, best_sols_history_file, eSSParams->maxiter);	
	printf("ref_set_final.csv, ref_set_history_file.out, best_sols_history_file.out, and stats_file is generated. \n");


	fclose(refSet_final_file);
	fclose(best_sols_history_file);
	fclose(stats_file);
	// fclose(file)



}








