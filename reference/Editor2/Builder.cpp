#include "Builder.h"
#include "ProjectManager.h"



BuilderMethod::BuilderMethod() {
	
	
}







Builder::Builder() {
	open_project = 0;
	current_builder = -1;
	builder_counter = 0;
	LoadThis();
	methods.Clear();
	/*if (methods.GetCount()==0) {
		
		BuilderMethod& bm = methods.Add();
		bm.id = 0;
		bm.name = "Gcc";
		bm.debugger = "gdb";

		bm.compiler = "clang++";
		bm.bins.Add("/usr/bin");
		bm.bins.Add("/usr/local/bin");
		bm.libs.Add("/usr/lib");
		bm.libs.Add("/usr/local/lib");
		bm.incs.Add("/usr/include");
		bm.incs.Add("/usr/local/include");
		bm.dbgcflags = "-O0 -g2 -ggdb -x c++";
		bm.dbglinkflags = "-lpthread";
		
		BuilderMethod& bm2 = methods.Add();
		bm.id = 1;
		bm2.type = BUILDER_NDLESS;
		bm2.name = "Ndless";
		bm2.debugger = "gdb";
		bm2.compiler = "arm-none-eabi-g++";
		bm2.bins.Add("/home/sblo/Ndless/ndless-sdk/toolchain/install/bin/");
		
		bm2.incs.Add("/home/sblo/Ndless/ndless-sdk/include");
		bm2.incs.Add("/home/sblo/Ndless/ndless-sdk/include/freetype2");
		bm2.incs.Add("/home/sblo/Ndless/ndless-sdk/toolchain/newlib-2.2.0/newlib/libc/include");
		bm2.incs.Add("/home/sblo/Ndless/ndless-sdk/toolchain/install/arm-none-eabi/sys-include");
		bm2.incs.Add("/home/sblo/Ndless/ndless-sdk/toolchain/install/arm-none-eabi/include");
		bm2.incs.Add("/home/sblo/Ndless/ndless-sdk/toolchain/install/arm-none-eabi/include/c++/4.9.2");
		bm2.incs.Add("/home/sblo/Ndless/ndless-sdk/toolchain/install/arm-none-eabi/include/c++/4.9.2/arm-none-eabi");
		bm2.incs.Add("/home/sblo/Ndless/ndless-sdk/toolchain/install/lib/gcc/arm-none-eabi/4.9.2/include");
		//bm2.incs.Add("W:\\ndless\\ndless\\include");
		
		//bm2.libs.Add("W:\\ndless\\ndless\\lib");
		bm2.libs.Add("/home/sblo/Ndless/ndless-sdk/lib");
		bm2.libs.Add("/home/sblo/Ndless/ndless-sdk/toolchain/install/arm-none-eabi/lib");
		
		//bm2.dbgcflags		= "  -O0 --debug -ggdb -g2  -mcpu=arm926ej-s -D flagSDL -D _TINSPIRE -D _LDBL_EQ_DBL -fuse-ld=gold -fno-use-cxa-atexit -D _TINSPIRE -D _LDBL_EQ_DBL -fuse-ld=gold ";
		bm2.dbgcflags		= "  -O2 -mcpu=arm926ej-s -D flagSDL -D _TINSPIRE -D _LDBL_EQ_DBL -fuse-ld=gold -fno-use-cxa-atexit -D _TINSPIRE -D _LDBL_EQ_DBL -fuse-ld=gold ";
		//bm2.dbglinkflags	= "  -O0 --debug -ggdb -g2  -mcpu=arm926ej-s -D flagSDL -lSDL -D _TINSPIRE -D _LDBL_EQ_DBL  -D _POSIX_THREADS -fuse-ld=gold -Wl,--nspireio ";
		bm2.dbglinkflags	= "  -O2 -mcpu=arm926ej-s -D flagSDL -lSDL -D _TINSPIRE -D _LDBL_EQ_DBL  -D _POSIX_THREADS -fuse-ld=gold -Wl,--nspireio ";
		
		BuilderMethod& gc = methods.Add();
		gc.id = 2;
		gc.name = "Calc";
		gc.type = BUILDER_GRAPHCALC;
		
		
		
		
		builder_counter = 3;
		
	}*/
}

