#ifndef _Local_Defs_h_
#define _Local_Defs_h_


#define CHKLOGRET0(x, y) if (!(x)) {LOG(y); return false;}
#define CHKLOGRET1(x, y) if (!(x)) {LOG(y); return true;}

#define SET_ZERO(x) memset(x, 0, sizeof(x))




#define NAMESPACE_PARALLEL_NAME		Parallel
#define PARALLEL					Parallel
#define NAMESPACE_PARALLEL_BEGIN	\
	static_assert(!is_in_parallel, "already in parallel"); \
	namespace TS { namespace NAMESPACE_PARALLEL_NAME {
#define NAMESPACE_PARALLEL_END		}}



#ifndef M_2PI
#define M_2PI	6.283185307179586
#endif

#ifndef M_PI
#define M_PI	3.1415926535897932384626433832795
#endif

#ifndef M_PIDIV2
#define M_PIDIV2	1.5707963267948966
#endif

#ifndef M_PIDIV4
#define M_PIDIV4	0.7853981633974483
#endif


	

#endif
