#include "ess.h"
#include <unistd.h>
#include <ctype.h>

void read_cli_params(eSSType *eSSParams, int argc, char **argv){

   // char *cvalue = NULL;
   // int index;
	int c;
	printf("Reading the command line paremters...\n");
	while ((c = getopt (argc, argv, "m:drwuslo:")) != -1)
		switch (c)
	{
	       case 'm':		// maxiter
	       eSSParams->maxiter = atoi(optarg);
	       break;
	       case 'd':
	       eSSParams->debug = 1;
	       break;
	       case 'u':
	       eSSParams->user_guesses = 1;
	       break;
	       case 'w':
	       eSSParams->warmStart = 1;
	       break;
	       case 's':
	       eSSParams->collectStats = 1;
	       break;
	       case 'r':
	       eSSParams->saveOutput = 1;
	       break;
	       case 'l':
	       eSSParams->perform_LocalSearch = 1;
	       break;
	       case 'o':
	       eSSParams->local_method = optarg[0];
	       break;
	       case '?':
	       break;
	       default:
	       abort ();
	   }

}

void print_Set(eSSType *eSSParams, Set *set){
	printf("-----------------------------------\n");
	for (int i = 0; i < set->size; ++i)
	{
		printf("% d: ", i); print_Ind(eSSParams, &(set->members[i]));
	}
	printf("\n");

}

void print_Ind(eSSType *eSSParams, individual *ind){

	for (int i = 0; i < eSSParams->n_Params; ++i)
	{
		printf("% 10.5lf, ", ind->params[i]);
	}	
	// printf("\t (cost: %lf)\t(dist: %lf)\n", ind->cost, ind->dist);
	printf("\t (cost: % lf) - %d\n", ind->cost, ind->nStuck);

}


void write_Set(eSSType *eSSParams, Set *set, FILE *fpt, int iter){

	for (int i = 0; i < set->size; ++i)
	{
		write_Ind(eSSParams, &(set->members[i]), fpt, iter);
	}
}

void write_Ind(eSSType *eSSParams, individual *ind, FILE *fpt, int iter){

	if (iter != -1)
		fprintf(fpt, "%d\t", iter);

	for (int i = 0; i < eSSParams->n_Params; ++i)
	{
		fprintf(fpt, "%.5lf\t", ind->params[i]);
	}
	
	fprintf(fpt, "%lf\n", ind->cost);
}


void print_Stats(eSSType *eSSParams){

	printf("%s\n", KGRN);
	printf("n_iter: %d\n", eSSParams->iter);
	printf("n_successful_goBeyond: %d\n", eSSParams->stats->n_successful_goBeyond);
	printf("n_local_search_performed: %d\n", eSSParams->stats->n_local_search_performed);
	printf("n_successful_localSearch: %d\n", eSSParams->stats->n_successful_localSearch);
	printf("n_local_search_iterations: %d \t (avg: %d)\n", eSSParams->stats->n_local_search_iterations, eSSParams->stats->n_local_search_iterations / (eSSParams->stats->n_successful_localSearch + 1));
	printf("n_refSet_randomized: %d\n", eSSParams->stats->n_refSet_randomized);
	printf("n_Stuck: %d\n", eSSParams->stats->n_Stuck);
	printf("n_successful_recombination: %d\n", eSSParams->stats->n_successful_recombination);
	if (eSSParams->compute_Set_Stats){
		printf("-------------------\n");
		printf("RefSet Mean Cost: %lf+/-%lf\n", eSSParams->refSet->mean_cost, eSSParams->refSet->std_cost);
	}
	printf("%s\n", KNRM);

}

void write_Stats(eSSType *eSSParams, FILE *fpt){

	fprintf(fpt, "%d\t", eSSParams->iter);
	fprintf(fpt, "%d\t", eSSParams->stats->n_successful_goBeyond);
	fprintf(fpt, "%d\t", eSSParams->stats->n_local_search_performed);
	fprintf(fpt, "%d\t", eSSParams->stats->n_successful_localSearch);
	fprintf(fpt, "%d\t", eSSParams->stats->n_local_search_iterations);
	fprintf(fpt, "%d\t", eSSParams->stats->n_Stuck);
	fprintf(fpt, "%d\t", eSSParams->stats->n_successful_recombination);
	fprintf(fpt, "%d\t", eSSParams->stats->n_flatzone_detected);
	fprintf(fpt, "\n");

}


void parse_double_row(eSSType *eSSParams, char *line, double *row){

    int i = 0;
    const char* tok;
    for (tok = strtok(line, "\t"); tok && *tok; i++, tok = strtok(NULL, "\t\n"))
    {
        row[i] = atof(tok);
    }
}


void parse_int_row(eSSType *eSSParams, char *line, int *row){

    int i = 0;
    const char* tok;
    for (tok = strtok(line, "\t"); tok && *tok; i++, tok = strtok(NULL, "\t\n"))
    {
        row[i] = atoi(tok);
    }
}

void print_Inputs(eSSType *eSSParams){
		printf("Maximum Iterations: % d\n", eSSParams->maxiter);
		printf("Debug: % d\n", eSSParams->debug);
		printf("Warm Start: % d\n", eSSParams->warmStart);
		printf("# of Sub Regions: % d\n", eSSParams->n_subRegions);
		printf("# of Parameters: % d\n", eSSParams->n_Params);
		printf("Reference Set Size: % d\n", eSSParams->n_refSet);
		printf("Candidate Set Size: % d\n", eSSParams->n_candidateSet);
		printf("Children Set Size: % d\n", eSSParams->n_childsSet);
		printf("Stuck Tolerance: % d\n", eSSParams->maxStuck);
		printf("Local Search Activated: %s\n", eSSParams->perform_LocalSearch == 1 ? "Yes" : "NO");
		printf("Local Search Method: %s\n", eSSParams->local_method == 'l' ? "Levenberg-Marquardt" : "Nelder-Mead");
		printf("Local Search Tolerance: %e\n", eSSParams->local_Tol);
		printf("Local Search Max Iters: %d\n", eSSParams->local_maxIter);
		printf("Local Search only on Best Sol: %s\n", eSSParams->local_onBest_Only == 1 ? "True" : "False");
		printf("\n");
}





