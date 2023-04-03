#ifndef _Core_Core0_h_
#define _Core_Core0_h_

#define DLOG(x) LOG(x)

#ifdef UPP_VERSION
	#error Cannot compile Topside Core with UPP flag set
#endif

#include <SharedCore/SharedDefs.h>
#include <SharedCore/Policies.h>

#include "config.h"
#include "Macros.h"
#include "Defs.h"
#include <SharedCore/RTTIDummy.h>
#include "Atomic.h"
#include "Fn.h"
#include "Ops.h"
#include "Topt.h"
#include "Atomic.h"
#include "Heap.h"
#include <SharedCore/Random.h>
#include "Algo.h"
#include "String_.h"
#include <SharedCore/String.h>
#include "Hash.h"
#include "App.h"
#include "Heap.h"
#include "Uuid.h"
#include <SharedCore/Container.h>
#include "Tuple.h"
#include "Vcont.h"
#include "SplitMerge.h"
#include "Path.h"

#endif
