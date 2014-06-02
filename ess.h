#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_multimin.h>
#include <gsl/gsl_multifit_nlin.h>


// #define DEBUG
#define STATS
#define LOG

/**
 * Colors code for printing
 */
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define eul 2.71828182845905
#define pi 3.14159265358979

#ifndef MAX
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#endif

typedef struct individual{
	
	double *params;
	double mean;
	double std;
	double cost;
	double dist;

	int nStuck;

} individual;

typedef struct Set{
	
	individual *members;
	int size;

} Set;

typedef struct Stats{

	int n_successful_goBeyond;
	int n_successful_localSearch;
	int n_Stuck;
	int n_successful_recombination;

	int **freqs_matrix;
	double **probs_matrix;
} Stats;


typedef struct eSSType{

	/**
	 * User Options
	 */
	double *log_bound;
	int maxeval;
	int maxtime;
	int maxiter;
	int iterprint;
	bool plot;
	double *weight;
	double tolc;
	double prob_bound;
	int strategy;
	int inter_save;
	bool is_warmStart;
	int n_subRegions;
	int debug;

	/**
	 * Global Options
	 */
	int n_Params;
	double *min_real_var;
	double *max_real_var;
	double **min_boundary_matrix;
	double **max_boundary_matrix;
	
	int n_refSet;
	Set *refSet;
	
	int n_scatterSet;
	Set *scatterSet;

	int n_childsSet;
	Set *childsSet;						// Stores best members of recombinedSet for each refSet member, size: n_refSet

	int n_candidateSet;
	Set *candidateSet;					// Stores childs generated from each refSet in each generation, size: n_refSet - 1

	individual *best;

	int init_RefSet_Type;
	int combination_Type;
	int regeneration_Type;
	// int delete;
	int intensification_Freqs;
	int diversification_Type;
	double cost_Tol;
	double dist_Tol;
	double param_Tol;
	double maxStuck;

	/**
	 * Local Search Options
	 */
	int perform_LocalSearch;
	char* local_method;
	int local_Freqs;
	int local_SolverMethod;
	int local_Tol;
	int local_IterPrint;
	int local_N1;
	int local_N2;
	int local_Balance;
	int local_atEnd;
	int local_onBest_Only;
	int local_merit_Filter;
	int local_distance_Filter;
	double local_th_merit_Factor;
	double local_max_distance_Factor;
	int local_wait_maxDist_limit;
	int local_wait_th_limit;


	Stats *stats;

} eSSType;



/**
 * Gloabl output files...
 */
extern FILE *refSet_history_file;
extern FILE *best_sols_history_file;
extern FILE *freqs_matrix_file;
extern FILE *freq_mat_final_file;
extern FILE *prob_mat_final_file;
extern FILE *refSet_final_file;
extern FILE *stats_file;


/**
 * essInit.c
 */
void init_essParams(eSSType*);
void init_scatterSet(eSSType*, void*, void*);
void init_refSet(eSSType*, void*, void*);
void init_report_files(eSSType *);
void init_stats(eSSType *);

/**
 * essStats.c
 */
void updateFrequencyMatrix(eSSType*);
void compute_Mean(eSSType*, individual*);
void compute_Std(eSSType*, individual*);

/**
 * essGoBeyond
 */
void goBeyond(eSSType*, int, void*, void*);

/**
 * essLocalSearch.c
 */
void localSearch(eSSType*, individual*, void*, void*, char method);
int levmer_localSearch(eSSType *eSSParams, individual *ind, void *inp, void *out);
int neldermead_localSearch(eSSType *eSSParams, individual *ind, void *inp, void *out);

/**
 * essRecombine.c
 */
int recombine(eSSType*, individual*, int, void*, void*);

/**
 * essSort.c
 */
void quickSort_Set(eSSType*, Set*, int, int, char);
void quickSort(eSSType*, Set*, double*, int, int);
void insertionSort(eSSType*, Set*, int, char);

/**
 * essAllocate.c
 */
void allocate_Ind(eSSType *, individual *);
void deallocate_Ind(eSSType *, individual *);
void allocate_Set(eSSType *, Set *);
void deallocate_Set(eSSType *, Set *);
void deallocate_eSSParams(eSSType *);


/**
 * essTools.c
 */
double euclidean_distance(eSSType*, individual*, individual*);
void isExist(eSSType*, individual*);
double min(double*, int, int*);
double max(double*, int, int*);
void copy_Ind(eSSType *, individual *, individual *);
void delete_and_shift(eSSType *eSSParams, Set *set, int set_size, int index_to_delete);

/**
 * essRand.c
 */
double rndreal(double, double);
void random_Set(eSSType*, Set*, double*, double* );
void random_Ind(eSSType*, individual*, double*, double* );

/**
 * essProblem.c
 */
double objectiveFunction(eSSType*, individual*, void*, void*);
void init_sampleParams(eSSType*);
// #define GSL_TESTFUNCTION
// #define NELDER
// #define LEVMER
#ifdef GSL_TESTFUNCTION 
	void bounds(double lb[], double ub[]);
	int feasible(double x[]);
	#ifdef LEVMER
		int objfn(const gsl_vector *x, void *data, gsl_vector *f);
	#elif defined(NELDER)
		double objfn(const gsl_vector *x, void *data);
	#endif
#endif


/**
 * Benchmark functions prototype
 */
void bounds(double lb[], double ub[]);
int feasible(double x[]);
double objfn(double x[]);
double nelder_objfn(const gsl_vector *x, void *data);


/**
 * essEvaluate.c
 */
void evaluate_Individual(eSSType*, individual*, void*, void*);
void evaluate_Set(eSSType*, Set*, void*, void*);

/**
 * ess.c
 */
void init_eSS(eSSType*, void*, void*);
void run_eSS(eSSType*, void*, void*);


/**
 * essIO.c
 */
void read_cli_params(eSSType *, int, char **);
void print_eSSParams(eSSType*);
void print_Set(eSSType*, Set*);
void print_Ind(eSSType*, individual*);
void write_Set(eSSType*, Set*, FILE*, int, char);
void write_Ind(eSSType*, individual*, FILE*, int, char);
void print_Stats(eSSType *);

/**
 * essMain.c
 */




