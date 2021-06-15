#ifndef _Editor_NodeCache_h_
#define _Editor_NodeCache_h_

#include "NodeItem.h"



class NodeCache {
	
protected:
	Translation::Project project;
	Vector<String> top_paths;
	ClangNode data;
	
	void GetAllBasicR(ClangNode& src, ClangNode& dest, int depth);
	
public:
	
	NodeCache();
	
	NodeCache& operator=(const NodeCache& nc) {
		top_paths <<= nc.top_paths;
		data = nc.data;
		return *this;
	}
	void Serialize(Stream& s) {s % top_paths % data;}
	void StoreThis() {ASSERT(data.GetString().GetCount()); StoreToFile(*this, ConfigFile("nodecache_" + data.GetString() + ".bin"));}
	void LoadThis() {ASSERT(data.GetString().GetCount()); LoadFromFile(*this, ConfigFile("nodecache_" + data.GetString() + ".bin"));}
	String Dump() {return ::Dump(data);}
	void LoadFileNode(String path, ClangNode& node);
	
	Translation::Project& GetTranslator() {return project;}
	ClangNode& GetProject() {return data;}
	ClangNode& GetPackage(String name) {return NodeGetPackage(data, name);}
	
	NodeCache& SetProjectName(String name) {data.SetType(CI_PRJMGR); data.SetString(name); return *this;}
	
	ClangNode GetAllBasic();
	
};

void CopyClangNode(Translation::Cursor& from_clang_node, ClangNode& to_node);


#endif
