#ifndef _Backend_Exporter_h_
#define _Backend_Exporter_h_

NAMESPACE_TOPSIDE_BEGIN

struct PackageFile {
	Vector<NodeBase*>				refs;
	String							name;
	
};

struct Package {
	ArrayMap<String,PackageFile>	files;
	Index<String>					deps;
	String							name;
	
	void Set(String s) {name = s; deps.Clear();}
	String ToString() const {return name;}
};


class AssemblyExporter {
public:
	
	
	
private:
	struct ScopeHolder {
		AssemblyExporter& e;
		ScopeHolder(AssemblyExporter* ae, NodeBase& n) : e(*ae) {e.Push(n);}
		~ScopeHolder() {e.Pop();}
	};
	
	ArrayMap<String,Package>	pkgs;
	Vector<NodeBase*>			scopes;
	AstNode&					root;
	String						export_dir;
	bool						protect_pkg = false;
	
	
	bool Visit(AstNode& n);
	void Push(NodeBase& n);
	void Pop();
	
	
	bool ExportComplete(String dir);
	bool ExportPackage(Package& pkg);
	bool ExportHeader(Package& pkg, PackageFile& file, String path);
	bool ExportImplementation(Package& pkg, PackageFile& file, String path);
	
public:
	typedef AssemblyExporter CLASSNAME;
	AssemblyExporter(AstNode& root);
	
	bool Export(String dir);
	void Dump();
	void ProtectPackageFile(bool b=true) {protect_pkg = b;}
	
};
	

NAMESPACE_TOPSIDE_END

#endif
