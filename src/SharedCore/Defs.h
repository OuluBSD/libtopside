#ifndef _SharedCore_Defs_h_
#define _SharedCore_Defs_h_


#define GLOBAL_VP(type, name, param) \
	name() { \
		MAKE_STATIC_(type, x, param); \
		return x; \
	}
#define GLOBAL_VARP(type, name, param)	type& name() {MAKE_STATIC_(type, x, param); return x; }
#define GLOBAL_V(type, name)			GLOBAL_VP(type, name, )
#define GLOBAL_VAR(type, name)			type& name() {MAKE_STATIC(type, x); return x; }
#define GLOBAL_VP_INIT(type, name, param) \
	name() \
	{ \
		MAKE_STATIC_(type, x, param); \
		return x; \
} \
INITBLOCK { name(); }


#endif
