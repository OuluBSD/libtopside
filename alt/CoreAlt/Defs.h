#ifndef _CoreAlt_Defs_h_
#define _CoreAlt_Defs_h_

#include <stdint.h>


#ifdef WINSOCK_HACK_FIX
	#define _WS2DEF_
	#define _WINSOCK2API_
	#define _WS2IPDEF_
	#define _WS2TCPIP_H_

#else
	#ifdef flagWIN32
		#include <ws2tcpip.h>
		#include <Windows.h>
		#include <winsock2.h>
		#if defined flagAMP
			#include <amp.h>
			#include <amp_math.h>
			#include <amp_graphics.h>
			#include <dxgi.h>
			#include <d3dcommon.h>
			#include <d3d9types.h>
			#include <d3d11.h>
			#include <d3dcompiler.h>
			#include <directxmath.h>
		#endif
	#endif
#endif




#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <stdio.h>
#include <float.h>
#include <math.h>
#include <string.h>

#if defined flagPOSIX
	#include <unistd.h>
#endif

#if defined flagFREEBSD
	#include <sys/time.h>
#endif

#if defined flagMSC
	#include <string.h> // memcmp
#endif

#include <functional>
#include <chrono>
#include <initializer_list>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <algorithm>
#include <tuple>
#include <shared_mutex>
#include <atomic>
#include <functional>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <codecvt>
#include <random>
#include <memory>
#include <complex>

#include <emmintrin.h>

#ifdef flagPOSIX
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#endif

#undef near
#undef far


#ifdef flagGLM
#include <plugin/glm/glm.hpp>
#include <plugin/glm/gtc/type_ptr.hpp>
#include <plugin/glm/gtx/transform.hpp>
#include <plugin/glm/gtx/intersect.hpp>
#include <plugin/f/gtx/matrix_decompose.hpp>
#include <plugin/glm/gtx/euler_angles.hpp>
#include <plugin/glm/gtc/matrix_transform.hpp>
#include <plugin/glm/gtc/type_ptr.hpp>
#include <plugin/glm/trigonometric.hpp>
#include <plugin/glm/gtx/quaternion.hpp>

using namespace glm;
#endif


#undef GetFileTitle
using namespace std::chrono; 






NAMESPACE_UPP_BEGIN

#define UPP Upp

#if defined __linux__ || defined __freebsd__ || defined flagPOSIX
	#define DIR_SEPS "/"
	#define DIR_SEP  '/'
	#define EOL "\n"
	#define PLATFORM_POSIX
	#ifdef __x86_64__
		#define CPU_64	1
	#endif
	#ifdef __GNUC__
		#define COMPILER_GNU
	#endif
	#ifdef __clang__
		#define COMPILER_CLANG
	#endif
#elif defined _WIN32 || defined WINAPI_FAMILY
	#undef  flagWIN32
	#define flagWIN32
	#define EOL "\r\n"
	#define DIR_SEP  '\\'
	#define DIR_SEPS "\\"
	#ifdef _MSC_VER
		#define COMPILER_MSC
		#ifdef _WIN64
			#define CPU_64	1
		#endif
	#endif
	#ifdef __clang__
		#ifdef __x86_64__
			#define CPU_64	1
		#endif
	#endif
	#ifdef __GNUC__
		#ifdef __x86_64__
			#define CPU_64	1
		#endif
	#endif
#endif



#ifdef flagWIN32
	#define __BREAK__		__debugbreak()
#elif defined flagPOSIX
	#define __BREAK__        raise(SIGTRAP);
#else
	#define __BREAK__        (*(volatile int *)0 = 0) // kill(getpid(), SIGTRAP)
#endif

#undef ASSERT
#undef ASSERT_
#ifdef flagDEBUG
#define ASSERT(x) {if (!(x)) {LogCString("Assertion failed: " #x); __BREAK__; Panic();}}
#define ASSERT_(x, msg) {if (!(x)) {LOG(Upp::String("Assertion failed: ") + msg); __BREAK__; Panic();}}
#else
#define ASSERT(x)
#define ASSERT_(x, msg)
#endif
#define PANIC(msg) ASSERT_(false, msg)

#define PKG(x) <x/x.h>


typedef unsigned char	uint8;
typedef char			int8;
typedef unsigned short	uint16;
typedef short			int16;
typedef unsigned int	uint32;
typedef int				int32;
typedef uint64_t		uint64;
typedef int64_t			int64;
typedef wchar_t			wchar;

typedef unsigned char	Byte;
typedef unsigned char	byte;
typedef uint16			word;
typedef uint32			dword;
typedef uint64			qword;

typedef unsigned long	DWORD;

typedef unsigned int	hash_t;


typedef const char*		CString;
typedef const wchar_t*	CWString;

template <class T>
inline void IGNORE_RESULT(const T&) {}


typedef void* VOID_PTR;
typedef const void* CONST_VOID_PTR;




NAMESPACE_UPP_END



#if defined flagWIN32 && ( defined flagCLANG || defined flagGCC )

#include <sec_api/stdlib_s.h> /* errno_t, size_t */
extern "C" {
errno_t getenv_s(
    size_t     *ret_required_buf_size,
    char       *buf,
    size_t      buf_size_in_bytes,
    const char *name
);
}
#endif


#endif
