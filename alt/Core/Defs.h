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
#include <algorithm>
#include <tuple>
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
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/quaternion.hpp>

using namespace glm;
#endif


#undef GetFileTitle
using namespace std::chrono; 






NAMESPACE_UPP_BEGIN

#define UPP Upp

#if PLATFORM_POSIX
	#define DIR_SEPS "/"
	#define DIR_SEP  '/'
	#define EOL "\n"
#elif PLATFORM_WIN32
	#define EOL "\r\n"
	#define DIR_SEP  '\\'
	#define DIR_SEPS "\\"
#endif



#if PLATFORM_WIN32
	#define __BREAK__		__debugbreak()
#elif PLATFORM_POSIX
	#define __BREAK__        raise(SIGTRAP);
#else
	#define __BREAK__        (*(volatile int *)0 = 0) // kill(getpid(), SIGTRAP)
#endif

#undef ASSERT
#undef ASSERT_
#ifdef flagDEBUG
#define ASSERT(x) {if (!(x)) {Upp::LogCString("Assertion failed: " #x); __BREAK__; Upp::Panic();}}
#define ASSERT_(x, msg) {if (!(x)) {LOG(Upp::String("Assertion failed: ") + msg); __BREAK__; Upp::Panic();}}
#else
#define ASSERT(x)
#define ASSERT_(x, msg)
#endif
#define PANIC(msg) ASSERT_(false, msg)

#define PKG(x) <x/x.h>


#define HAVE_OPENGL 1


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
