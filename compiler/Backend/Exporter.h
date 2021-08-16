#ifndef _Backend_Exporter_h_
#define _Backend_Exporter_h_

NAMESPACE_TOPSIDE_BEGIN


class AssemblyExporter {
public:
	
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
	
	
private:
	struct ScopeHolder {
		AssemblyExporter& e;
		ScopeHolder(AssemblyExporter* ae, NodeBase& n) : e(*ae) {e.Push(n);}
		~ScopeHolder() {e.Pop();}
	};
	
	ArrayMap<String,Package>	pkgs;
	Vector<NodeBase*>			scopes;
	CompilationUnit&			cu;
	
	bool Visit(CompilationUnit& cu);
	bool Visit(Namespace& ns);
	bool Visit(Class& c);
	bool Visit(Field& f);
	bool Visit(Function& fn);
	bool Visit(Statement& s);
	bool Visit(Expression& e);
	void Push(NodeBase& n);
	void Pop();
	
	
public:
	typedef AssemblyExporter CLASSNAME;
	AssemblyExporter(CompilationUnit& cu);
	
	bool Export(String dir);
	bool ExportComplete(String dir);
	bool ExportPackage(String dir, String prj_name);
	
};
	

NAMESPACE_TOPSIDE_END

#endif
