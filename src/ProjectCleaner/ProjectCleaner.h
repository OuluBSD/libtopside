#ifndef _ProjectCleaner_ProjectCleaner_h_
#define _ProjectCleaner_ProjectCleaner_h_

#include <Local/Local.h>


NAMESPACE_TOPSIDE_BEGIN



struct ProjectConfig {
	VectorMap<int,VectorMap<String,String>> renames;
	String path;
	
	
	
	void Serialize(Stream& s) {s % renames % path;}
	void SetPath(String s) {path = s;}
	void StoreThis();
	void LoadThis();
	
};


struct CodeItem : Moveable<CodeItem> {
	String file;
	int offset = 0;
	
	String name, qual_name;
	int type = 0;
	//void* uniq = 0;
	
	enum {
		INVALID,
		
		NAMESPACE,
		CLASS,
		TYPEDEF,
		ENUM,
		STATIC_FUNCTION,
		CLASS_METHOD,
		
		NAMESPACE_REF,
		CLASS_REF,
		TYPEDEF_REF,
		ENUM_REF,
		STATIC_FUNCTION_REF,
		CLASS_METHOD_REF,
		CLASS_FIELD_REF,
		
		TYPE_COUNT,
		
		UNKNOWN,
	};
	
	void RemoveQualTemplate();
	
	void Serialize(Stream& s) {s % file % offset % name % qual_name % type;}
	bool operator==(const CodeItem& i) const {return offset == i.offset && file == i.file && type == i.type;}
	
	String ToString() const {
		return GetFileName(file) + ":" + IntStr(offset) + ": " + name + ", " + qual_name + " (" + GetTypeString(type) + ")";
	}
	
	static String GetTypeString(int i) {
		switch(i) {
			case NAMESPACE: return "namespace";
			case CLASS: return "class";
			case TYPEDEF: return "typedef";
			case ENUM: return "enum";
			case STATIC_FUNCTION: return "function";
			case CLASS_METHOD: return "method";
			
			case NAMESPACE_REF: return "namespace-ref";
			case CLASS_REF: return "class-ref";
			case TYPEDEF_REF: return "typedef-ref";
			case ENUM_REF: return "enum-ref";
			case STATIC_FUNCTION_REF: return "function-ref";
			case CLASS_METHOD_REF: return "method-ref";
			case CLASS_FIELD_REF: return "field-ref";
			
			case UNKNOWN: return "unknown";
		}
		return "invalid";
	}
	
	bool operator()(const CodeItem& a, const CodeItem& b) const {
		if (a.file == b.file) {
			if (a.offset == b.offset)
				return a.type < b.type;
			return a.offset < b.offset;
		}
		return a.file < b.file;
	}
};

NAMESPACE_TOPSIDE_END
int ClangToolMain(int argc, const char **argv, UPP::Vector<TS::CodeItem>& out);
NAMESPACE_TOPSIDE_BEGIN

void CppImportTool(String path, const Vector<String>& includes, const Vector<String>& defines, Vector<CodeItem>& out);
void CppImportToolFork(String path, const Vector<String>& includes, const Vector<String>& defines, Vector<CodeItem>& out);

void CleanAssembly(String conf_path, String assembly_dir, const Index<String>& pkgs, String output_dir, bool use_cache);
void RunArtisticStyleRecursively(String output_dir, String astyle_flags);
String RunCompiler(String cmd);


struct UppFile : Moveable<UppFile> {
	struct MacroConditional : Moveable<MacroConditional> {
		Index<String> id_list;
		
		void Serialize(Stream& s) {s % id_list;}
	};
	struct MacroDefinition : Moveable<MacroDefinition> {
		int line = -1;
		bool is_function = false;
		String key;
		String placeholder, original_line;
		Index<String> id_list;
		
		void Serialize(Stream& s) {s % line % is_function % key % placeholder % original_line % id_list;}
	};
	struct MacroUse : Moveable<MacroUse> {
		String id;
		int cursor;
		
		void Serialize(Stream& s) {s % id % cursor;}
	};
	
	Vector<MacroConditional> macro_conds;
	Vector<MacroDefinition> macro_defs;
	Vector<MacroUse> macro_use;
	Index<String> macro_cond_ids, macro_def_ids;
	bool pragma_once = false;
	
	//Index<String> included_by;
	
	void Serialize(Stream& s) {
		s
		  % macro_conds % macro_defs % macro_use % macro_cond_ids % macro_def_ids % pragma_once;
	}
};

struct UppProjectProcessor {
	UppAssemblyCache& cache;
	ArrayMap<String, UppFile> files;
	Index<String> macro_cond_ids;
	VectorMap<String,int> macro_def_ids;
	Vector<CodeItem> all_items;
	int stage = 0;
	
	ProjectConfig config;
	
	String persistent_path;
	String ref_cache_dir;
	Vector<String> includes, defines;
	int actual, total;
	Mutex lock;
	bool verbose = false;
	
	
	
	static const char* placeholder_str;
	
	typedef UppProjectProcessor CLASSNAME;
	UppProjectProcessor(UppAssemblyCache& cache);
	
	void Serialize(Stream& s) {
		s % cache % files % macro_cond_ids % macro_def_ids % all_items % stage;
	}
	
	void SetPersistent(String path) {persistent_path = path;}
	bool LoadThis();
	bool StoreThis();
	void EraseDepreacedHeaderOnce();
	void EraseComments();
	void FindMacroConditionals();
	void FindMacroDefinitions();
	void InstallMacroPlaceholder_NonConditionallyUsedDefine();
	void RunStdPreprocessor();
	void RunStdPreprocessorPath(int i);
	void UninstallMacroPlaceholder_NonConditionallyUsedDefine();
	void FindMacroDefineReferences();
	void RemoveUnusedMacros();
	void FindReferences();
	void FindReferencePath(String path);
	void RealizeConfiguration(String conf_file);
	void Process();
	void Export(String output_dir);
	
	Callback2<int,int> WhenProgress;
	Callback1<int> WhenLoaded;
};

NAMESPACE_TOPSIDE_END

#endif
