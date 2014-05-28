#include "ess.h"

/**
 * Sort the set of individual with respect to their cost (`c`) or dist (`d`).
 */
void quickSort_Set(eSSType *eSSParams, Set *set, int left, int right, char key){

	double *values;
	values = (double *)malloc(set->size * sizeof(double));
	// allocate_ind_memory(eSSParams, &(pivot_ind), eSSParams->nreal);
			// TODO: It could be as a static variable

	for (int i = 0; i < set->size; ++i)
	{
		if (key == 'c')
			values[i] = set->members[i].cost;
		else if (key == 'd')
			values[i] = set->members[i].dist;
	}

	// printf("hi\n");
	quickSort(eSSParams, set, values, left, right);
	// printf("hi\n");
	// deallocate_ind_memory(eSSParams, &(pivot_ind));
	free(values);

}

individual pivot_ind;								// Might cause problem
/**
 * Perform QuickSort in-place, based on the values array which could be cost or dist.
 */
void quickSort(eSSType *eSSParams, Set *set, double* values, int left, int right){

	double pivot;
	int l_hold, r_hold;

	l_hold = left;
	r_hold = right;
	pivot = values[left];

	pivot_ind = set->members[left];

	while (left < right)
	{
		while ((values[right] >= pivot) && (left < right))
			right--;

		if (left != right)
		{
			values[left] = values[right];
			set->members[left] = set->members[right];
			// TODO: Check the assigment
			left++;
		}

		while ((values[left] <= pivot) && (left < right))
			left++;

		if (left != right)
		{
			values[right] = values[left];
			set->members[right] = set->members[left];
			// TODO: Check the assignment
			right--;
		}
	}

	values[left] = pivot;

	set->members[left] = pivot_ind;

	pivot = left;
	left = l_hold;
	right = r_hold;

	// free(&pivot_ind);

	if (left < pivot)
		quickSort(eSSParams, set, values, left, pivot-1);

	if (right > pivot)
		quickSort(eSSParams, set, values, pivot+1, right);



}

/*
	Remove the last item of the set and put the ind at it's correct place, assuming that 
	the list is already a sorted list.
	So, it's basically a reverse Insertion Sort!
*/
	// TODO: Need to be modified
void insertionSort(eSSType *eSSParams, Set *set, int location, char key){
        
	individual temp;
    // allocate_ind_memory(eSSParams, &(temp), eSSParams->nreal);
    int j =  location;			// The iteration starts from `set->size - 1` since the last
    								// item should be replaced anyway.
 
    while (j > 0 && set->members[j].cost < set->members[j - 1].cost) {

    	temp 				= set->members[j - 1];
    	set->members[j - 1] = set->members[j];
    	set->members[j] 	= temp;

     	j--;

    }

    // free(&temp);
    // deallocate_ind_memory(eSSParams, &(temp));

       
}

