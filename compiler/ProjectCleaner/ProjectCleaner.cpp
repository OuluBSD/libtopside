#include "ProjectCleaner.h"


NAMESPACE_TOPSIDE_BEGIN


void RecursiveLoad(UppAssemblyData& ass_data, String pkg, int depth=0) {
	if (depth >= 8) {
		LOG("Recursive load went too deep");
		Exit(1);
	}
	
	if (ass_data.FindName(pkg) >= 0)
		return;
	
	UppProject& prj = ass_data.GetProject(pkg);
	
	for(int i = 0; i < prj.GetUseCount(); i++) {
		String use = prj.GetUse(i);
		if (ass_data.FindName(use) < 0)
			RecursiveLoad(ass_data, use, depth+1);
	}
}

void CleanAssembly(String conf_path, String assembly_dir, const Index<String>& pkgs, String output_dir, bool use_cache) {
	if (conf_path.IsEmpty())
		conf_path = ConfigFile("renaming.conf");
	
	String conf_dir = GetFileDirectory(conf_path);
	if (!DirectoryExists(conf_dir)) {
		LOG("Configuration directory doesn't exist: " << conf_dir);
		Exit(1);
	}
	
	LOG("Cleaning assembly:");
	LOG("\tAssembly directory: " << assembly_dir);
	for(String pkg : pkgs) {
		LOG("\tInclude package: " << pkg);
	}
	LOG("\tOutput directory: " << output_dir);
	
	RealizeDirectory(output_dir);
	
	if (!DirectoryExists(output_dir)) {
		LOG("error: output directory doesn't exist");
		return;
	}
	
	
	// Load packages
	UppAssembly ass;
	ass.AddPath(assembly_dir);
	
	UppAssemblyData ass_data(ass);
	Array<UppProject> prjs;
	
	for(String pkg : pkgs) {
		RecursiveLoad(ass_data, pkg);
	}
	
	
	// Load files. Use file cache for faster startup (when --cache flag is used)
	CombineHash hash;
	hash << assembly_dir.GetHashValue();
	for(String pkg : pkgs)
		hash << pkg.GetHashValue();
	uint32 ass_cache_hash = hash;
	String ass_cache_uniq = IntStr64(ass_cache_hash);
	LOG("Persistent file for UppAssemblyCache: " << ass_cache_uniq);
	
	UppAssemblyCache ass_cache(ass_data);
	UppProjectProcessor proc(ass_cache);
	proc.SetPersistent(ConfigFile(ass_cache_uniq + ".bin"));
	proc.WhenProgress << [](int actual, int total) {
		if (actual % 100 == 0) {
			double perc = actual * 100.0 / total;
			LOG(Format("%1n%% loaded", perc));
		}
	};
	proc.WhenLoaded << [](int total) {LOG(Format("%d files loaded in total", total));};
	if (use_cache) {
		if (proc.LoadThis() && !proc.cache.files.IsEmpty()) {
			LOG("Cache file loaded succesfully");
		}
		else {
			proc.cache.Load();
			if (!proc.StoreThis()) {
				LOG("Couldn't store cache to " << proc.persistent_path);
				Exit(1);
			}
		}
	}
	else proc.cache.Load();
	
	int cur_stage = 0;
	#define STAGE for (int once = 0; once < 1 && proc.stage == cur_stage++; once++, proc.stage++, proc.StoreThis())
	
	
	if (0) {
		// Traverse identifiers: references and their targets
		// - functions, classes, typedefs, enums
		// - identifiers
		// - find from "::" in #defines
		STAGE proc.FindReferences();
		
		// Realize identifier dictionary file
		// - load existing rename definition first
		STAGE proc.RealizeConfiguration(conf_path);
		
		// Rename identifiers
		STAGE proc.Process();
	}
	
	// Remove comments
	STAGE proc.EraseComments();
	
	// Remove "#pragma once" made with #defines and #ifdefs
	STAGE proc.EraseDepreacedHeaderOnce();
	
	// Find all used ids in #if and #ifdef statements
	STAGE proc.FindMacroConditionals();
	
	// Find all #defines in all files
	STAGE proc.FindMacroDefinitions();
	
	// Create placeholers for all other #defines than those used in #if and #ifdefs
	STAGE proc.InstallMacroPlaceholder_NonConditionallyUsedDefine();
	
	// Run C++ preprocessor
	STAGE proc.RunStdPreprocessor();
	
	// Restore used #defines to placeholders
	STAGE proc.UninstallMacroPlaceholder_NonConditionallyUsedDefine();
	
	// Find all references to remaining #defines in files
	STAGE proc.FindMacroDefineReferences();
	
	// Remove #defines without any references
	STAGE proc.RemoveUnusedMacros();
	
	// Export packages and file contents
	STAGE proc.Export(output_dir);
	
	// Run astyle
	String astyle_flags = "-A2 -t4 -xn -xc -xl -xk -xV -xt2 -L -xW -w -Y -f -p -xg -H -xe -E -k1 -W1 -y -xj -xf -xh -O -o -xy -xp -xL -z2";
	RunArtisticStyleRecursively(output_dir, astyle_flags);
	
	// Add breaks after "}"
	TODO
	
	
	LOG("Assembly was cleaned successfully.");
}