int Builder::FindBuilder(int builder_id) {
	for(int i = 0; i < methods.GetCount(); i++) {
		BuilderMethod& bm = methods[i];
		if (bm.id == builder_id)
			return i;
	}
	return -1;
}

void Builder::StoreThis() {
	StoreToFile(*this, ConfigFile("Builders.bin"));
}

void Builder::LoadThis() {
	LoadFromFile(*this, ConfigFile("Builders.bin"));
}

int Builder::GetTotalCompileFiles() {
	Package& p = open_project->GetOpenPackage();
	int out = GetPackageCompileFiles(p);
	int pkg_count = open_project->GetOpenUsedPackageCount();
	for(int i = 0; i < pkg_count; i++) {
		Package& p = open_project->GetOpenUsedPackage(i);
		out += GetPackageCompileFiles(p);
	}
	return out;
}

int Builder::GetPackageCompileFiles(Package& p) {
	int out = 0;
	for(int i = 0; i < p.files.GetCount(); i++) {
		PackageFile& pf = p.files[i];
		String ext = GetFileExt(pf.name);
		if (!pf.IsCompiled(GetObjectPath(p, pf)) &&
				(ext == ".cpp" || ext == ".c") ) 
					out++;
	}
	return out;
}

int Builder::CompileProject(Project& prj) {
	open_project = &prj;
	Package& p = prj.GetOpenPackage();
	
	// Check builder method, set default if invalid
	bid = FindBuilder(builder);
	if (bid == -1) {
		Log("", "Bad builder");
		return -1;
	}
	
	Log("Builder","Using " + methods[bid].name);
	
	// Get total package files to compile
	total = GetTotalCompileFiles() + 1; // 1 for linking, looks nicer
	actual = 0;
	WhenProgress(actual, total);
	
	// Open project
	int r = Compile(p);
	if (r) return r;
	
	
	int pkg_count = prj.GetOpenUsedPackageCount();
	for(int i = 0; i < pkg_count; i++) {
		Package& p = prj.GetOpenUsedPackage(i);
		r = Compile(p);
		if (r) return r;
	}
	return 0;
}

int Builder::Compile(Package& p) {
	Log("Package " + p.name, "Compiling files");
	for(int i = 0; i < p.files.GetCount(); i++) {
		PackageFile& pf = p.files[i];
		String ext = GetFileExt(pf.path);
		if (ext != ".cpp" && ext != ".c") continue;
		if (!pf.IsCompiled(GetObjectPath(p, pf))) {
			Log("Package " + p.name, "Compiling: " + pf.path);
			int r = Compile(p, pf);
			if (r) return r;
		} else {
			Log("Package " + p.name, "Compiled already: " + pf.path);
		}
	}
	return 0;
}

inline void AddInclude(String& s, String path) {s += " -I\"" + path + "\"";}

