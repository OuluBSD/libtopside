#ifndef _Core_Core0_h_
#define _Core_Core0_h_

#define DLOG(x) LOG(x)

#ifdef UPP_VERSION
	#error Cannot compile Topside Core with UPP flag set
#endif


#ifdef flagDEBUG
	#define HAVE_SHORT_NAMESPACE 1
#else
	#define HAVE_SHORT_NAMESPACE 0
#endif


#if HAVE_SHORT_NAMESPACE
	#define NAMESPACE_UPP namespace  ts {
	#define END_UPP_NAMESPACE }
	#define NAMESPACE_UPP_BEGIN namespace  ts {
	#define NAMESPACE_UPP_END }
	#define UPP ts
#else
	#define NAMESPACE_UPP namespace  Topside {
	#define END_UPP_NAMESPACE }
	#define NAMESPACE_UPP_BEGIN namespace  Topside {
	#define NAMESPACE_UPP_END }
	#define UPP Topside
#endif



#include <SharedCore/Policies.h>

#include "config.h"
#include "Defs.h"
#include <SharedCore/RTTIDummy.h>
#include "Macros.h"
#include "Fn.h"
#include "Topt.h"
#include "Ops.h"
#include "Hash.h"
#include "Algo.h"
#include "String_.h"
#include <SharedCore/String.h>

#endif
