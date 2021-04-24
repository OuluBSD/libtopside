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
//#include <errno.h>
#include <io.h> // _findfirst and _findnext set errno iff they return -1 
#include <stdlib.h>
#include <string.h>

/*#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.AccessCache.h>
#include <winrt/Windows.Storage.FileProperties.h>
#include <winrt/Windows.Storage.Pickers.h>
#include <winrt/Windows.Storage.Streams.h>*/


#endif



#include "Core.h"


NAMESPACE_UPP_BEGIN


#if defined flagWIN32

typedef struct DIR DIR;

struct dirent
{
    char *d_name;
};

#ifdef flagUWP
typedef ::_finddata64i32_t _finddata_t;
#endif

DIR           *opendir(const char *);
int           closedir(DIR *);
struct dirent *readdir(DIR *);
void          rewinddir(DIR *);

typedef ptrdiff_t handle_type; /* C99's intptr_t not sufficiently portable */

struct DIR
{
    handle_type         handle; /* -1 for failed rewind */
    _finddata_t         info;
    struct dirent       result; /* d_name null iff first time */
    String              name;  /* null-terminated char string */
};

DIR *opendir(const char *name)
{
    DIR *dir = 0;

    if(name && name[0])
    {
        size_t base_length = strlen(name);
        const char *all = /* search pattern must end with suitable wildcard */
            strchr("/\\", name[base_length - 1]) ? "*" : "/*";
		
		dir = new DIR();
        
        dir->name = name + String(all);
        
        if((dir->handle =
            (handle_type) _findfirst(dir->name.Begin(), &dir->info)) != -1)
        {
            dir->result.d_name = 0;
        }
        else /* rollback */
        {
            delete (dir);
            dir = 0;
        }
    }
    else
    {
        errno = EINVAL;
    }

    return dir;
}

int closedir(DIR *dir)
{
    int result = -1;

    if(dir)
    {
        if(dir->handle != -1)
        {
            result = _findclose(dir->handle);
        }

        delete (dir);
    }

    if(result == -1) /* map all errors to EBADF */
    {
        errno = EBADF;
    }

    return result;
}

struct dirent *readdir(DIR *dir)
{
    struct dirent *result = 0;

    if(dir && dir->handle != -1)
    {
        if(!dir->result.d_name || _findnext(dir->handle, &dir->info) != -1)
        {
            result         = &dir->result;
            result->d_name = dir->info.name;
        }
    }
    else
    {
        errno = EBADF;
    }

    return result;
}

void rewinddir(DIR *dir)
{
    if(dir && dir->handle != -1)
    {
        _findclose(dir->handle);
        dir->handle = (handle_type) _findfirst(dir->name.Begin(), &dir->info);
        dir->result.d_name = 0;
    }
    else
    {
        errno = EBADF;
    }
}

#endif




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
	static MultiStream s;
	return s;
}

Stream& VppLog() {return LogMulti();}

Stream& LogFile() {
	static FileOut fout;
	static StringStream ss; // for early logging
	if (!fout.IsOpen()) {
		String exepath = GetExeFilePath();
		if (exepath.IsEmpty()) {
			return ss;
		}
		else {
			String exe_title = GetFileTitle(exepath);
			String path = ConfigFile(exe_title + ".log");
			int r0 = (path.GetString0()->GetRefs());
			const char* p = path.Begin();
			int r1 = (path.GetString0()->GetRefs());
			RealizeDirectory(GetFileDirectory(path));
			int r2 = (path.GetString0()->GetRefs());
			//cout << path << EOL;
			fout.Open(path);
			int r3 = (path.GetString0()->GetRefs());
			fout << " *** " << GetSysTime().ToString() << " ***" << EOL
				 << " *** " << GetExeFilePath() << " ***" << EOL;
			
			if (ss.GetSize())
				fout << ss.GetResult();
			
			fout.Flush();
			
			int r4 = (path.GetString0()->GetRefs());
			
			int s = r0 + r1 + r2 + r3 + r4;
		}
	}
	return fout;
}

Stream& Cout() {
	static FileOut fout(stdout);
	return fout;
}

Stream& Cerr() {
	static FileOut fout(stderr);
	return fout;
}

Stream& Cin() {
	static FileIn fin(stdin);
	return fin;
}




String exe_path;

void SetExeFilePath(String s) {
	exe_path = s;
}

String GetExeFilePath() {
	return exe_path;
}

String GetHomeDir() {
	#ifdef flagPOSIX
	struct passwd *pw = getpwuid(getuid());
	const char *homedir = pw->pw_dir;
	return homedir;
	#else
	char homedir[2048];
	getenv_s(0, homedir, 2048, "USERPROFILE");
	return homedir;
	#endif
}

extern String config_path;

String ConfigFile(String file_name) {
	if (config_path.GetCount())
		return AppendFileName(config_path, file_name);
	#ifdef flagWIN32
	String dir = GetExeDirFile("");
	#else
	String home_dir = GetHomeDir();
	String upp = AppendFileName(home_dir, ".config");
	upp = AppendFileName(upp, "u++");
	String dir = AppendFileName(upp, GetFileTitle(GetExeFilePath()));
	#endif
	return AppendFileName(dir, file_name);
}

