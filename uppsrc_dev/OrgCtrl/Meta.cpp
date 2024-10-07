#include "OrgCtrl.h"


BEGIN_TEXTLIB_NAMESPACE


MetaView::MetaView() {
	
}

void MetaView::Data() {
	
}



MetaCtrl::MetaCtrl() {
	CtrlLayout(form);
	
	Add(form.SizePos());
	
	
	form.deps.AddColumn("Dependency");
	
}

void MetaCtrl::Data() {
	Node& n = *view->node;
	
	String description = n.data.GetAdd("description");
	form.description.SetData(description);
	
	ValueArray& deps = ValueToArray(n.data.GetAdd("deps"));
	for(int i = 0; i < deps.GetCount(); i++) {
		form.deps.Set(i, 0, deps[i]);
	}
	form.deps.SetCount(deps.GetCount());
	
}

void MetaCtrl::OnValueChange() {
	
}

void MetaCtrl::Do(int fn) {
	
}

void MetaCtrl::ToolMenu(Bar& bar) {
	
}




END_TEXTLIB_NAMESPACE
