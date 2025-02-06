#include "OrgCtrl.h"


BEGIN_TEXTLIB_NAMESPACE


PackageView::PackageView() {
	
}

void PackageView::Data() {
	
}



PackageCtrl::PackageCtrl() {
	CtrlLayout(form);
	
	Add(form.SizePos());
	
	
	form.deps.AddColumn("Dependency");
	
}

void PackageCtrl::Data() {
	Node& n = *view->node;
	
	String description = n.data.GetAdd("description");
	form.description.SetData(description);
	
	ValueArray& deps = ValueToArray(n.data.GetAdd("deps"));
	for(int i = 0; i < deps.GetCount(); i++) {
		form.deps.Set(i, 0, deps[i]);
	}
	form.deps.SetCount(deps.GetCount());
	
}

void PackageCtrl::OnValueChange() {
	
}

void PackageCtrl::Do(int fn) {
	
}

void PackageCtrl::ToolMenu(Bar& bar) {
	
}




END_TEXTLIB_NAMESPACE
