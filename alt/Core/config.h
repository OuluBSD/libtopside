#ifndef _Core_config_h_
#define _Core_config_h_

#define LIBTOPSIDE 1

#if __MINGW32__
	#define HAVE_MINGW 1
#endif


#if __GNUC__

	#define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)

	#define COMPILER_GCC 1
	
	#ifdef __clang__
	#define COMPILER_CLANG 1
	#endif
	
	#define UNREACHABLE __builtin_unreachable()
	
	#define GLEW_STATIC 1
	#define GLEW_INCLUDE <GL/glew.h>
	
	#if defined(__WIN32) || defined(_WIN32) || defined(WIN32)
		#define COMPILER_MINGW 1
		#define PLATFORM_WIN32 1
		#undef  WINVER
		#undef  _WIN32_WINNT

		#ifdef flagWIN10
			#define _WIN32_WINNT   _WIN32_WINNT_WIN10
			#undef NTDDI_VERSION
			#define NTDDI_VERSION   NTDDI_WIN10_19H1
		#elif defined flagWINXP
			#define _WIN32_WINNT   _WIN32_WINNT_WINXP
		#else
			#define _WIN32_WINNT   _WIN32_WINNT_VISTA
			#undef NTDDI_VERSION
			#define NTDDI_VERSION   NTDDI_VISTA
		#endif
	#endif

	#if __unix || __unix__ || __APPLE__
		#define PLATFORM_POSIX 1
		
		#if __linux
			#define PLATFORM_LINUX 1
			#if __ANDROID__
				#define PLATFORM_ANDROID 1
			#else
				#define PLATFORM_POSIX_DESKTOP 1
				#define flagPOSIXDESKTOP 1
			#endif
		// zvzv add
		// __linux is undef on APPLE MACOSX, MACOSX has BSD stuff
		#elif __APPLE__
			// zvzv note
			// s/b MACOSX
			#ifdef flagX11
				#define PLATFORM_OSX11 1
				#define flagNOGTK
			#else
				#define PLATFORM_COCOA 1
			#endif
			#define PLATFORM_BSD 1
			#define PLATFORM_MACOS 1
			#define PLATFORM_OSX 1
			#ifndef flagUSEMALLOC
				#define STD_NEWDELETE
			#endif
		#else
			// zvzv mod
			// was: #if __FreeBSD__ || __OpenBSD__ || __NetBSD__ || __APPLE__
			#if __FreeBSD__ || __OpenBSD__ || __NetBSD__ || __DragonFly__
				#define PLATFORM_BSD 1
				#if __FreeBSD__
					#define PLATFORM_FREEBSD 1
					#define PLATFORM_POSIX_DESKTOP 1
					#define flagPOSIXDESKTOP 1
				#endif
				#if __OpenBSD__
					#define PLATFORM_OPENBSD 1
				#endif
				#if __NetBSD__
					#define PLATFORM_NETBSD 1
				#endif
				#if __DragonFly__
					#define PLATFORM_DRAGONFLY 1
				#endif
			#elif __sun
				#define PLATFORM_SOLARIS 1
			#elif EMSCRIPTEN
				#define PLATFORM_EMSCRIPTEN 1
			#else
				#error Unknown OS
			#endif
		#endif
	#endif
	
	#if  __x86_64
		#undef  _AMD64_
		#define CPU_LE 1
		#define CPU_LITTLE_ENDIAN 1
		#define CPU_UNALIGNED 1
		#define CPU_X86 1
		#define CPU_64 1
		#define CPU_AMD64 1
		#define CPU_SSE2 1
		#define CPU_IA64 1
		#define _AMD64_ 1
	#elif __i386 || __i386__ || i386
		#define CPU_LE 1
		#define CPU_LITTLE_ENDIAN 1
		#define CPU_UNALIGNED 1
		#define CPU_X86 1
		#define CPU_32 1
		#define CPU_IA32 1
		#define CPU_SSE2 1
		#define _X86_ 1
	#elif __sparc  // ToDo!
		#define CPU_32 1
		#define CPU_SPARC 1
		#define CPU_BE 1
		#define CPU_BIG_ENDIAN 1
		#define CPU_ALIGNED 1
	#elif __aarch64__
		#define CPU_64 1
		#define CPU_ARM 1
		#define CPU_LE 1
		#define CPU_LITTLE_ENDIAN 1
		#define CPU_UNALIGNED 1
		#define _ARM_ 1
	#elif __arm__
		#define CPU_32 1
		#define CPU_ARM 1
		#ifdef __ARM_BIG_ENDIAN
			#define CPU_BE 1
			#define CPU_BIG_ENDIAN 1
		#else
			#define CPU_LE 1
			#define CPU_LITTLE_ENDIAN 1
		#endif
		#ifdef __ARM_FEATURE_UNALIGNED
			#define CPU_UNALIGNED 1
		#else
			#define CPU_ALIGNED 1
		#endif
		#ifdef __ARM_NEON
			#define CPU_NEON 1
		#endif
	#elif __bfin
		#define CPU_32 1
		#define CPU_BLACKFIN
		#define CPU_LE 1
		#define CPU_LITTLE_ENDIAN 1
		#define CPU_ALIGNED 1
		#define _HAVE_NO_STDWSTRING 1
		//BF toolchain has no support for __thread (TLS), so U++ Heap not possible
		#define flagUSEMALLOC
	#elif __wasm__
		#define CPU_WASM 1
		#define CPU_32 1
		#define CPU_LE 1
		#define CPU_LITTLE_ENDIAN 1
		#define CPU_ALIGNED 1
	#else
		#error Unknown CPU architecture
	#endif