const char* UppProjectProcessor::placeholder_str = "___phold___";

UppProjectProcessor::UppProjectProcessor(UppAssemblyCache& cache) : cache(cache) {
	ref_cache_dir = ConfigFile("ref_cache");
}

bool UppProjectProcessor::LoadThis() {
	if (!FileExists(persistent_path))
		return false;
	LoadFromFile(*this, persistent_path);
	return true;
}

bool UppProjectProcessor::StoreThis() {
	String dir = GetFileDirectory(persistent_path);
	if (persistent_path.IsEmpty() || !DirectoryExists(dir))
		return false;
	StoreToFile(*this, persistent_path);
	return true;
}

void UppProjectProcessor::EraseComments() {
	for(int i = 0; i < cache.files.GetCount(); i++) {
		if (i % 100 == 0) {
			LOG("EraseComments: " << i << " / " << cache.files.GetCount());
		}
		String path = cache.files.GetKey(i);
		String& content = cache.files[i];
		UppFile& file = files.GetAdd(path);
		
		#if 1
		String tmp_path = AppendFileName(GetFileDirectory(path), "____tmp____.cpp");
		FileOut fout(tmp_path);
		fout << content;
		fout.Close();
		
		String file_cmd = "gcc -fpreprocessed -dD -P -E \"" + tmp_path + "\"";
		content = RunCompiler(file_cmd);
		
		DeleteFile(tmp_path);
		
		#else
		Vector<String> lines = Split(content, "\n");
		for(int i = 0; i < lines.GetCount(); i++) {
			String& line = lines[i];
			int j = line.Find("//");
			if (j >= 0)
				line = line.Left(j);
		}
		content = Join(lines, "\n", false) + "\n";
		
		try {
			CParser p(content);
			p.SkipComments(false);
			while (!p.IsEof()) {
				const char* begin = p.GetPtr();
				if (p.Char2('/', '*')) {
					bool found = false;
					while (!p.IsEof()) {
						if (p.Char2('*', '/')) {
							const char* end = p.GetPtr();
							int begin_i = begin - content.Begin();
							int end_i = end - content.Begin();
							content = content.Left(begin_i) + content.Mid(end_i);
							p.Set(content);
							found = true;
							break;
						}
						else p.PassChar(p.PeekChar());
					}
					if (!found) {
						LOG("error: didn't find end of multiline comment in file " + path);
						break;
					}
				}
				else if (p.IsDouble())
					p.ReadDouble();
				else if (p.IsInt())
					p.ReadInt();
				else
					p.PassChar(p.PeekChar());
			}
		}
		catch (Exc e) {
			LOG(e);
		}
		#endif
	}
}

