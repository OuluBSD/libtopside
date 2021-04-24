#ifndef __Plugin_bz2lib__
#define __Plugin_bz2lib__

#ifdef flagWIN32
	#include "lib/bzlib.h"
#else
	#include <bzlib.h>
#endif

namespace Upp {

String BZ2Compress(String s, int level, bool allow_empty);
String BZ2Decompress(String s, bool allow_fail);

}

#endif//__Plugin_Z__
