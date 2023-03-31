#ifndef _Core_Path_h_
#define _Core_Path_h_

NAMESPACE_UPP_BEGIN


void SetExeFilePath(String s);
void SetGuiInstance(void* instance);
void* GetGuiInstance();
String GetExeFilePath();
String GetHomeDirectory();
String ConfigFile(String file_name);
String GetFileName(String path);
String GetFileTitle(String path);
String GetFileDirectory(String path);
String AppendFileName(String a, String b);
String GetParentDirectory(String path, int steps=1);
String GetFileExt(String path);
void RealizeDirectory(String dir);
void DeleteFile(String path);

class FindFile {
	Vector<String> files;
	String dir_path, pre, post;
	int i = 0;
	
	void UpdateFiles();
	
public:
	typedef FindFile CLASSNAME;
	FindFile();
	
	bool Search(String path);
	bool Next();
	
	bool IsDirectory() const;
	String GetPath() const;
	String GetName() const;
};

void SetDataPath(String path);
String GetDataDirectory();
String GetDataFile(String filename);
bool FileExists(String path);
bool DirectoryExists(String path);
String GetExeDirFile(String filename);

NAMESPACE_UPP_END

#endif