void UppProjectProcessor::EraseDepreacedHeaderOnce() {
	for(int i = 0; i < cache.files.GetCount(); i++) {
		String path = cache.files.GetKey(i);
		String& content = cache.files[i];
		UppFile& file = files.GetAdd(path);
		file.pragma_once = false;
		
		String ext = GetFileExt(path);
		if (ext == ".h") {
			bool match = false;
			CParser p(content);
			const char* begin = p.GetPtr();
			if (p.Char('#') && p.Id("ifndef") && p.IsId()) {
				String a = p.ReadId();
				if (p.Char('#') && p.Id("define") && p.IsId() ) {
					String b = p.ReadId();
					if (a == b) {
						int end = content.ReverseFind("#endif");
						if (end >= 0) {
							const char* cur = p.GetPtr();
							int chars = cur - begin;
							content = content.Mid(chars, end - chars);
							match = true;
							file.pragma_once = true;
						}
						else {
							LOG("error: Partially matching old-style pragma once in " << path);
						}
					}
				}
			}
			if (verbose && !match) {LOG("Skipping: " << path);}
		}
	}
}

void FindIds(CParser& p, Index<String>& id_list) {
	while (!p.IsEof()) {
		if (p.IsId()) {
			String id = p.ReadId();
			id_list.FindAdd(id);
		}
		else {
			if (p.IsDouble())
				p.ReadDouble();
			else if (p.IsInt())
				p.ReadInt();
			else
				p.PassChar(p.PeekChar());
		}
	}
}

void UppProjectProcessor::FindMacroConditionals() {
	macro_cond_ids.Clear();
	for(int i = 0; i < cache.files.GetCount(); i++) {
		String path = cache.files.GetKey(i);
		String& content = cache.files[i];
		UppFile& file = files.GetAdd(path);
		file.macro_conds.Clear();
		file.macro_cond_ids.Clear();
		
		Vector<String> lines = Split(content, "\n");
		for(String& line : lines) {
			CParser p(line);
			const char* begin = p.GetPtr();
			if (p.Char('#')) {
				if (p.Id("if") || p.Id("ifdef") || p.Id("elif")) {
					p.Id("defined");
					
					Index<String> id_list;
					FindIds(p, id_list);
					if (id_list.GetCount()) {
						UppFile::MacroConditional& cond = file.macro_conds.Add();
						Swap(cond.id_list, id_list);
						for(const String& id : cond.id_list)
							file.macro_cond_ids.FindAdd(id);
					}
				}
			}
		}
		for(String id : file.macro_cond_ids)
			macro_cond_ids.FindAdd(id);
		
		if (verbose && file.macro_cond_ids.GetCount()) {
			LOG("Macro conditional ids: " << path);
			for(int i = 0; i < file.macro_cond_ids.GetCount(); i++) {
				LOG("\t" << i << ": " << file.macro_cond_ids[i]);
			}
		}
	}
}

void UppProjectProcessor::FindMacroDefinitions() {
	macro_def_ids.Clear();
	
	for(int i = 0; i < cache.files.GetCount(); i++) {
		String path = cache.files.GetKey(i);
		String& content = cache.files[i];
		UppFile& file = files.GetAdd(path);
		file.macro_defs.Clear();
		file.macro_def_ids.Clear();
		
		Vector<String> lines = Split(content, "\n");
		int line_i = 0;
		for(String& line : lines) {
			CParser p(line);
			const char* begin = p.GetPtr();
			if (p.Char('#')) {
				if (p.Id("define")) {
					String id = p.ReadId();
					file.macro_def_ids.FindAdd(id);
					macro_def_ids.GetAdd(id, 0);
					UppFile::MacroDefinition& def = file.macro_defs.Add();
					def.key = id;
					def.line = line_i;
					def.is_function = p.Char('(');
					FindIds(p, def.id_list);
				}
			}
			line_i++;
		}
		if (verbose && file.macro_def_ids.GetCount()) {
			LOG("Macro conditional ids: " << path);
			for(int i = 0; i < file.macro_def_ids.GetCount(); i++) {
				LOG("\t" << i << ": " << file.macro_def_ids[i]);
			}
		}
	}
}