int Builder::Compile(Package& pkg, PackageFile& pf) {
	ProjectManager& pman = GetProjectManager();
	
	//Log(pf.name, "Compiling");
	String content = LoadFile(pf.path);
	hash_t hash = content.GetHashValue();
	hash_t compiled_hash;
	
	GetCompiledHash(pf.path, &compiled_hash);
	
	String obj_path = GetObjectPath(pkg, pf);
	
	if (hash == compiled_hash && FileExists(obj_path)) {
		// Already compiled (not checking object file though) TODO: rethink checking the hash of the object file
		//Log("Already compiled", pf.path);
		actual++;
		WhenProgress(actual, total);
		return 0;
	}
	
	String dir = GetFileDirectory(obj_path);
	LOG("File directory: " << dir);
	int max_depth = 5;
	for (int j = 0; !DirectoryExists(dir) && j < max_depth; j++){
		String d = dir;
		for(int i = 0; i < max_depth; i++) {
			RealizeDirectory(d);
			int a = d.ReverseFind(DIR_SEPS);
			if (a == -1) break;
			d = d.Left(a);
			LOG(i << ": " << d);
		}
	}
	
	// Very weird bug in windoze
	if (!DirectoryExists(dir))
		Panic("fail to create directory: " + dir);
	
	//String cmd = "c++ -c  -I"W:\svn" -I"W:\upp\uppsrc" -I"W:\TDM-GCC-32\include" -I"C:/upp/out/svn/IDE/MINGW.Debug.Debug_Full.Gui.Main.Mt.Sse2" -DflagGUI -DflagMT -DflagSSE2 -DflagMAIN -DflagGCC -DflagDEBUG -DflagDEBUG_FULL -DflagBLITZ -DflagWIN32 -mthreads -
	String cmd, out;
	
	BuilderMethod& bm = methods[bid];
	
	String exe;
	for(int i = 0; i < bm.bins.GetCount(); i++) {
		exe = AppendFileName(bm.bins[i], bm.compiler);
		LOG(exe);
		if (FileExists(exe)) break;
		exe.Clear();
	}
	
	if (!exe.GetCount()) {
		Log("Compiler", "Executable not found: " + bm.compiler + " (set path)");
		return 1;
	}
	
	Assembly& assembly = open_project->GetOpenAssembly();
	
	cmd = exe + " -c ";
	Vector<String> nests = assembly.GetNests();
	for(int i = 0; i < nests.GetCount(); i++)
		AddInclude(cmd, nests[i]);
	for(int i = 0; i < bm.incs.GetCount(); i++) 
		AddInclude(cmd, bm.incs[i]);
	
	
	if (bm.type == BUILDER_GCC)
		cmd += " -DflagPOSIX";
	
	if (bm.type == BUILDER_NDLESS)
		cmd += " -DflagNDLESS";
	

	if (1) {
		cmd += " -D_DEBUG";
		cmd += " " + bm.dbgcflags;
	} else {
		
	}
	
	cmd += " \"" + pf.path + "\"";
	cmd += " -o \"" + obj_path + "\"";
	LOG(cmd);
	Cout() << cmd << "\n";
	
	
	Sys(cmd, out);
	Log("Compiler", cmd);
	Log("Compiler", out);
	
	int r = ParseCompilerLog(out);
	if (r==0) {
		pf.SetCompiled(obj_path);
		actual++;
		WhenProgress(actual, total);
		WhenCompiled(pf.path, hash);
	}
	return r; 
}

String Builder::GetObjectPath(Package& pkg, PackageFile& pf) {
	//String base = GetHomeDirectory();
	ProjectManager& pman = GetProjectManager();
	Assembly& a = open_project->GetOpenAssembly();
	String obj_dir = AppendFileName(a.output , pkg.nest + DIR_SEPS + pkg.name);
	obj_dir = AppendFileName(obj_dir, GetConfigurationDir());
	RealizeDirectory(obj_dir);
	String obj_path = AppendFileName(obj_dir, GetFileTitle( pf.name ) + ".o");
	return obj_path;
}

int Builder::ParseCompilerLog(const String& log) {
	Vector<String> lines = Split(log, "\n");
	int r = 0;
	for(int i = 0; i < lines.GetCount(); i++) {
		String& line = lines[i];
		if (!lines.GetCount() || line[0] == ' ') continue;
		
		Vector<String> l = Split(line, ": ");
		BuildLogItem item;
		
		if (l.GetCount() < 3) {
			item.message = line;
		} else {
			
			Vector<String> path_vec = Split(l[0], ":"); // Path:row:col
			
			String& type = l[1];
			
			if (path_vec.GetCount()==3) {
				item.path = GetFileName(path_vec[0]);
				item.line = StrInt( path_vec[1] );
				item.col  = StrInt( path_vec[2] );
			} else {
				item.path = l[0];
				item.line = -1;
				item.col  = -1;
			}
			
			
			item.message = line.Mid(line.Find(": "));
		}
		WhenLogItem(item);
	}
	return r;
}

