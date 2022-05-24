#include "EcsCtrl.h"


NAMESPACE_TOPSIDE_BEGIN
using namespace Ecs;


InterfaceDataCtrl::InterfaceDataCtrl() {
	ParentCtrl::Add(list.SizePos());
	
	list.AddColumn("Key");
	list.AddColumn("Value");
	
}


	
InterfaceSystemCtrl::InterfaceSystemCtrl() {
	Add(hsplit.Horz().SizePos());
	
	hsplit << vsplit << ent_cont;
	hsplit.SetPos(2000);
	
	vsplit.Vert();
	vsplit << ent_browser << iface_list;
	vsplit.SetPos(4000);
	
	ent_browser.WhenEntityChanged << THISBACK(OnEntityCursorChanged);
	iface_list.WhenInterfaceCursor << THISBACK(OnInterfaceCursorChanged);
	
}

void InterfaceSystemCtrl::OnEntityCursorChanged() {
	EntityRef ent = ent_browser.GetSelected();
	if (ent != sel_ent) {
		sel_ent = ent;
		iface_list.SetEntity(sel_ent);
		iface_list.Update();
	}
}

void InterfaceSystemCtrl::OnInterfaceCursorChanged() {
	if (sel_ent) {
		ComponentBaseRef c;
		ExchangeProviderBaseRef b;
		iface_list.GetCursor(c, b);
		
		if (c && b)
			SetInterfaceCtrl(c, b);
		else
			ClearActiveCtrl();
	}
	else
		ClearActiveCtrl();
}

void InterfaceSystemCtrl::Updated() {
	ent_browser.Updated();
	iface_list.Updated();
}

void InterfaceSystemCtrl::ClearActiveCtrl() {
	if (active_ctrl) {
		ent_cont.RemoveChild(active_ctrl);
		active_ctrl = 0;
	}
}

void InterfaceSystemCtrl::SetInterfaceCtrl(ComponentBaseRef c, ExchangeProviderBaseRef b) {
	ClearActiveCtrl();
	
	TODO
	/*TypeId type = b->GetTypeCls();
	int i = iface_ctrls.Find(type);
	if (i < 0) {
		active_ctrl = NewInterfaceCtrl(type);
		if (!active_ctrl)
			return;
		iface_ctrls.Add(type, active_ctrl);
	}
	else {
		active_ctrl = &iface_ctrls[i];
		ASSERT(active_ctrl);
	}*/
	
	ent_cont.Add(active_ctrl->SizePos());
	
	active_ctrl->SetInterface(c, b);
	active_ctrl->Update();
}


NAMESPACE_TOPSIDE_END