void UppProjectProcessor::InstallMacroPlaceholder_NonConditionallyUsedDefine() {
	for(int i = 0; i < cache.files.GetCount(); i++) {
		String path = cache.files.GetKey(i);
		String& content = cache.files[i];
		UppFile& file = files.GetAdd(path);
		
		Vector<String> lines = Split(content, "\n");
		int def_i = 0;
		for (UppFile::MacroDefinition& def : file.macro_defs) {
			// Check simply from global key list (not accurate)
			if (macro_cond_ids.Find(def.key) >= 0 ||
				def.key.Left(10) == "NAMESPACE_") {
				auto& l = lines[def.line];
				def.original_line = l;
				def.placeholder = placeholder_str + IntStr(def_i);
				l = def.placeholder;
			}
			def_i++;
		}
		content = Join(lines, "\n", false) + "\n";
	}
}

String RunCompiler(String cmd) {
	String err_out, out;
	LocalProcess p;
	p.ConvertCharset(true);
	if(!p.Start2(cmd)) {
		LOG("error: couldn't run " << cmd);
		Exit(1);
	}
	String os, es;
	while (p.IsRunning()) {
		p.Read2(os, es);
		out << os;
		err_out << es;
	}
	p.Read2(os, es);
	out << os;
	err_out << es;
	p.Finish(os);
	out << os;
	return out;
}

void UppProjectProcessor::RunStdPreprocessor() {
	TimeStop ts;
	actual = 0;
	total = cache.files.GetCount();
	CoWork co;
	co.SetPoolSize(max<int>(1, CPU_Cores()-2));
	for(int i = 0; i < cache.files.GetCount(); i++)
		co & THISBACK1(RunStdPreprocessorPath, i);
	co.Finish();
	
	LOG("RunStdPreprocessor took " << ts.ToString());
}

void UppProjectProcessor::RunStdPreprocessorPath(int i) {
	String path = cache.files.GetKey(i);
	String& content = cache.files[i];
	UppFile& file = files.GetAdd(path);
	
	String filename;
	for(int i = 0; i < 10; i++)
		filename.Cat('a' + Random('z' - 'a' + 1));
	String tmp_path = AppendFileName(GetFileDirectory(path), filename + ".cpp");
	FileOut fout(tmp_path);
	fout << content;
	fout.Close();
	
	//verbose = 1;
	String file_cmd = "clang++ ";
	for(int i = 0; i < cache.asd.as.GetDirectoryCount(); i++)
		file_cmd << " -I \"" << cache.asd.as.GetDirectory(i) << "\"";
	file_cmd << " -E \"" << tmp_path << "\"";
	if (verbose) {LOG(file_cmd);}
	
	content = RunCompiler(file_cmd);
	DeleteFile(tmp_path);
	
	
	// Change line macros to back to #include
	bool removing = true;
	Vector<String> lines = Split(content, "\n");
	Vector<int> rm_lines;
	rm_lines.Reserve(1000000);
	for(int i = 0; i < lines.GetCount(); i++) {
		String& line = lines[i];
		CParser p(line);
		if (p.Char('#') && p.IsInt()) {
			int line_i = p.ReadInt();
			if (p.IsString()) {
				bool replaced = false;
				String file = p.ReadString();
				if (file == tmp_path) {
					removing = false;
				}
				else if (!removing) {
					for(int i = 0; i < cache.asd.as.GetDirectoryCount(); i++) {
						String dir = cache.asd.as.GetDirectory(i);
						if (file.GetCount() < dir.GetCount()) continue;
						if (strncmp(file, dir, dir.GetCount()) == 0) {
							file = file.Mid(dir.GetCount());
							line = "#include <" + file + ">";
							replaced = true;
							break;
						}
					}
					removing = true;
				}
				if (!replaced)
					rm_lines.Add(i);
			}
		}
		else if (removing)
			rm_lines.Add(i);
	}
	lines.Remove(rm_lines);
	content = Join(lines, "\n", false) + "\n";
	if (verbose && content.GetCount() > 10) {LOG(content);}
	
	
	lock.Enter();
	if (++actual % 100 == 0) {
		LOG("RunStdPreprocessor: " << actual << " / " << total);
	}
	lock.Leave();
}

