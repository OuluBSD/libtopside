#ifndef _Backend_Exporter_h_
#define _Backend_Exporter_h_

NAMESPACE_TOPSIDE_BEGIN


class AssemblyExporter {
	
	
public:
	typedef AssemblyExporter CLASSNAME;
	AssemblyExporter() = default;
	
	bool Export(String dir);
	
};
	

NAMESPACE_TOPSIDE_END

#endif
