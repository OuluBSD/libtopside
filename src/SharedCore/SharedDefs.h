#ifndef _SharedCore_SharedDefs_h_
#define _SharedCore_SharedDefs_h_

#ifdef flagDEBUG
	#define HAVE_SHORT_NAMESPACE 1
#else
	#define HAVE_SHORT_NAMESPACE 0
#endif

#ifndef NAMESPACE_UPP
	#if HAVE_SHORT_NAMESPACE
		#define NAMESPACE_UPP namespace  ts {
		#define END_UPP_NAMESPACE }
		#define UPP ts
	#else
		#define NAMESPACE_UPP namespace  Topside {
		#define END_UPP_NAMESPACE }
		#define UPP Topside
	#endif
#endif

#define NAMESPACE_UPP_BEGIN namespace  UPP {
#define NAMESPACE_UPP_END }

#if HAVE_SHORT_NAMESPACE
	#define NAMESPACE_TOPSIDE_NAME ts
	#define NAMESPACE_TOPSIDE_BEGIN \
		/*static_assert(is_in_topside == false, "already in topside namespace");*/ \
		namespace NAMESPACE_TOPSIDE_NAME {
	#define NAMESPACE_TOPSIDE_END }
	#define TS ts
#else
	#define NAMESPACE_TOPSIDE_NAME Topside
	#define NAMESPACE_TOPSIDE_BEGIN \
		/*static_assert(is_in_topside == false, "already in topside namespace");*/ \
		namespace NAMESPACE_TOPSIDE_NAME {
	#define NAMESPACE_TOPSIDE_END }
	#define TS Topside
	namespace UPP {}
	namespace TS {using namespace UPP;}
#endif

// initialize namespace
namespace TS  {}

#ifdef UPP_VERSION
	#define IS_UPP_CORE 1
	#define IS_TS_CORE 0
#else
	#define IS_UPP_CORE 0
	#define IS_TS_CORE 1
#endif

#endif
