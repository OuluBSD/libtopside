#ifndef _Core_Core0_h_
#define _Core_Core0_h_

#define DLOG(x) LOG(x)

#ifdef UPP_VERSION
	#error Cannot compile Topside Core with UPP flag set
#endif

#include <SharedCore/SharedDefs.h>
#include <SharedCore/Policies.h>

#include "config.h"
#include "Defs.h"
#include <SharedCore/RTTIDummy.h>
#include "Macros.h"
#include "Fn.h"
#include "Topt.h"
#include "Ops.h"
#include "Hash.h"
#include <SharedCore/Random.h>
#include "Algo.h"
#include "String_.h"
#include <SharedCore/String.h>

#endif
