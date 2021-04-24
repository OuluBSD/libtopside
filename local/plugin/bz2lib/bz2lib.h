#ifndef __Plugin_bz2lib__
#define __Plugin_bz2lib__

#ifdef flagWIN32
	#include "lib/bzlib.h"
#else
	#include <bzlib.h>
#endif

namespace Upp {

void BZ2Decompress(Stream& out, Stream& in);
void BZ2Compress(Stream& out, Stream& in);
String BZ2Compress(Stream& in);
String BZ2Decompress(Stream& in);
String BZ2Compress(const void *data, int64 len);
String BZ2Decompress(const void *data, int64 len);
String BZ2Compress(const String& data);
String BZ2Decompress(const String& data);

}

#endif//__Plugin_Z__
