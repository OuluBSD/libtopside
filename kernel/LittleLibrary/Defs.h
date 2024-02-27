#ifndef _LittleLibrary_Defs_h_
#define _LittleLibrary_Defs_h_

#ifdef flagHWEMU
#define PACKED_ATTR
#define HWEMU 1
#else
#define PACKED_ATTR __attribute__((packed))
#define HWEMU 0
#endif

#endif
