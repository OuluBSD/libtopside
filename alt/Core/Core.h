#ifndef CORE_H
#define CORE_H

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
	#define NAMESPACE_UPP namespace  Upp {
	#define END_UPP_NAMESPACE }
	#define NAMESPACE_UPP_BEGIN namespace  Upp {
	#define NAMESPACE_UPP_END }
	#define UPP Upp
#endif



#include "Config.h"
#include "Defs.h"
#include <SharedCore/RTTIDummy.h>
#include "Macros.h"
#include "Fn.h"
#include "Topt.h"
#include "Ops.h"
#include "Hash.h"
#include "Algo.h"
#include "String_.h"
#include "Tuple.h"
#include <SharedCore/Container.h>
#include "Vector.h"
#include <SharedCore/Shared.h>
#include "Stream.h"
#include "Math.h"
#include "Callback.h"
#include "Util.h"
#include "Sort.h"
#include "Chrono.h"
#include "Geom.h"
#include "Graph.h"
#include "Thread.h"
#include "Socket.h"
#include "Ptr.h"
#include "Value.h"
#include <SharedCore/Object.h>
#include "Parser.h"
#include "JSON.h"
#include "System.h"
#include <SharedCore/CtrlEvent.h>
#include "Internet.h"






#endif
