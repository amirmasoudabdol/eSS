#include "ess.h"
#include <ctype.h>
#include <unistd.h>

void read_cli_params(eSSType *eSSParams, int argc, char **argv){

   // char *cvalue = NULL;
   // int index;
   int c;
   printf("hi\n");
	while ((c = getopt (argc, argv, "m:dlo:")) != -1)
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
       case 'l':
         eSSParams->perform_LocalSearch = 1;
         printf("%d\n", eSSParams->perform_LocalSearch);
         break;
       case 'o':
         	eSSParams->local_method = (char*)optarg;
         	printf("%s\n", eSSParams->local_method);
         // 	printf("Use `l` for Levenberg-Marquardt or 'n' for Nelder-Mead Simplex method.");
         break;
       case '?':
         if (optopt == 'c')
           fprintf (stderr, "Option -%c requires an argument.\n", optopt);
         else if (isprint (optopt))
           fprintf (stderr, "Unknown option `-%c'.\n", optopt);
         else
           fprintf (stderr,
                    "Unknown option character `\\x%x'.\n",
                    optopt);
         // return 1;
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


void write_Set(eSSType *eSSParams, Set *set, FILE *fpt, int iter, char mode){

	for (int i = 0; i < set->size; ++i)
	{
		write_Ind(eSSParams, &(set->members[i]), fpt, iter, mode);
	}
}

void write_Ind(eSSType *eSSParams, individual *ind, FILE *fpt, int iter, char mode){

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
	printf("n_successful_goBeyond: %d\n", eSSParams->stats->n_successful_goBeyond);
	printf("n_successful_localSearch: %d\n", eSSParams->stats->n_successful_localSearch);
	printf("n_Stuck: %d\n", eSSParams->stats->n_Stuck);
	printf("n_successful_recombination: %d\n", eSSParams->stats->n_successful_recombination);
	printf("%s\n", KNRM);

}