#include "Editor.h"

NAMESPACE_TOPSIDE_BEGIN


class PlanUnit {
	
	
};

class ScheduleUnit {
	
	
};

class ScheduleGroup {
	
	
};

class TransformerObject {
	
	
};

class ActionEntity {
	
	
};

class CompilationObject {
	
	
};

class CompilationUnit {
	
	
};


NAMESPACE_TOPSIDE_END

using namespace UPP;
using namespace TS;


GUI_APP_MAIN {
	
	String prj_name = "SuccessSingle";
	
	UppAssembly as;
	UppAssemblyData ad(as);
	#ifdef flagWIN32
	as.AddPath("C:\\Topside\\tests\\cpp");
	#else
	as.AddPath(GetHomeDirFile("fos/tests/plan"));
	#endif
	as.Dump();
	
	UppProject& prj = ad.GetProject(prj_name);
	
	Editor e;
	e.SetProject(prj, ad);
	e.Run();
	
}


