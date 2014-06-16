## Enhanced Scatter Search In C

This repository contains a C implementation of derivation of a Scatter Search algorithm developed by Mario .... The first implementation was in matlab in a so called “eSS” package which is not supported anymore; in fact, the improved and parallelise matlab version is now included in the package called AMIGO. The source code for improved eSS implementation is available in form of M-packages. The C version presented here is based on the latest changes to the algorithm but not provide the parallize algorithm yet. 

### Enhanced Scatter Search Algorithm 

Enhanced Scatter search is a meta heuristic population based algorithm with similarities to evolutionary strategies. The eSS is designed specifically for optimizing biological system and it achieved very good results which some of them are listed on ...

Let's start with pure Scatter Search algorithm. Scatter search is a working with the same population based principle as genetic and evolutionary algorithm with some variants in its selection and combination routine. Basically, what happens is that new children or candidate generates based on the linear combinations of its parents; and parents are selected by considering all the combination of the individual in a population or "Reference Set".

The pure scatter search algorithm describes below:

1. Start with a  diverse set of solution in the search space called "diverseSet"
2. Select best solutions from _diverseSet_ to form a "referenceSet"
3. repeat
	1. For all possible combination of solutions in the _referenceSet_ generate one or more candidate by using linear combination of their parameters, "candidateSet".
	2. Check every generated solutions in the previous step with the worst solution in the _referenceSet_ and replace the later with a new candidate. Repeat this process until no solution in _candidateSet_ has better fitness or cost than the worst solution of the _referenceSet_.
	3. Perform refinement procedure on new solution added to the _referenceSet_.
	4. Continue this procedure until the maximum number of iteration reaches or the stop criteria satisfies.
4.	Report the best solution in the _referenceSet_ as a result and the _referenceSet_ as the final population.

This is the basic structure of an scatter search algorithm which can be divided into 5 steps, 


### Prerequisites

The local search algorithms (Nelder-Mead and Levenberg-Marquardt) are provided using the GNU Scientific Library (GSL). So, you need to install GSL in order to use local search algorithms. To install the gsl follows the procedure below for your OS:

OS X:
	
	’brew install gsl’

Linux (Ubuntu):

	’sudo apt-get install libgsl0-dev’

### Make

In order to make the program just run the
	
	make clean; make

### Running the optimization

The `_ess.o` executable file will be generated after the compilation. To run the optimization just execute the file using `./_ess.o` in the command line. *In order to test different benchmark function, uncomment different `#include` statement in `essProblem.c` file. Note that the Levenberg-Marquardt algorithm is only can be set for `expo.h` test problem.*

### Defining the objective function

In order to perform the optimization you need a objective function to compute the cost of each individual during the optimization process. The functions `eval_Ind` and `eval_Set` are defined to call user defined objective function independent from the actual objective function definition. In each run, they call `objectiveFunction`; this function decides how to call the user defined objective function. Since the local search routines are implemented using `gel` library, you need to define special function pointer to pass to the `gsl_` functions.

If you look at the code of one of the benchmark functions, you see that there are 3 similar functions are defined. I recommend you define your cost function inside the `objfn` and leave the `nelder_objfn` and `levermed_objfn` function untouched since as you see they are just translating an array to `gsl_vector`. 

The last thing that you should do is to modify `objectiveFunction` in such a way that it sends a `double` array to `objfn` or other objective functions.

### Role of `inp` and `out`

### TODO:
[ ] Implement the local search candidate selection routine
[ ] Test it on more sophosticated functions