void UppProjectProcessor::UninstallMacroPlaceholder_NonConditionallyUsedDefine() {
	for(int i = 0; i < cache.files.GetCount(); i++) {
		String path = cache.files.GetKey(i);
		String& content = cache.files[i];
		UppFile& file = files.GetAdd(path);
		
		//bool had = content.Find(placeholder_str) >= 0;
		//if (had) {LOG(content);}
		
		Vector<String> lines = Split(content, "\n");
		for (String& line : lines) {
			if (line.GetCount() >= placeholder_str.GetCount()) {
				if (memcmp(line.Begin(), placeholder_str.Begin(), placeholder_str.GetCount()) == 0) {
					int def_i = StrInt(line.Mid(placeholder_str.GetCount()));
					const UppFile::MacroDefinition& def = file.macro_defs[def_i];
					line = def.original_line;
				}
			}
		}
		content = Join(lines, "\n", false) + "\n";
		
		//if (had) {LOG(content);}
	}
}

void UppProjectProcessor::FindMacroDefineReferences() {
	macro_def_ids.RemoveKey("cosf");
	macro_def_ids.RemoveKey("sinf");
	macro_def_ids.RemoveKey("tanf");
	macro_def_ids.RemoveKey("sqrtf");
	macro_def_ids.RemoveKey("fabsf");
	macro_def_ids.RemoveKey("acosf");
	macro_def_ids.RemoveKey("inline");
	macro_def_ids.RemoveKey("strcmpi");
	macro_def_ids.RemoveKey("dprintf");
	macro_def_ids.RemoveKey("printf");
	macro_def_ids.RemoveKey("isnanf");
	macro_def_ids.RemoveKey("isinff");
    macro_def_ids.RemoveKey("gethostbyname");
    macro_def_ids.RemoveKey("gethostname");
    macro_def_ids.RemoveKey("inet_addr");
    macro_def_ids.RemoveKey("inet_aton");
    macro_def_ids.RemoveKey("inet_ntoa");
    macro_def_ids.RemoveKey("in_addr");
    macro_def_ids.RemoveKey("sockaddr_in");
    macro_def_ids.RemoveKey("sockaddr");
    macro_def_ids.RemoveKey("AF_INET");
    macro_def_ids.RemoveKey("PF_INET");
    macro_def_ids.RemoveKey("htonl");
    macro_def_ids.RemoveKey("ntohl");
    macro_def_ids.RemoveKey("htons");
    macro_def_ids.RemoveKey("ntohs");
    macro_def_ids.RemoveKey("sin_family");
    macro_def_ids.RemoveKey("sin_port");
    macro_def_ids.RemoveKey("sin_addr");
    macro_def_ids.RemoveKey("sin_zero");
    macro_def_ids.RemoveKey("s_addr");
    macro_def_ids.RemoveKey("INADDR_ANY");
    macro_def_ids.RemoveKey("IPPROTO_UDP");
    macro_def_ids.RemoveKey("accept");
    macro_def_ids.RemoveKey("bind");
    macro_def_ids.RemoveKey("closesocket");
    macro_def_ids.RemoveKey("connect");
    macro_def_ids.RemoveKey("getpeername");
    macro_def_ids.RemoveKey("getsockname");
    macro_def_ids.RemoveKey("getsockopt");
    macro_def_ids.RemoveKey("listen");
    macro_def_ids.RemoveKey("recv");
    macro_def_ids.RemoveKey("recvfrom");
    macro_def_ids.RemoveKey("recvmsg");
    macro_def_ids.RemoveKey("select");
    macro_def_ids.RemoveKey("send");
    macro_def_ids.RemoveKey("sendmsg");
    macro_def_ids.RemoveKey("sendto");
    macro_def_ids.RemoveKey("setsockopt");
    macro_def_ids.RemoveKey("shutdown");
    macro_def_ids.RemoveKey("socket");
	
	for(int i = 0; i < cache.files.GetCount(); i++) {
		String path = cache.files.GetKey(i);
		String& content = cache.files[i];
		UppFile& file = files.GetAdd(path);
		file.macro_use.Clear();
		
		try {
			const char* begin = content.Begin();
			CParser p(begin);
			while (!p.IsEof()) {
				if (p.IsId()) {
					String id = p.ReadId();
					int j = macro_def_ids.Find(id);
					if (j >= 0) {
						macro_def_ids[j]++;
						const char* cur = p.GetPtr();
						int cursor = cur - begin;
						UppFile::MacroUse& use = file.macro_use.Add();
						use.id = id;
						use.cursor = cursor;
					}
				}
				else {
					if (p.IsDouble())
						p.ReadDouble();
					else if (p.IsInt())
						p.ReadInt();
					else
						p.PassChar(p.PeekChar());
				}
			}
		}
		catch (Exc e) {
			DUMP(path);
			LOG(content);
			Panic("error: " + e);
		}
	}
}

