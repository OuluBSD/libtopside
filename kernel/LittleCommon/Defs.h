#ifndef _LittleCommon_Defs_h_
#define _LittleCommon_Defs_h_


#define TRACE(x)

#ifdef flagEMU
	#define EMU		1
	#define REALHW	0
	#define PACKED
	#ifdef flagGUI
		#define EMUGUI		1
	#endif
#else
	#define EMU		0
	#define REALHW	1
	#define PACKED	__attribute__((packed))
#endif



#if REALHW
	#define EXTERN_C_BEGIN extern "C" {
	#define EXTERN_C_END }
#endif

#if EMU
	#define EXTERN_C_BEGIN
	#define EXTERN_C_END
#endif



#endif
