#ifndef _TrustCore_TrustCore_h_
#define _TrustCore_TrustCore_h_

#include <Statistics/Statistics.h>

#if 0
	#define LLOG(x) LOG(x)
	#define LDUMPM(x) DUMPM(x)
	#define LDUMPC(x) DUMPC(x)
	#define LDUMPCC(x) DUMPCC(x)
#else
	#define LLOG(x)
	#define LDUMPM(x)
	#define LDUMPC(x)
	#define LDUMPCC(x)
#endif

#include "Graph.h"
#include "Util.h"
#include "Net.h"

#endif
