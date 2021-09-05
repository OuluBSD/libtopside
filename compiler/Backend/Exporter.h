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
	CompilationUnit&			cu;
	String						export_dir;
	bool						protect_pkg = false;
	
	bool Visit(CompilationUnit& cu);
	bool Visit(Namespace& ns);
	bool Visit(Class& c);
	bool Visit(Field& f);
	bool Visit(FunctionIdScope& fis);
	bool Visit(Function& fn);
	bool Visit(Statement& s);
	bool Visit(Expression& e);
	bool Visit(MetaStatement& ms);
	bool Visit(MetaExpression& me);
	bool Visit(UsingStatement& us);
	void Push(NodeBase& n);
	void Pop();
	
	
	bool ExportComplete(String dir);
	bool ExportPackage(Package& pkg);
	bool ExportHeader(Package& pkg, PackageFile& file, String path);
	bool ExportImplementation(Package& pkg, PackageFile& file, String path);
	
public:
	typedef AssemblyExporter CLASSNAME;
	AssemblyExporter(CompilationUnit& cu);
	
	bool Export(String dir);
	void Dump();
	void ProtectPackageFile(bool b=true) {protect_pkg = b;}
	
};
	

NAMESPACE_TOPSIDE_END

#endif
