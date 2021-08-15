#ifndef _Backend_Exporter_h_
#define _Backend_Exporter_h_

NAMESPACE_TOPSIDE_BEGIN


class AssemblyExporter {
public:
	
	struct Project {
		String name;
		Index<String> deps;
		
		void Set(String s) {name = s; deps.Clear();}
		String ToString() const {return name;}
	};
	
private:
	ArrayMap<String,Project> prjs;
	
public:
	typedef AssemblyExporter CLASSNAME;
	AssemblyExporter();
	
	bool Export(String dir);
	bool ExportComplete(String dir);
	bool ExportProject(String dir, String prj_name);
	
};
	

NAMESPACE_TOPSIDE_END

#endif
