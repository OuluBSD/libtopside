#include "OrgCtrl.h"


BEGIN_TEXTLIB_NAMESPACE


ClassView::ClassView() {
	
}

void ClassView::Data() {
	
}



ClassCtrl::ClassCtrl() {
	CtrlLayout(form);
	
	Add(form.SizePos());
	
	
	form.deps.AddColumn("Dependency");
	form.dep_bys.AddColumn("Dependend by");
	
}

void ClassCtrl::Data() {
	Node& n = *view->node;
	
	int max_depth = n.data.GetAdd("max_depth");
	form.max_depth.SetData(max_depth);
	
	String description = n.data.GetAdd("description");
	form.description.SetData(description);
	
	ValueArray& deps = ValueToArray(n.data.GetAdd("deps"));
	for(int i = 0; i < deps.GetCount(); i++) {
		form.deps.Set(i, 0, deps[i]);
	}
	form.deps.SetCount(deps.GetCount());
	
	ValueArray& dep_bys = ValueToArray(n.data.GetAdd("dep_bys"));
	for(int i = 0; i < dep_bys.GetCount(); i++) {
		form.dep_bys.Set(i, 0, dep_bys[i]);
	}
	form.dep_bys.SetCount(dep_bys.GetCount());
	
}

void ClassCtrl::OnValueChange() {
	
}

void ClassCtrl::Do(int fn) {
	
}

void ClassCtrl::ToolMenu(Bar& bar) {
	
}




END_TEXTLIB_NAMESPACE
