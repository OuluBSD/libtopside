#ifndef _plugin_assimp_z_h_
#define _plugin_assimp_z_h_

#ifdef flagALTCORE
	#include <ports/zlib/zlib.h>
#else
	#include <plugin/z/lib/zlib.h>
#endif

#include <ports/unzip/unzip.h>

#undef max
#undef min


#endif
