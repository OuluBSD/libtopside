#ifndef _SerialMach_SerialMach_h_
#define _SerialMach_SerialMach_h_

#include <AtomMinimal/AtomMinimal.h>

#ifndef HAVE_PACKETTIMING
	#error HAVE_PACKETTIMING not defined
#endif


#undef Serial
#define NAMESPACE_SERIAL_NAME	Serial
#define SERIAL					Serial
#define NAMESPACE_SERIAL_BEGIN	namespace TS { namespace NAMESPACE_SERIAL_NAME {
#define NAMESPACE_SERIAL_END	}}


#include "Fn.h"
#include "Types.h"
#include "Factory.h"
#include "Link.h"
#include "LinkStore.h"
#include "LinkSystem.h"
#include "LinkUtil.h"
#include "Base.h"



#endif
