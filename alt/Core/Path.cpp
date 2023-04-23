#include "Core.h"

#ifdef flagPOSIX
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#endif

#include <sys/stat.h>

#if defined flagUWP
	#include <winrt/Windows.Foundation.h>
	#include <winrt/Windows.Foundation.Collections.h>
	#include <winrt/Windows.UI.Core.h>
#endif

NAMESPACE_UPP_BEGIN

#if defined flagWIN32

typedef struct DIR DIR;

struct dirent
{
    char *d_name;
};

#ifdef flagMSC
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


#endif


#if defined flagWIN32

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


String exe_path;

void SetExeFilePath(String s) {
	exe_path = s;
}

String GetExeTitle() {
	return GetFileName(exe_path);
}

String GetExeFilePath() {
	return exe_path;
}

String GetHomeDirectory() {
	#ifdef flagPOSIX
	struct passwd *pw = getpwuid(getuid());
	String homedir = pw->pw_dir;
	return homedir;
	#elif defined flagUWPREL
	return "ms-appdata:///local/";
	#elif defined flagUWP
	return ConfigFile("");
	#elif defined flagWIN32 && (defined flagMSC || defined flagCLANG)
	char buff[255];
    SHGetSpecialFolderPathA(HWND_DESKTOP, buff, CSIDL_PROFILE, FALSE);
    return buff;
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
	#ifdef flagUWPREL
	String dir = "ms-appdata:///local/";
	#else
	String dir = GetExeDirFile("");
	#endif
	#else
	String home_dir = GetHomeDirectory();
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
	#ifdef flagUWPREL
	TODO
	#elif defined flagUWP
	TODO
	#else
	unlink(path.Begin());
	#endif
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



String sDataPath;
String config_path;


void SetDataPath(String path) {
	sDataPath = path;
}

String GetDataDirectory() {
	if(sDataPath.GetCount())
		return sDataPath;
	#ifdef flagUWPREL
	return "ms-appx://";
	#else
	return GetEnv("UPP_MAIN__");
	#endif
}

String GetDataFile(String filename) {
	if(sDataPath.GetCount())
		return AppendFileName(sDataPath, filename);
	#ifdef flagUWPREL
	return AppendFileName("ms-appx://", filename);
	#else
	String s = GetEnv("UPP_MAIN__");
	return s.GetCount() ? AppendFileName(s, filename) : GetExeDirFile(filename);
	#endif
}

bool FileExists(String path) {
	#ifdef flagWIN32
	#if defined flagMSC || defined flagCLANG
	
	#if defined flagUWP
	#if defined flagUWPREL
	ASSERT(path.GetCount() < 2 || path[1] != ':');
	path = "ms-appx://" + path;
	#endif
	DWORD dwAttrib = GetFileAttributes(path.ToWString().Begin());
	return (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
	#else
	return PathFileExistsA(path.Begin());
	#endif
	
	#else
	struct stat stat_info;
	if (stat(path.Begin(), &stat_info) != 0)
		return false;
	return true;
	#endif
	#else
	return access( path.Begin(), F_OK ) != -1;
	#endif
}

bool DirectoryExists(String path) {
	#ifdef flagWIN32
	#ifdef flagUWPREL
	ASSERT(path.GetCount() < 2 || path[1] != ':');
	path = "ms-appx://" + path;
	#endif
	#ifdef flagUWP
	DWORD dwAttrib = GetFileAttributes(path.ToWString().Begin());
	#else
	DWORD dwAttrib = GetFileAttributes(path.Begin());
	#endif
	return (dwAttrib != INVALID_FILE_ATTRIBUTES && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
	#else
	DIR* dir = opendir(path.Begin());
	if (dir) {
	    closedir(dir);
	    return true;
	}
	return false;
	#endif
}


FindFile::FindFile() {
	
}

void FindFile::UpdateFiles() {
	files.SetCount(0);
	DIR *d;
	struct dirent *dir;
	d = opendir(dir_path.Begin());
	if (d) {
		while ((dir = readdir(d)) != NULL) {
			if (strncmp(dir->d_name, ".", 2) == 0 || strncmp(dir->d_name, "..", 3) == 0)
				continue;
			files.Add(dir->d_name);
		}
		closedir(d);
	}
}

bool FindFile::Search(String path) {
	dir_path = GetFileDirectory(path);
	UpdateFiles();
	
	String fname = GetFileName(path);
	ASSERT(!fname.IsEmpty());
	if (fname.IsEmpty())
		return false;
	
	Vector<String> parts = Split(fname, "*", false);
	ASSERT_(parts.GetCount() <= 2, "regex pattern matching not implemented yet");
	
	pre = parts[0];
	post = parts.GetCount() >= 2 ? parts[1] : String();
	i = -1;
	return Next();
}


bool FindFile::Next() {
	while (++i < files.GetCount()) {
		const String& f = files[i];
		if (f.Left(pre.GetCount()) == pre && f.Right(post.GetCount()) == post)
			break;
	}
	return i < files.GetCount();
}

bool FindFile::IsDirectory() const {
	const String& f = files[i];
	return DirectoryExists(f);
}

String FindFile::GetPath() const {
	return AppendFileName(dir_path, files[i]);
}

String FindFile::GetName() const {
	return files[i];
}


NAMESPACE_UPP_END
