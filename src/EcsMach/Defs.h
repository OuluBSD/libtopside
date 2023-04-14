#ifndef _EcsMech_Defs_h_
#define _EcsMech_Defs_h_

#ifndef CXX2A_STATIC_ASSERT
	#if defined flagMSC && !defined flagUWP
		#define CXX2A_STATIC_ASSERT(x, y) static_assert(x, y)
	#else
		#define CXX2A_STATIC_ASSERT(x, y)
	#endif
#endif

#define ECS_SYS_CTOR_(x) \
	typedef x CLASSNAME; \
	x(Engine& e) : SP(e)


#endif