int Sys2(const char *cmd, String& out, bool convertcharset=false)
{
	out.Clear();
	LocalProcess p;
	p.ConvertCharset(convertcharset);
	if(!p.Start2(cmd))
		return -1;
	while(p.IsRunning()) {
		//out.Cat(p.Get());
		Sleep(1); // p.Wait would be much better here!
	}
	//out.Cat(p.Get());
	String s1, s2;
	p.Read2(s1, s2);
	out << s1 << s2;
	return p.GetExitCode();
}

int TmpSys(const char *cmd, String& out, bool convertcharset=false) {
	String tmpfile = "/tmp/tmpcmd";
	for(int i = 0; i < 5; i++) tmpfile << Random(10);
	{
		FileOut tmp(tmpfile);
		tmp << cmd;
	}
	String tmpcmd = "csh -b " + tmpfile;
	LOG(tmpcmd);
	int r = Sys2(tmpcmd, out);
	{
		tmpcmd = "rm " + tmpfile;
		String t;
		Sys(tmpcmd, t);
	}
	return r;
}

int Builder::LinkProject() {
	Vector<String> objs;
	
	Package& p = open_project->GetOpenPackage();	
	// TODO: Clean this... duplicate code
	for(int j = 0; j < p.files.GetCount(); j++) {
		PackageFile& pf = p.files[j];
		String ext = GetFileExt(pf.path);
		if (ext != ".cpp") continue;
		objs.Add(GetObjectPath(p, pf));
	}
	
	int pkg_count = open_project->GetOpenUsedPackageCount();
	for(int i = 0; i < pkg_count; i++) {
		Package& p = open_project->GetOpenUsedPackage(i);
		for(int j = 0; j < p.files.GetCount(); j++) {
			PackageFile& pf = p.files[j];
			String ext = GetFileExt(pf.path);
			if (ext != ".cpp") continue;
			objs.Add(GetObjectPath(p, pf));
		}
	}
	BuilderMethod& bm = methods[bid];
	
	
	String cmd, out;
	
	
	String exe_path_out = GetExeDirectory(p);
	
	RealizeDirectory(exe_path_out);
	if (!DirectoryExists(exe_path_out))
		Panic("fail to create directory: " + exe_path_out);

	
	String exe_out = GetExePath(p);
	
	// TODO: Clean, duplicate...
	String exe;
	for(int i = 0; i < bm.bins.GetCount(); i++) {
		exe = AppendFileName(bm.bins[i], bm.compiler);
		LOG(exe);
		if (FileExists(exe)) break;
		exe.Clear();
	}
	
	if (!exe.GetCount()) {
		Log("Compiler", "Executable not found: " + bm.compiler + " (set path)");
		return 1;
	}
	
	cmd = exe;
	//cmd += " -static ";
	cmd += " -o \"" + exe_out + "\"";
	cmd += " -ggdb -g2 ";
	
	for(int i = 0; i < objs.GetCount(); i++)
		cmd += " \"" + objs[i] + "\" ";
	
	for(int i = 0; i < bm.libs.GetCount(); i++)
		cmd += " -L\"" + bm.libs[i] + "\"";
	
	
	
	if (1) {
		cmd += " " + bm.dbglinkflags;
	} else {
		
	}
	
	
	
	
	LOG(cmd);
	Cout() << cmd << "\n";
	//Log("", cmd);
	
	TmpSys(cmd, out);
	
	int r = ParseLinkerLog(out);
	if (r==0) {
		WhenProgress(1,1);
		Log("Linked", exe_out);
	}
	
	
	if (bm.type == BUILDER_NDLESS) {
		String tnsout = GetFileDirectory(exe_out) + GetFileTitle(exe_out) + ".tns";
		String prgout = GetFileDirectory(exe_out) + GetFileTitle(exe_out) + ".prg.tns";
		cmd = "/home/sblo/Ndless/ndless-sdk/toolchain/install/bin/genzehn --input \"";
		cmd += exe_out + "\" --output \"" + tnsout + "\" --name \"" + GetFileTitle(exe_out) + "\"";
		LOG(cmd); out.Clear();
		Sys(cmd, out);
		if(out.GetCount()) Log("genzehn", out);
		Log("genzehn", tnsout);
		
		cmd = "/home/sblo/Ndless/ndless-sdk/bin/make-prg \"" + tnsout + "\" \"" + prgout + "\"";
		LOG(cmd); out.Clear();
		TmpSys(cmd, out);
		if(out.GetCount()) Log("make-prg", out);
		Log("make-prg", prgout);
	}

	return r; 
	
}

