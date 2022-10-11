#ifndef _SoftSynth_Common_h_
#define _SoftSynth_Common_h_


#if COMPILER_GCC || COMPILER_CLANG
	#define ALIGNED_PRE(x)
	#define ALIGNED_CACHE_PRE
	#define ALIGNED_POST(x) __attribute__((aligned(x)))
	#define ALIGNED_CACHE_POST ALIGNED_POST(64)
	#define NOINLINE __attribute__((noinline))
	#define ASSUME_ALIGNED(x, align) __builtin_assume_aligned(x, align)
#elif COMPILER_MSC
	#define ALIGNED_PRE(x) __declspec(align(x))
	#define ALIGNED_CACHE_PRE ALIGNED_PRE(64)
	#define ALIGNED_POST(x)
	#define ALIGNED_CACHE_POST
	#define NOINLINE __declspec(noinline)
	#define ASSUME_ALIGNED(x, align) x
#else
	#define ALIGNED_PRE(x)
	#define ALIGNED_CACHE_PRE
	#define ALIGNED_POST(x)
	#define ALIGNED_CACHE_POST
	#define NOINLINE
	#define ASSUME_ALIGNED(x, align) x
#endif

#define ALIGNEDVAR(x) ALIGNED_CACHE_PRE x ALIGNED_CACHE_POST
#undef M_PIf
#define M_PIf 3.14159265359f

#define INV_FACTORIAL_3_2PIPOW3 ((1.0f / 6.0f) * (2.0f * M_PIf) * (2.0f * M_PIf) * (2.0f * M_PIf))
#define INV_FACTORIAL_5_2PIPOW5 ((1.0f / 120.0f) * (2.0f * M_PIf) * (2.0f * M_PIf) * (2.0f * M_PIf) * (2.0f * M_PIf) * (2.0f * M_PIf))
#define INV_FACTORIAL_7_2PIPOW7 ((1.0f / 5040.0f) * (2.0f * M_PIf) * (2.0f * M_PIf) * (2.0f * M_PIf) * (2.0f * M_PIf) * (2.0f * M_PIf) * (2.0f * M_PIf) * (2.0f * M_PIf))

#define FRAMES_PER_LFO 32


#endif
