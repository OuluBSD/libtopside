#ifndef _Editor_Builder_h_
#define _Editor_Builder_h_

#include <Core/Core.h>
using namespace UPP;

#include "Project.h"

struct BuildLogItem {
	String message, path;
	int line, col;

};

enum {BUILDER_GCC, BUILDER_OWC, BUILDER_CLANG, BUILDER_NDLESS, BUILDER_FENIX, BUILDER_GRAPHCALC};

struct BuilderMethod : public Moveable<BuilderMethod> {
	int type;
	String name, compiler, debugger, dbgcflags, dbglinkflags, cflags, linkflags;
	bool isdefault;
	int id;
	Vector<String> bins, libs, incs;
	
	BuilderMethod();
	void SetDefault(bool b) {isdefault = b;}
	void Serialize(Stream& s) {
		s % name % type % compiler % debugger % dbgcflags % dbglinkflags % cflags % linkflags % isdefault % id % bins % libs % incs;}
	void SetId(int i) {id = i;}
	
};

class Builder {
	// Current
	int builder, mode, bid;
	int total, actual;
	Project* open_project;
	
	
	String GetObjectPath(Package& p, PackageFile& pf);
public:
	enum {MODE_DEBUG, MODE_OPTIMAL, MODE_SPEED, MODE_SIZE};
	
	Array<BuilderMethod> methods;
	int builder_counter;
	int current_builder;
	
	void SetCurrentBuilder(int i) {builder = i;}
	void SetCurrentMode(int i) {mode = i;}
	
	int FindBuilder(int builder_id);
	BuilderMethod& GetBuilder(int builder_id) {return methods[FindBuilder(builder_id)];}
	BuilderMethod& GetCurrentBuilder() {return methods[current_builder];}
	int GetBuilderMethodCount() {return methods.GetCount();}
	
	Builder();
	void StoreThis();
	void LoadThis();
	
	
	int CompileProject(Project& prj);
	int Compile(Package& p);
	int Compile(Package& pkg, PackageFile& pf);
	int ParseCompilerLog(const String& log);
	int ParseLinkerLog(const String& log);
	int GetTotalCompileFiles();
	int GetPackageCompileFiles(Package& p);
	int LinkProject();
	
	bool HasCurrentBuilder() {return current_builder >= 0 && current_builder < methods.GetCount();}
	
	Callback2<String, String> Log;
	Callback3<String, String, String> CompilerLog;
	Callback2<int, int> WhenProgress;
	Callback2<String, unsigned> WhenCompiled;
	Callback2<String, unsigned*> GetCompiledHash;
	Callback1<BuildLogItem> WhenLogItem;
	
	String GetExePath(Package& p);
	String GetExeDirectory(Package& p);
	
	String GetBuildMethod(int i);
	String GetBuildMode(int i);
	int FindBuildMethod(String s);
	int FindBuildMode(String s);
	
	String GetConfigurationDir();
	
	void Serialize(Stream& s) {s % methods % builder_counter;}
};


inline Builder& GetBuilder() {return Single<Builder>();}

#endif