void UppProjectProcessor::RemoveUnusedMacros() {
	SortByValue(macro_def_ids, StdGreater<int>());
	
	Index<String> unused;
	for(int i = 0; i < macro_def_ids.GetCount(); i++) {
		if (macro_def_ids[i] <= 1) {
			String id = macro_def_ids.GetKey(i);
			unused.Add(id);
		}
	}
	LOG("Found " << unused.GetCount() << " macro keys");
	
	int rem_count = 0;
	for(int i = 0; i < cache.files.GetCount(); i++) {
		String path = cache.files.GetKey(i);
		String& content = cache.files[i];
		UppFile& file = files.GetAdd(path);
		
		Vector<String> lines = Split(content, "\n");
		for(int j = 0; j < lines.GetCount(); j++) {
			String& line = lines[j];
			CParser p(line);
			if (p.Char('#')) {
				if (p.Id("define")) {
					String id = p.ReadId();
					if (unused.Find(id) >= 0) {
						lines.Remove(j--);
						rem_count++;
					}
				}
			}
		}
		content = Join(lines, "\n", false) + "\n";
	}
	LOG("Removed " << rem_count << " macro keys (the rest were removed already with conditional simplification");
}

void UppProjectProcessor::FindReferences() {
	includes.Clear();
	includes.Add("/usr/include");
	includes.Add("/usr/lib/clang/11.0.1/include/");
	for(int i = 0; i < cache.asd.as.GetDirectoryCount(); i++) includes.Add(cache.asd.as.GetDirectory(i));
	
	defines.Clear();
	defines.Add("flagSDL");
	defines.Add("flagHAVE_DIRECT_OPENGL");
    defines.Add("flagCLANG");
    defines.Add("flagDEBUG");
    defines.Add("flagSHARED");
    defines.Add("flagDEBUG_FULL");
    defines.Add("flagPOSIX");
    defines.Add("flagLINUX");
	defines.Add("flagEMU");
    defines.Add("EMU");
    
	RealizeDirectory(ref_cache_dir);
	
	CoWork co;
	co.SetPoolSize(max<int>(1, CPU_Cores()-2));
	
	
	Vector<String> c_paths;
	all_items.Clear();
	for(int i = 0; i < cache.files.GetCount(); i++) {
		if (i % 10 == 0) {
			LOG("RunStdPreprocessor: " << i << " / " << cache.files.GetCount());
		}
		
		String path = cache.files.GetKey(i);
		String ext = GetFileExt(path);
		
		if (ext == ".cpp" || ext == ".cxx" || ext == ".cc" || ext == ".c")
			c_paths.Add(path);
	}
	
	TimeStop ts;
	actual = 0;
	total = c_paths.GetCount();
	for(String path: c_paths)
		co & THISBACK1(FindReferencePath, path);
	co.Finish();
	LOG("Finding references took " << ts.ToString());
	
	for(CodeItem& it : all_items)
		it.RemoveQualTemplate();
	RemoveDuplicates(all_items, CodeItem());
}

