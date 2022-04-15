#ifndef _Local_Defs_h_
#define _Local_Defs_h_


#define CHKLOGRET0(x, y) if (!(x)) {LOG(y); return false;}
#define CHKLOGRET1(x, y) if (!(x)) {LOG(y); return true;}

#define SET_ZERO(x) memset(x, 0, sizeof(x))




#define NAMESPACE_PARALLEL_NAME		Parallel
#define PARALLEL					Parallel
#define NAMESPACE_PARALLEL_BEGIN	namespace TS { namespace NAMESPACE_PARALLEL_NAME {
#define NAMESPACE_PARALLEL_END		}}



#endif
