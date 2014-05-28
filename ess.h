#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEBUG
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
	double *means;
	double *stds;
	double cost;
	double dist;

	int nStuck;

} individual;

typedef struct Set{
	
	individual *members;
	int size;

} Set;

typedef struct Stats{



	double **freq_matrix;
	double **prob_matrix;
} Stats;


typedef struct eSSType{

	/**
	 * User Options
	 */
	double *log_bound;
	int maxeval;
	int maxtime;
	int iterprint;
	bool plot;
	double *weight;
	double tolc;
	double prob_bound;
	int strategy;
	int inter_save;
	bool is_warmStart;

	/**
	 * Global Options
	 */
	int n_Params;
	double *min_real_var;
	double *max_real_var;
	double **min_boundary_matrix;
	double **max_boundary_martix;
	
	int n_RefSet;
	Set *refSet;
	
	int n_DiverseSet;
	Set *diverseSet;

	int n_childsSet;
	Set *childsSet;

	int n_candidateSet;
	Set *candidateSet;

	int init_RefSet_Type;
	int combination_Type;
	int regeneration_Type;
	// int delete;
	int intensification_Freqs;
	int diversification_Type;
	double cost_Tol;
	double dist_Tol;
	double param_Tol;
	double stuck_Tol;

	/**
	 * Local Search Options
	 */
	int perform_LocalSearch;
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
extern FILE *ref_set_history_file;
extern FILE *best_sols_history_file;
extern FILE *freqs_matrix_file;
extern FILE *freq_mat_final_file;
extern FILE *prob_mat_final_file;
extern FILE *ref_set_final_file;
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
void goBeyond(eSSType*, individual*, void*, void*);

/**
 * essLocalSearch.c
 */
void localSearch(eSSType*, individual*, void*, void*);

/**
 * essRecombine.c
 */
void recombine(eSSType*, individual*, individual*);


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
void euclidean_distance(eSSType*, individual*, individual*);
void isExist(eSSType*, individual*);
void min(eSSType*, double*, double*, int*);
void max(eSSType*, double*, double*, int*);

/**
 * essRand.c
 */
double rndreal(double, double);
void random_Set(eSSType*, Set*, double, double );
void random_Ind(eSSType*, individual*, double, double );

/**
 * essProblem.c
 */
double objectiveFunction(eSSType*, individual*, void*, void*);
void init_sampleParams(eSSType*);

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
void print_eSSParams(eSSType*);
void print_Set(eSSType*, Set*);
void print_Ind(eSSType*, individual*);
void write_Set(eSSType*, Set*, FILE*, char *mode);
void write_Ind(eSSType*, individual*, FILE*, char *mode);

/**
 * essMain.c
 */