void UppProjectProcessor::FindReferencePath(String path) {
	hash_t hash = path.GetHashValue();
	String cache_file = IntStr64(hash) + ".bin";
	String cache_path = AppendFileName(ref_cache_dir, cache_file);
	Vector<CodeItem> items;
	if (!FileExists(cache_path)) {
		CppImportToolFork(path, includes, defines, items);
		Sort(items, CodeItem());
		
		lock.Enter();
		int before_remove = items.GetCount();
		AppendSortedRemoveDuplicateSource(items, all_items, CodeItem());
		LOG("\t" << ++actual << "/" << total << ": " << path << ": added " << items.GetCount() << " items (" << before_remove - items.GetCount() << " duplicates)");
		lock.Leave();
		
		FileOut fout(cache_path);
		fout % items;
	}
	else {
		FileIn fin(cache_path);
		fin % items;
		Sort(items, CodeItem());
		
		lock.Enter();
		int before = all_items.GetCount();
		AppendSortedNoDuplicates(items, all_items, CodeItem());
		int added = all_items.GetCount() - before;
		LOG("\t" << ++actual << "/" << total << ": " << path << ": added " << added << " items (" << items.GetCount() - added << " duplicates)");
		lock.Leave();
		
		ASSERT(added >= 0);
	}
}

void CodeItem::RemoveQualTemplate() {
	/*int a = 0;
	while (1) {
		a = qual_name.Find("<", a);
		if (a < 0)
			break;
		int b = qual_name.Find(">", a+1);
		if (b >= 0) {
			String l = qual_name.Left(a);
			String r = qual_name.Mid(b+1);
			qual_name = l + r;
		}
		else if (qual_name.Mid(a - 8, 8) == "operator") {
			if (qual_name.Mid(a,2) == "<<")
				a += 2;
			else
				a += 1;
		}
		else {
			LOG("error: invalid qualified name " << qual_name);
			break;
		}
	}*/
	int depth = 0;
	int begin = 0;
	for(int i = 0; i < qual_name.GetCount(); i++) {
		if (i + 8 <= qual_name.GetCount()) {
			if (memcmp("operator", qual_name.Begin() + i, 8) == 0) {
				i += 8;
				char chr0 = qual_name[i];
				char chr1 = i+1 < qual_name.GetCount() ? qual_name[i+1] : 0;
				if (chr0 == '<' && chr1 == '<')
					i += 1;
				else if (chr0 == '>' && chr1 == '>')
					i += 1;
				
				continue;
			}
		}
		
		char chr = qual_name[i];
		if (chr == '<') {
			if (!depth)
				begin = i;
			depth++;
		}
		else if (chr == '>') {
			depth--;
			if (!depth) {
				String l = qual_name.Left(begin);
				String r = qual_name.Mid(i+1);
				qual_name = l + r;
				i = begin - 1;
			}
		}
	}
}

void UppProjectProcessor::RealizeConfiguration(String conf_file) {
	LOG("Loaded configuration " << conf_file);
	
	config.SetPath(conf_file);
	config.LoadThis();
	
	bool changes = false;
	for(const CodeItem& ci : all_items) {
		VectorMap<String,String>& renames = config.renames.GetAdd(ci.type);
		int i = renames.Find(ci.qual_name);
		if (i < 0 && ci.qual_name.GetCount()) {
			renames.Add(ci.qual_name);
			changes = true;
		}
	}
	
	SortByKey(config.renames, StdLess<int>());
	for(auto& map : config.renames)
		SortByKey(map, StdLess<String>());
	
	if (changes) {
		config.StoreThis();
		LOG("Stored configuration " << conf_file);
	}
}

