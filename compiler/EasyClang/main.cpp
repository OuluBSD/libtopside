#ifdef flagEASYCLANG_TESTS

#include "EasyClang.h"


CONSOLE_APP_MAIN {
	
	
	ClangNode n = CacheFile(GetDataFile("test1"));
	Dump(n);
	
	
}

#endif
