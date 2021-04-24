#include "Editor.h"

NAMESPACE_OULU_BEGIN


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


NAMESPACE_OULU_END

using namespace Upp;
using namespace Oulu;


GUI_APP_MAIN {
	
	String prj_name = "SuccessSingle";
	
	UppAssembly as;
	UppAssemblyData ad(as);
	#ifdef flagWIN32
	as.AddPath("C:\\Oulu\\tests\\cpp");
	#else
	as.AddPath(GetHomeDirFile("fos/tests/plan"));
	#endif
	as.Dump();
	
	UppProject& prj = ad.GetProject(prj_name);
	
	Editor e;
	e.SetProject(prj, ad);
	e.Run();
	
}


