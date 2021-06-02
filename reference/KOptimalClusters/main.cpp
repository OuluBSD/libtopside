#include <Statistics/Statistics.h>

CONSOLE_APP_MAIN {
	using namespace UPP;
	using namespace TS;

	{
		VecFloat input;
		input.Add(-2);
		input.Add(1);
		input.Add(5);
		input.Add(1);
		input.Add(-2);
		input.Add(6);
		input.Add(-2);
		input.Add(1);
		input.Add(-2);
		input.Add(7);
		MatFloat res = CKMeans(input, 3);
		DUMPCC(res);
	}
	
}

