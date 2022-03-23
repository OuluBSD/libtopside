#ifndef _ParallelMach_Util_h_
#define _ParallelMach_Util_h_

NAMESPACE_PARALLEL_BEGIN

String RealizeEonFile(String path);

#if defined flagDEBUG && defined flagDEBUG_RT
	#define HAVE_SCRIPTLOADER_MACHVER	1
#else
	#define HAVE_SCRIPTLOADER_MACHVER	0
#endif


#ifdef flagDEBUG
	#define DEFAULT_AUDIO_QUEUE_SIZE	10
#else
	#define DEFAULT_AUDIO_QUEUE_SIZE	4
#endif


#if HAVE_SCRIPTLOADER_MACHVER

#define MACHVER_FWDFN_LIST \
	MACHVER_FWD_FN(TerminalTest) \
	MACHVER_FWD_FN(SearchNewSegment) \
	MACHVER_FWD_FN(ScriptLoopLoaderForwardBeginning) \
	MACHVER_FWD_FN(ScriptLoopLoaderForwardRetry) \
	MACHVER_FWD_FN(ScriptLoopLoaderForwardSides) \


#define MACHVER_FWD_FN(x) \
	void MachineVerifier_OnEnter##x(size_t call_id); \
	void MachineVerifier_OnLeave##x(size_t call_id);
MACHVER_FWDFN_LIST
#undef MACHVER_FWD_FN

#define MACHVER_ENTER(fn)		{static byte __; Parallel::MachineVerifier_OnEnter##fn((size_t)&__);}
#define MACHVER_LEAVE(fn)		{static byte __; Parallel::MachineVerifier_OnLeave##fn((size_t)&__);}
#define MACHVER_STATUS(fn, ptr)	{static byte __; Parallel::MachineVerifier_On##fn(ptr);}


void MachineVerifier_OnLoopLoader_Status(ScriptLoopLoader* ll);
void MachineVerifier_OnLoopLoader_RealizeAtoms(ScriptLoopLoader* ll);
void MachineVerifier_OnLoopLoader_AtomLinked(ScriptLoopLoader* ll);
void MachineVerifier_OnLoopLoader_SearchNewSegment(ScriptLoopLoader* ll);

#else

#define MACHVER_FWDFN_LIST
#define MACHVER_ENTER(fn)
#define MACHVER_LEAVE(fn)
#define MACHVER_STATUS(fn, ptr)

#endif

NAMESPACE_PARALLEL_END

#endif
