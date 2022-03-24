#ifndef _SerialMach_SerialMach_h_
#define _SerialMach_SerialMach_h_

#include <AtomDebug/AtomDebug.h>


#undef Serial
#define NAMESPACE_SERIAL_NAME	Serial
#define SERIAL					Serial
#define NAMESPACE_SERIAL_BEGIN	namespace TS { namespace NAMESPACE_SERIAL_NAME {
#define NAMESPACE_SERIAL_END	}}


#include "Fn.h"
#include "Types.h"
#include "Link.h"
#include "Base.h"
#include "LoopSystem.h"



#endif
