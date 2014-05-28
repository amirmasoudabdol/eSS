#include "ess.h"


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