void ProjectConfig::StoreThis() {
	FileOut fout(path);
	if (!fout.IsOpen()) {
		LOG("error: couldn't open file " << path);
		return;
	}
	
	SortByKey(renames, StdLess<int>());
	
	for(int i = 0; i < renames.GetCount(); i++) {
		if (i) fout << "\n\n\n";
		fout << "[" << CodeItem::GetTypeString(renames.GetKey(i)) << "]\n";
		VectorMap<String,String>& map = renames[i];
		SortByKey(map, StdLess<String>());
		for(int j = 0; j < map.GetCount(); j++) {
			String qual_name = map.GetKey(j);
			String replacement = map[j];
			fout << qual_name << " = " << replacement << "\n";
		}
	}
}


void ProjectConfig::LoadThis() {
	renames.Clear();
	
	VectorMap<String,int> sections;
	for(int i = 1; i < CodeItem::TYPE_COUNT; i++)
		sections.Add(CodeItem::GetTypeString(i), i);
	
	VectorMap<String,String>* map = 0;
	String content = LoadFile(path);
	Vector<String> line = Split(content, "\n");
	for(String s : line) {
		try {
			CParser p(s);
			
			if (p.Char('[')) {
				map = 0;
				String section = p.ReadId();
				int type = sections.Get(section, -1);
				if (type < 0) throw Exc("Invalid section '" + section + "'");
				p.PassChar(']');
				map = &renames.GetAdd(type);
			}
			else if (!p.IsEof()) {
				String orig_qual;
				while (true) {
					orig_qual << p.ReadId();
					if (!p.Char2(':', ':'))
						break;
				}
				p.PassChar('=');
				if (p.IsId()) {
					String new_qual = p.ReadId();
					if (!map) {
						LOG("error: no section set for key '" << orig_qual << "'");
						break;
					}
					else if (map->Find(orig_qual) >= 0) {
						LOG("error: key '" << orig_qual << "' already exists");
					}
					else {
						map->Add(orig_qual, new_qual);
					}
				}
			}
		}
		catch (Exc e) {
			LOG("error: " << e);
		}
	}
}

void UppProjectProcessor::Process() {
	TODO
}

void UppProjectProcessor::Export(String output_dir) {
	UppAssembly as;
	as.AddPath(output_dir);
	
	UppAssemblyData asd(as);
	
	for(int i = 0; i < this->cache.asd.prjs.GetCount(); i++) {
		LOG(i << ": " << this->cache.asd.prjs.GetKey(i));
		
		const UppProject& src_prj = this->cache.asd.prjs[i];
		UppProject& dst_prj = asd.GetProject(src_prj.GetName());
		
		for(int j = 0; j < src_prj.GetUseCount(); j++) {
			String use = src_prj.GetUse(j);
			dst_prj.AddUse(use);
		}
		for(int j = 0; j < src_prj.GetFileCount(); j++) {
			String file_name = src_prj.GetFile(j);
			LOG("\t" << file_name);
			String src_file_path = src_prj.GetFilePath(j);
			String& content = cache.files.Get(src_file_path);
			UppFile& file = files.Get(src_file_path);
			
			if (IsAllSpace(content))
				continue;
			
			String dst_file_path = dst_prj.AddFile(file_name);
			RealizeDirectory(GetFileDirectory(dst_file_path));
			FileOut fout(dst_file_path);
			fout << content;
		}
		dst_prj.Store();
	}
	
	TODO
}

void RunArtisticStyleRecursively(String output_dir, String astyle_flags) {
	TODO
}



NAMESPACE_TOPSIDE_END