#endif

#ifdef _MSC_VER
	#define COMPILER_MSC 1
	#if _MSC_VER <= 1300
		#error  MSC 6.0 not supported anymore
	#endif
	#pragma warning(disable: 4786)
	#define _CRT_SECURE_NO_DEPRECATE 1 // we really need strcpy etc. to work with MSC 8.0
	
	#define PLATFORM_WIN32 1

	#define CPU_LE 1
	#define CPU_LITTLE_ENDIAN 1
	#define CPU_UNALIGNED 1
	#define CPU_X86 1
	
	#define UNREACHABLE __assume(0)
	
	#if 0
		#define GLEW_INCLUDE <ports/glew/glew.h>
		#define GLEW_STATIC 1
	#else
		#define GLEW_INCLUDE <GL/glew.h>
	#endif
	
	#ifdef _WIN64
		#define PLATFORM_WIN64 1
		#define CPU_64 1
		#define CPU_AMD64 1
		#define CPU_SSE2 1
		#define CPU_IA64 1
		#define _AMD64_ 1
	#else
		#define CPU_32 1
		#define CPU_IA32 1
		#define CPU_SSE2 1
		#define _X86_ 1
	#endif
	
	#ifdef flagUWP
		#define _UNICODE         1
		#define  UNICODE         1
		#define _WIN32_WINNT    _WIN32_WINNT_WIN10
		#if WINAPI_FAMILY != WINAPI_FAMILY_APP
			#define  WINAPI_FAMILY   WINAPI_FAMILY_APP
		#endif
		#define  __WRL_NO_DEFAULT_LIB__   1
		#undef   NTDDI_VERSION
		#define  NTDDI_VERSION   NTDDI_WINBLUE
	#elif defined flagWIN10
		#define _WIN32_WINNT    _WIN32_WINNT_WIN10
		#undef   NTDDI_VERSION
		#define  NTDDI_VERSION   NTDDI_WIN10_19H1
	#elif defined flagWINXP
		#define _WIN32_WINNT    _WIN32_WINNT_WINXP
	#else
		#define  NTDDI_VERSION   NTDDI_VISTA
		#define _WIN32_WINNT    _WIN32_WINNT_VISTA
	#endif
	
#endif

#ifdef  flagCLR
	#define flagUSEMALLOC
	#define STD_NEWDELETE
#endif

#if __cplusplus >= 201100
	#define CPP_11
#endif

#if _MSC_VER >= 1900 // MSC from VS2015 is good enough C++11 compiler...
	#define CPP_11
#endif

#if defined flagUWP && defined flagRELPKG
	#define UWPREL 1
	#define flagUWPREL 1
#endif



#ifdef flagUWP
	#ifndef WINAPI_FAMILY
		#define WINAPI_FAMILY WINAPI_FAMILY_APP
	#endif
#endif



#endif
