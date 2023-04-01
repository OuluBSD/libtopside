#include <stdio.h>

#if defined flagWIN32 && defined flagMSC
	#include <corecrt_io.h>
#endif

#ifdef flagPOSIX
	#include <sys/types.h>
	#include <dirent.h>
	#include <unistd.h>
	#include <sys/types.h>
	#include <pwd.h>
#endif

#include <sys/stat.h>


#ifdef flagWIN32
	#define _WINSOCKAPI_
	#include <windows.h>
	#include <fileapi.h>
	#include <io.h>
	#include <stdlib.h>
	#include <string.h>
#endif


#include "Core.h"


NAMESPACE_UPP_BEGIN






FileIn cin(stdin);
FileOut cout(stdout), cerr(stderr);

void LogCString(const char* c) {
	LOG(c);
}

void Panic(String s) {
	LOG(" *** Panic: " + s + " ***");
	Panic();
}

void Panic() {
#ifdef PLATFORM_POSIX
	signal(SIGILL, SIG_DFL);
	signal(SIGSEGV, SIG_DFL);
	signal(SIGBUS, SIG_DFL);
	signal(SIGFPE, SIG_DFL);
#endif
	
#ifdef flagDEBUG
	__BREAK__;
#endif
	abort();
}

void Panic(const char* s) {
	LOG(" *** Panic: " << s << " ***");
	Panic();
}

void Assert(bool b, String s) {
	if (!b)
		Panic(s);
}
void AssertFalse(bool b, String s) {
	if (b)
		Panic(s);
}



String ToUpper(const String& s) {
	StringStream out;
	for(int i = 0; i < s.GetCount(); i++)
		out.Put(ToUpper(s[i]));
	return out.GetResult();
}

String ToLower(const String& s) {
	StringStream out;
	for(int i = 0; i < s.GetCount(); i++)
		out.Put(ToLower(s[i]));
	return out.GetResult();
}

WString ToUpper(const WString& s) {
	TODO_
}

WString ToLower(const WString& s) {
	TODO_
}


#ifdef __GNUC__
typedef __attribute__((__may_alias__)) size_t WT;
#define WS (sizeof(WT))
#endif

void MemoryMoveSlow(void* dst, const void* src, int n) {
	char *d = (char*)dst;
	const char *s = (const char*)src;

	if (d==s) return;
	if ((uintptr_t)s-(uintptr_t)d-n <= -2*n) {
		MemoryCopySlow(d, s, n);
		return;
	}

	if (d<s) {
#ifdef __GNUC__
		if ((uintptr_t)s % WS == (uintptr_t)d % WS) {
			while ((uintptr_t)d % WS) {
				if (!n--) return;
				*d++ = *s++;
			}
			for (; n>=WS; n-=WS, d+=WS, s+=WS) *(WT *)d = *(WT *)s;
		}
#endif
		for (; n; n--) *d++ = *s++;
	} else {
#ifdef __GNUC__
		if ((uintptr_t)s % WS == (uintptr_t)d % WS) {
			while ((uintptr_t)(d+n) % WS) {
				if (!n--) return;
				d[n] = s[n];
			}
			while (n>=WS) n-=WS, *(WT *)(d+n) = *(WT *)(s+n);
		}
#endif
		while (n) n--, d[n] = s[n];
	}
}


MultiStream& LogMulti() {
	MAKE_STATIC(MultiStream, s);
	return s;
}

Stream& VppLog() {return LogMulti();}

Stream& LogFile() {
	MAKE_STATIC(FileOut, fout);
	MAKE_STATIC(StringStream, ss); // for early logging
	if (!fout.IsOpen()) {
		String exepath = GetExeFilePath();
		if (exepath.IsEmpty()) {
			return ss;
		}
		else {
			String exe_title = GetFileTitle(exepath);
			String path = ConfigFile(exe_title + ".log");
			//int r0 = (path.GetString0()->GetRefs());
			//const char* p = path.Begin();
			//int r1 = (path.GetString0()->GetRefs());
			RealizeDirectory(GetFileDirectory(path));
			//int r2 = (path.GetString0()->GetRefs());
			//cout << path << EOL;
			fout.Open(path);
			//int r3 = (path.GetString0()->GetRefs());
			fout << " *** " << GetSysTime().ToString() << " ***" << EOL
				 << " *** " << GetExeFilePath() << " ***" << EOL;
			
			if (ss.GetSize())
				fout << ss.GetResult();
			
			fout.Flush();
			
			//int r4 = (path.GetString0()->GetRefs());
			
			//int s = r0 + r1 + r2 + r3 + r4;
		}
	}
	return fout;
}

Stream& Cout() {
	MAKE_STATIC_(FileOut, fout, stdout);
	return fout;
}

Stream& Cerr() {
	MAKE_STATIC_(FileOut, fout, stderr);
	return fout;
}

Stream& Cin() {
	MAKE_STATIC_(FileIn, fin, stdin);
	return fin;
}






String TrimLeft(String s) {
	if (s.IsEmpty())
		return s;
	String out;
	int begin = s.FindFirstNotOf(" \t\n\r");
	if (begin < 0)
		return "";
	return s.Mid(begin, s.GetCount() - begin);
}

String TrimRight(String s) {
	if (s.IsEmpty())
		return s;
	String out;
	int end = s.ReverseFindFirstNotOf(" \t\n\r");
	if (end < 0)
		return "";
	end++;
	return s.Left(end);
}

String TrimBoth(String s) {
	if (s.IsEmpty())
		return s;
	String out;
	int begin = s.FindFirstNotOf(" \t\n\r");
	if (begin < 0)
		return "";
	int end = s.ReverseFindFirstNotOf(" \t\n\r");
	if (end < 0)
		return "";
	end++;
	if (end <= begin)
		return "";
	return s.Mid(begin, end - begin);
}




NAMESPACE_UPP_END

