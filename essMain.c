#include "ess.h"
#include "time.h"

int main(int argc, char **argv)
{
	eSSType l_essParams;
	void *inp = NULL;
	void *out = NULL;

	read_cli_params(&l_essParams, argc, argv);

	srand(time(NULL));

	printf("eSS - Enhanced Scatter Search\n");
	
	init_eSS(&l_essParams, inp, out);

	run_eSS(&l_essParams, inp, out);

	deallocate_eSSParams(&l_essParams);

	return 0;
}