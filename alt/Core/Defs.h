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
	#include <sys/time.h>
	#include <netinet/in.h>
#endif

#if defined flagMSC
	#include <string.h> // memcmp
	#include <corecrt_io.h>
	#include <Shlobj.h>
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
#include <numeric>

#if CPU_X86
	#include <emmintrin.h>
#endif

#if defined flagWIN32 && defined flagGCC
	#include <ports/MingwThreads/mingw.thread.h>
	#include <ports/MingwThreads/mingw.mutex.h>
	#define MINGWTHREAD 1
	using std_thread = mingw_stdthread::thread;
	using std_mutex = mingw_stdthread::mutex;
	#define std_thread_hardware_concurrency		mingw_stdthread::thread::hardware_concurrency
#else
	using std_thread = std::thread;
	using std_mutex = std::mutex;
	#define std_thread_hardware_concurrency		std::thread::hardware_concurrency
#endif

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




#ifndef flagSTDRTTI
	#include <RTTI/RTTI.h>
#endif

NAMESPACE_UPP_BEGIN

class Stream;  Stream& VppLog(); void Panic(); void Panic(const char* msg); void LogCString(const char* c);


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
	#define __BREAK__		__debugbreak();
#elif PLATFORM_POSIX
	#define __BREAK__        raise(SIGTRAP);
#else
	#define __BREAK__        (*(volatile int *)0 = 0); // kill(getpid(), SIGTRAP);
#endif

#undef ASSERT
#undef ASSERT_
#ifdef flagDEBUG
#define ASSERT(x) {if (!(x)) {::UPP::LogCString("Assertion failed: " #x); __BREAK__; ::UPP::Panic();}}
#define ASSERT_(x, msg) {if (!(x)) {LOG(::UPP::String("Assertion failed: ") + msg); __BREAK__; ::UPP::Panic();}}
#else
#define ASSERT(x)
#define ASSERT_(x, msg)
#endif
#define PANIC(msg) ASSERT_(false, msg); UNREACHABLE



#if defined flagGUI && !defined flagSCREEN
	#define flagSCREEN 1
#endif

#if defined flagSCREEN
	#if defined(flagPOSIX) || defined(flagWIN32) || defined(flagOPENGL)
		#define HAVE_OPENGL 1
	#endif
#endif


#ifdef COMPILER_MSC
#define force_inline __forceinline
#define never_inline __declspec(noinline)
#elif defined(COMPILER_GCC)
#define force_inline __attribute__((always_inline)) inline
#define never_inline __attribute__((noinline))
#else
#define force_inline inline
#define never_inline
#endif


typedef unsigned char	uint8;
typedef signed char		int8;
typedef unsigned short	uint16;
typedef signed short	int16;
typedef unsigned int	uint32;
typedef signed int		int32;
typedef uint64_t		uint64;
typedef int64_t			int64;
typedef wchar_t			wchar;

typedef unsigned char	Byte;
typedef unsigned char	byte;
typedef uint16			word;
typedef uint32			dword;
typedef uint64			qword;

typedef unsigned long	DWORD;

typedef size_t			hash_t;


typedef const char*		CString;
typedef const wchar_t*	CWString;

template <class T>
inline void IGNORE_RESULT(const T&) {}


typedef void* VOID_PTR;
typedef const void* CONST_VOID_PTR;




#ifndef flagSTDRTTI
template <class T> TypeCls AsTypeCls() {return T::TypeIdClass();}
template <class T> const RTTI& AsTypeId(const T& o) {const RTTI* r = o.GetTypeInfo(AsTypeCls<T>()); ASSERT(r); return *r;}
template <class T> const char* AsTypeName() {return T::GetTypeName();}
inline const RTTI& AsVoidTypeId() {return GetTypenameRTTI<void>();}
inline TypeCls AsVoidTypeCls() {return GetTypenameRTTI<void>().GetTypeId();}
#endif


NAMESPACE_UPP_END



#if /*!defined HAVE_MINGW &&*/ defined flagWIN32 && ( defined flagCLANG || defined flagGCC )
	
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