String GetFileName(String path) {
	int i = path.ReverseFind(DIR_SEPS);
	if (i >= 0)
		return path.Mid(i + 1);
	return path;
}

String GetFileTitle(String path) {
	String fname = GetFileName(path);
	int i = fname.ReverseFind(".");
	if (i >= 0)
		return fname.Left(i);
	return fname;
}

String GetFileDirectory(String path) {
	int i = path.ReverseFind("\\");
	int j = path.ReverseFind("/");
	if (i >= 0 && j >= 0)
		return path.Left(max(i, j));
	if (i >= 0)
		return path.Left(i);
	if (j >= 0)
		return path.Left(j);
	return "";
}

void RealizeDirectory(String dir) {
	if (dir.IsEmpty())
		return;
	DIR* d = opendir(dir.Begin());
	if (d) {
	    closedir(d);
	}
	else {
		RealizeDirectory(GetFileDirectory(dir));
		
		#ifdef flagWIN32
		struct stat st = {0};
		
		if (stat(dir.Begin(), &st) == -1) {
			CreateDirectoryA(dir.Begin(), NULL);
		}
		#else
		struct stat st = {0};
		
		if (stat(dir.Begin(), &st) == -1) {
			mkdir(dir.Begin(), 0700);
		}
		#endif
	}
}

void DeleteFile(String path) {
	unlink(path.Begin());
}

String AppendFileName(String a, String b) {
	if (b.IsEmpty()) return a;
	if (a.IsEmpty()) return b;
	bool a_sep = a.ReverseFind(DIR_SEPS) == a.GetCount()-1;
	bool b_sep = b.Find(DIR_SEPS) == 0;
	if (!a_sep) {
		if (!b_sep)
			return a + DIR_SEPS + b;
		else
			return a + b;
	}
	else {
		if (!b_sep)
			return a + b;
		else
			return a + b.Mid(1);
	}
}

String GetParentDirectory(String path, int steps) {
	path = TrimBoth(path);
	String last_known_dir = path;
	for(int i = 0; i < steps; i++) {
		if (path.IsEmpty())
			return last_known_dir;
		
		while (path.Right(1) == DIR_SEPS)
			path = path.Left(path.GetCount()-1);
		
		int j = path.ReverseFind(DIR_SEPS);
		#ifdef flagPOSIX
		if (!j)
			return DIR_SEPS;
		#endif
		if (j <= 0)
			return path;
		
		path = path.Left(j);
		last_known_dir = path;
	}
	return path;
}

String GetFileExt(String path) {
	for(int i = path.GetCount()-1; i >= 0; i--) {
		int chr = path[i];
		if (chr == DIR_SEP)
			return "";
		if (chr == '.')
			return path.Mid(i);
	}
	return "";
}






String LoadFile(String path) {
	FileIn in;
	if (!in.Open(path))
		return "";
	int size = in.GetSize();
	if (!size)
		return String();
	return in.Get(size);
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



























String Join(const Vector<String>& v, String join_str, bool ignore_empty) {
	String out;
	for (const String& s : v) {
		if (s.IsEmpty() && ignore_empty)
			continue;
		if (!out.IsEmpty())
			out << join_str;
		out << s;
	}
	return out;
}




NAMESPACE_UPP_END



#ifdef flagMAIN
using namespace SDK;

CONSOLE_APP_MAIN {
	ASSERT(SignificantBits(0xF) == 4);
	ASSERT(SignificantBits64(0xF) == 4);
	
	CombineHash ch;
	ch.Put(777999777).Put(123).Put64(0xF0F0F0F0F0F0F0F0);
	dword hash = ch;
	ASSERT(hash == 1894504625);
	
	ASSERT(min(1.0f, 2.0f) == 1.0f);
	ASSERT(max(1.0f, 2.0f) == 2.0f);
	ASSERT(fabs(-1.0) == 1.0);
	
	DUMP(Random());
	DUMP(Randomf());
	
	int arr0[10];
	for(int i = 0; i < 10; i++) arr0[i] = i;
	ASSERT(*FindIf(arr0, arr0 + 10, [](int i) -> bool {return i == 6;}) == 6);
	
	// String
	
	
	
	Vector<int> v0;
	for(int i = 0; i < 10; i++) v0.Add(i);
	
	Uuid uuid;
	uuid.New();
	DUMP(uuid);
	
	
	Object value = ParseJSON(
		"{\"menu\": {\n"
		"  \"id\": \"file\",\n"
		"  \"value\": \"File\",\n"
		"  \"popup\": {\n"
		"    \"menuitem\": [\n"
		"      {\"value\": \"New\", \"onclick\": \"CreateNewDoc()\"},\n"
		"      {\"value\": \"Open\", \"onclick\": \"OpenDoc()\"},\n"
		"      {\"value\": \"Close\", \"onclick\": \"CloseDoc()\"}\n"
		"    ]\n"
		"  }\n"
		"}}\n");
	LOG(GetObjectTreeString(value));
	
	
	
	TestShared();
	OrderedLinkedListTest();
	EncryptionTest();
}

#endif
