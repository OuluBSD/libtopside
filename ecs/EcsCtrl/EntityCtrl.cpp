#include "EcsCtrl.h"

NAMESPACE_TOPSIDE_BEGIN
using namespace Ecs;


EntityDataCtrl::EntityDataCtrl() {
	ParentCtrl::Add(list.SizePos());
	list.AddColumn("Key");
	list.AddColumn("Value");
	
}




EntityCtrl::EntityCtrl() {
	Add(hsplit.Horz().SizePos());
	
	hsplit << vsplit << ent_cont;
	hsplit.SetPos(2000);
	
	vsplit.Vert();
	vsplit << ent_browser << ent_content;
	
	
	ent_browser.WhenEntityChanged << THISBACK(OnEntityCursorChanged);
	ent_content.WhenContentCursor << THISBACK(OnContentCursorChanged);
	
}

void EntityCtrl::OnEntityCursorChanged() {
	EntityRef ent = ent_browser.GetSelected();
	if (ent != sel_ent) {
		sel_ent = ent;
		ent_content.SetEntity(sel_ent);
		ent_content.Update();
	}
}

void EntityCtrl::OnContentCursorChanged() {
	if (sel_ent) {
		ComponentBaseRef c;
		
		ent_content.GetCursor(c);
		
		if (c)
			SetComponentCtrl(*c);
		else
			SetEntityDataCtrl();
	}
	else
		ClearActiveCtrl();
}

void EntityCtrl::Updated() {
	ent_browser.Updated();
	ent_content.Updated();
}

void EntityCtrl::ClearActiveCtrl() {
	if (active_ctrl) {
		ent_cont.RemoveChild(active_ctrl);
		active_ctrl = 0;
	}
}

void EntityCtrl::SetEntityDataCtrl() {
	ClearActiveCtrl();
	
	active_ctrl = &ent_data;
	ent_cont.Add(ent_data.SizePos());
	UpdateEntityData();
}

void EntityCtrl::SetComponentCtrl(ComponentBase& c) {
	ClearActiveCtrl();
	
	TODO
	/*TypeId type = c.GetType();
	int i = comp_ctrls.Find(type);
	if (i < 0) {
		active_ctrl = NewComponentCtrl(type);
		if (!active_ctrl)
			return;
		comp_ctrls.Add(type, active_ctrl);
	}
	else {
		active_ctrl = &comp_ctrls[i];
		ASSERT(active_ctrl);
	}
	
	ent_cont.Add(active_ctrl->SizePos());*/
	
	active_ctrl->SetComponent(c);
	active_ctrl->Update();
}

void EntityCtrl::UpdateEntityData() {
	if (sel_ent)
		ent_data.UpdateEntityData(*sel_ent);
}






void EntityDataCtrl::UpdateEntityData(Entity& e) {
	ent_cursor = 0;
	
	AddEntityDataRow("created", e.GetCreatedTick());
	AddEntityDataRow("id", e.GetId());
	AddEntityDataRow("prefab", e.GetPrefab());
	
	const auto& comps = e.GetComponents();
	AddEntityDataRow("component-count", comps.GetCount());
	
	list.SetCount(ent_cursor);
}

void EntityDataCtrl::AddEntityDataRow(UPP::Value key, UPP::Value value) {
	list.Set(ent_cursor, 0, key);
	list.Set(ent_cursor, 1, value);
	ent_cursor++;
}


NAMESPACE_TOPSIDE_END
