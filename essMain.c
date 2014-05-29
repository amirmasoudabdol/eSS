#include "ess.h"
#include "time.h"

int main(int argc, char const *argv[])
{
	eSSType l_essParams;
	void *inp = NULL;
	void *out = NULL;

	// srand(time(NULL));

	printf("eSS - Enhanced Scatter Search\n");
	
	init_eSS(&l_essParams, inp, out);

	run_eSS(&l_essParams, inp, out);

	deallocate_eSSParams(&l_essParams);

	return 0;
}