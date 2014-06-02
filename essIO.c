#include "ess.h"
#include <unistd.h>

void read_cli_params(eSSType *eSSParams, int argc, char **argv){

   // char *cvalue = NULL;
   // int index;
   int c;
   printf("hi\n");
	while ((c = getopt (argc, argv, "m:drwslo:")) != -1)
     switch (c)
       {
       case 'm':		// maxiter
         eSSParams->maxiter = atoi(optarg);
         printf("%d\n", eSSParams->maxiter);
         break;
       case 'd':
         eSSParams->debug = 1;
         printf("%d\n", eSSParams->debug);
         break;
       case 'w':
         eSSParams->warmStart = 1;
         printf("%d\n", eSSParams->warmStart);
         break;
       case 's':
         eSSParams->collectStats = 1;
         printf("%d\n", eSSParams->collectStats);
         break;
       case 'r':
         eSSParams->saveOutput = 1;
         printf("%d\n", eSSParams->saveOutput);
         break;
       case 'l':
         eSSParams->perform_LocalSearch = 1;
         printf("%d\n", eSSParams->perform_LocalSearch);
         break;
       case 'o':
         	// eSSParams->local_method = (char*)optarg;
         	printf("%c\n", eSSParams->local_method);
         // 	printf("Use `l` for Levenberg-Marquardt or 'n' for Nelder-Mead Simplex method.");
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
		printf("%d: ", i); print_Ind(eSSParams, &(set->members[i]));
	}
	printf("\n");

}

void print_Ind(eSSType *eSSParams, individual *ind){

	for (int i = 0; i < eSSParams->n_Params; ++i)
	{
		printf("%.5lf, ", ind->params[i]);
	}	
	// printf("\t (cost: %lf)\t(dist: %lf)\n", ind->cost, ind->dist);
	printf("\t (cost: %lf)\n", ind->cost/*, ind->dist*/);

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
	printf("n_iter: %d\n", eSSParams->maxiter);
	printf("n_successful_goBeyond: %d\n", eSSParams->stats->n_successful_goBeyond);
	printf("n_local_search_performed: %d\n", eSSParams->stats->n_local_search_performed);
	printf("n_successful_localSearch: %d\n", eSSParams->stats->n_successful_localSearch);
	printf("n_local_search_iterations: %d \t (avg: %lf)\n", eSSParams->stats->n_local_search_iterations, (double)eSSParams->stats->n_local_search_iterations / eSSParams->stats->n_successful_localSearch);
	printf("n_Stuck: %d\n", eSSParams->stats->n_Stuck);
	printf("n_successful_recombination: %d\n", eSSParams->stats->n_successful_recombination);
	printf("%s\n", KNRM);

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