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
FILE *archive_set_file;

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

		// print_Set(eSSParams, eSSParams->refSet);

}


/**
 * Main optimization loop
 * @param essProblem Contains all the variables needed by eSS
 * @param inp        Objective function `inp` struct
 * @param out        Objective function `out` struct
 */
void run_eSS(eSSType *eSSParams, void *inp, void *out){


	int label[eSSParams->n_refSet];				/*<! Uses to store the index of individuals that should be replaced with their children. */
	memset(label, 0, eSSParams->n_refSet * sizeof(int));
	
	int candidate_index;						/*<! Store the index of candidate for replacement after recombination. */
	int n_currentUpdated;						/*<! Counter for all updated solutions either from recombination or goBeyond procedure. */
	int archive_index = 0;						/*<! Track the index of `archiveSet` for storing the best solutions found. */				



	/**
	 * It sets to 0 at first, and then increments until it hits the 100. Because we don't wanted
	 * to spend time and checking archive members that are not already assigned!
	 */
	eSSParams->archiveSet->size = 0;

	for (eSSParams->iter = 1; eSSParams->iter < eSSParams->maxiter; ++eSSParams->iter)
	{
		n_currentUpdated = 0;
		// int i_lCandidate = 0;
		for (int i = 0; i < eSSParams->n_refSet; ++i)
		{
			/**
			 * Generate a candidate set by combining the `i`th member of the refSet and returning
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
				 * TODO: Implement the local search selection routine as described in the paper
				 */
				// copy_Ind(eSSParams, &(eSSParams->localSearchCandidateSet->members[i_lCandidate]), &(eSSParams->childsSet->members[i]));
				// i_lCandidate++;
				// eSSParams->localSearchCandidateSet->size = i_lCandidate;

				/**
				 * Check if the local search is activated and it is not activated only for best
				 * sol, if so, then check if it's a right moment to run the local search based on
				 * n1, and n2 values.
				 * Note that the local search won't apply here if it meant to apply only on best
				 * sol.
				 */
				if ( (eSSParams->perform_LocalSearch && !eSSParams->local_onBest_Only) 
					 && ( (eSSParams->iter > eSSParams->local_N1) || ( eSSParams->iter % eSSParams->local_N2 == 0 ) ) )
					{
						/**
						 * This check will prevent the local search operation if the cost of the individual
						 * is greater than some value.
						 */
						if (eSSParams->childsSet->members[i].cost < eSSParams->local_min_criteria ){
							/**
							 * Check if the selected child is close to the area that already the 
							 * local search applied on it or not
							 */
							///////////////////////////////////////
							///		  Flatzone Detection 	///
							///////////////////////////////////////	
							if (eSSParams->perform_flatzone_check){
								if ( !is_in_flatzone(eSSParams, eSSParams->refSet, &(eSSParams->childsSet->members[i])) ){
									goto local_search;

									local_search:
										if ( -1 == is_exist(eSSParams, eSSParams->archiveSet, &(eSSParams->childsSet->members[i])) )
										 {
											if (eSSParams->local_method == 'n'){
												neldermead_localSearch(eSSParams, &(eSSParams->childsSet->members[i]), inp, out);
												eSSParams->stats->n_local_search_performed++;
											}else if (eSSParams->local_method == 'l'){
												levmer_localSearch(eSSParams, &(eSSParams->childsSet->members[i]), inp, out);
												eSSParams->stats->n_local_search_performed++;
											}
										}else{
											eSSParams->stats->n_duplicate_found++;
										}
								}
							}else
								goto local_search;
						}
					}
			}

		}

		/**
		 * Update the refSet individual based on the indexes flagged in `label`, if the nStuck is
		 * greater than the maxStuck then the individual will add to the archiveSet and then randomizes and n_notRandomized and all it's statistics will set to zero.
		 */
		for (int i = 0; i < eSSParams->n_refSet; ++i)
		{
			/**
			 * If an individual marked, it will replace by its improved child
			 */
			if (label[i] == 1){
				/**
				 * Check if the candidate is very close to a member of a refSet, if so, then randomize the 
				 * duplicated members in refSet.
				 */
				int duplicate_index = is_exist(eSSParams, eSSParams->refSet, &(eSSParams->childsSet->members[i]));
				if ((duplicate_index != -1) && (duplicate_index != i) && (duplicate_index != 0)){
					eSSParams->stats->n_duplicate_found++;
					// TODO: I can do this better by picking a random value based on the frequency matrix; then I can promote areas that are not discovered enough yet.
					random_Ind(eSSParams, &(eSSParams->refSet->members[duplicate_index]), eSSParams->min_real_var, eSSParams->max_real_var);
					evaluate_Individual(eSSParams, &(eSSParams->refSet->members[duplicate_index]), inp, out);
				}

				/**
				 * Replace the parent with its better child! If it does pass the flatzone_detection_test
				 */
				if (eSSParams->perform_flatzone_check){
					if (!is_in_flatzone(eSSParams, eSSParams->refSet, &(eSSParams->childsSet->members[i])))
					{
						goto replace;

						replace:
							eSSParams->refSet->members[i].n_notRandomized++;
							copy_Ind(eSSParams, &(eSSParams->refSet->members[i]), &(eSSParams->childsSet->members[i]));
							eSSParams->refSet->members[i].nStuck = 0;
					}
				}else
					goto replace;

				label[i] = 0;
			}else{
				/**
				 * Otherwise, the individual randomzies and all of it's stats and counters set
				 * to 0.
				 */
				eSSParams->refSet->members[i].nStuck++;
				if (eSSParams->refSet->members[i].nStuck > eSSParams->maxStuck
						&& (eSSParams->iter % eSSParams->n_randomization_Freqs == 0 )
							&& (i > 3) ){	// I decided to keep 3 best sols in the refSet.

					/* Add the stuck individual to the archiveSet */
					if (archive_index == eSSParams->n_archiveSet)
						archive_index = 0;

					if ((archive_index < eSSParams->n_archiveSet) 
							&& (eSSParams->archiveSet->size < eSSParams->n_archiveSet))
						eSSParams->archiveSet->size++;
					
					copy_Ind(eSSParams, &(eSSParams->archiveSet->members[archive_index]), &(eSSParams->refSet->members[i]));
					archive_index++;

					/**
					 * Randomize the stuck refSet member.
					 */
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
		 * The last condition avoid performing local search on solutions that are stuck, since
		 * the local search algorithm couldn't keep the parameters in boundary so, we have to stop
		 * over-applying it on solutions before make them really far from defined box constratins.
		 */
		if (eSSParams->perform_LocalSearch 
				&& eSSParams->local_onBest_Only 
					&& (eSSParams->best->cost < eSSParams->local_min_criteria)
						&& eSSParams->best->nStuck < eSSParams->maxStuck)		
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

			/**
			 * Check if the standard deviation of the set is small and the number of 
			 * updatedMembers is less than 1/4 of the n_refSet then randomize the refSet.
			 * After randomization all the n_notRandomized values of refSet individual will
			 * set to 0.
			 */
			if (eSSParams->perform_refSet_randomization && 
					eSSParams->refSet->std_cost < eSSParams->set_std_Tol && n_currentUpdated < (eSSParams->n_refSet / 4)){
				/**
				 * Replace the last n_delete members of the refSet with the newly 
				 * randomized solutions in and sort the refSet at the end of the replacement.
				 */
				for (int i = eSSParams->refSet->size - 1; i > eSSParams->refSet->size - eSSParams->n_delete; --i)
				{
					random_Ind(eSSParams, &(eSSParams->refSet->members[i]), eSSParams->min_real_var, eSSParams->max_real_var);
					evaluate_Individual(eSSParams, &(eSSParams->refSet->members[i]), inp, out);
				}
				quickSort_Set(eSSParams, eSSParams->refSet, 0, eSSParams->refSet->size - 1, 'c');
				eSSParams->stats->n_refSet_randomized++;
			}
			
			update_SetStats(eSSParams, eSSParams->refSet);
		}	


		if (eSSParams->iter % eSSParams->iterprint == 0){
			print_Stats(eSSParams);
		}


		write_Stats(eSSParams, stats_file);
	}

	printf("Final refSet: \n");
	print_Set(eSSParams, eSSParams->refSet);

	printf("bestSol: \n");
	print_Ind(eSSParams, eSSParams->best);
	print_Stats(eSSParams);

	/**
	 * Performing the local search on the bestSol.
	 */
	if (eSSParams->perform_LocalSearch && eSSParams->local_atEnd && !eSSParams->local_onBest_Only)
	{
		printf("Perforimg the last local search\n");
		if (eSSParams->local_method == 'n')
			neldermead_localSearch(eSSParams, eSSParams->best, inp, out);
		else
			levmer_localSearch(eSSParams, eSSParams->best, inp, out);
	
		printf("Final Result: \n");
		print_Ind(eSSParams, eSSParams->best);
	}

	refSet_final_file     = fopen("ref_set_final.csv", "w");
	write_Set(eSSParams, eSSParams->refSet, refSet_final_file, -1);
	write_Set(eSSParams, eSSParams->archiveSet, archive_set_file, -1);
	write_Ind(eSSParams, eSSParams->best, best_sols_history_file, eSSParams->maxiter);	
	printf("ref_set_final.csv, ref_set_history_file.out, best_sols_history_file.out, and stats_file is generated. \n");


	fclose(refSet_final_file);
	fclose(best_sols_history_file);
	fclose(stats_file);
	// fclose(file)



}








