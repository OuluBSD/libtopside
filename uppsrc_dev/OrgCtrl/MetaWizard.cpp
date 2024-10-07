#include "OrgCtrl.h"


BEGIN_TEXTLIB_NAMESPACE


MetaWizardView::MetaWizardView() {
	
}

void MetaWizardView::Data() {
	
}



MetaWizardCtrl::MetaWizardCtrl() {
	CtrlLayout(form);
	
	Add(form.SizePos());
	
	
	form.deps.AddColumn("Dependency");
	
}

void MetaWizardCtrl::Data() {
	Node& n = *view->node;
	
	String description = n.data.GetAdd("description");
	form.description.SetData(description);
	
	ValueArray& deps = ValueToArray(n.data.GetAdd("deps"));
	for(int i = 0; i < deps.GetCount(); i++) {
		form.deps.Set(i, 0, deps[i]);
	}
	form.deps.SetCount(deps.GetCount());
	
}

void MetaWizardCtrl::OnValueChange() {
	
}

void MetaWizardCtrl::Do(int fn) {
	
}

void MetaWizardCtrl::ToolMenu(Bar& bar) {
	
}




END_TEXTLIB_NAMESPACE
