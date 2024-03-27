#ifndef _LittleCore_Defs_h_
#define _LittleCore_Defs_h_

#ifndef flagEMU
typedef unsigned char      byte;
typedef signed char        int8;
typedef unsigned char      uint8;

typedef short unsigned     word;
typedef short int          int16;
typedef short unsigned     uint16;

#ifdef PLATFORM_WIN32
typedef unsigned long      dword;
typedef long               int32;
typedef unsigned long      uint32;
typedef WCHAR              wchar;
#else
typedef unsigned int       dword;
typedef int                int32;
typedef unsigned int       uint32;
typedef word               wchar;
#endif

#ifdef COMPILER_MSC
typedef __int64            int64;
typedef unsigned __int64   uint64;
#else
typedef long long int      int64;
typedef long long unsigned uint64;
#endif

#if __i386 || __i386__ || i386
typedef unsigned int		size_t;
#elif __x86_64
typedef long long unsigned	size_t;
#endif




#define ASSERT(b) ((b) ? (void)0 : PanicAssert(__FILE__, __LINE__, #b))


#define TODO ASSERT(false);

#endif


#endif