String Builder::GetExeDirectory(Package& p) {
	//String base = GetHomeDirectory();
	//return base + DIR_SEPS + String("kide") + DIR_SEPS + p.nest;
	ProjectManager& pman = GetProjectManager();
	Assembly& a = open_project->GetOpenAssembly();
	return AppendFileName(a.output , GetConfigurationDir());
}

String Builder::GetExePath(Package& p) {
	BuilderMethod& bm = methods[bid];
	if (bm.type == BUILDER_GCC)
		return GetExeDirectory(p) + DIR_SEPS + p.name + ".out";
	else if (bm.type == BUILDER_NDLESS)
		return GetExeDirectory(p) + DIR_SEPS + p.name + ".elf";
	else
		Panic("builder not implemented yet");
	TODO;
	return String();
}

int Builder::ParseLinkerLog(const String& log) {
	Vector<String> lines = Split(log, "\n");
	int r = 0;
	LOG("ParseLinkerLog: " << log);
	for(int i = 0; i < lines.GetCount(); i++) {
		String& line = lines[i];
		if (!line.GetCount() || line[0] == ' ') continue;
		
		int a = line.Find(": ");
		if (a == -1) {
			Log("Linker", line);
			r = 1;
			continue;
		}
		Log("Verbose Linker", line);
		
		String path = line.Mid(0,a);
		String what = line.Mid(a+2);
		
		
		Vector<String> path_vec = Split(path, ":"); // Path:row:col
		if (GetFileExt(path_vec[0]) == ".o") continue; // Linker's "In function..." line
		
		String where;
		if (path_vec.GetCount()==2) where = GetFileName(path_vec[0]) + ":" + path_vec[1];
		else where = path;
		
		CompilerLog(where, what, path_vec[0]);	
		r = 1;	
	}
	return r;
}

String Builder::GetBuildMethod(int i) {
	if (i < 0 || i >= methods.GetCount()) return "";
	i = FindBuilder(i); // "double buffer" requiring id of builder
	if (i == -1) return "";
	return methods[i].name;
}

String Builder::GetBuildMode(int i) {
	switch (i) {
		case MODE_DEBUG:	return "Debug";
		case MODE_OPTIMAL:	return "Optimal";
		case MODE_SPEED:	return "Speed";
		case MODE_SIZE:		return "Size";
		default: return "";
	}
}

int Builder::FindBuildMethod(String s) {
	for(int i = 0; i < methods.GetCount(); i++) {
		if (methods[i].name == s) 
			return methods[i].id;
	}
	return -1;
}



int Builder::FindBuildMode(String s) {
	if (s == "Debug") return 0;
	if (s == "Optimal") return 1;
	if (s == "Speed") return 2;
	if (s == "Size") return 3;
	return -1;
}

String Builder::GetConfigurationDir() {
	String out;
	
	out << GetBuildMethod(builder);
	out << "." << GetBuildMode(mode);
	out << "." << "CONFIG_TODO";
	return out;
}

