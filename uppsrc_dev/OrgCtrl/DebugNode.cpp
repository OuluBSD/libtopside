#include "OrgCtrl.h"


BEGIN_TEXTLIB_NAMESPACE


DebugView::DebugView() {
	
}

void DebugView::Data() {
	
}







DebugCtrl::DebugCtrl() {
	Add(hsplit.SizePos());
	
	hsplit.Horz() << types << items << subitems0 << subitems1 << subitems2 << subitems3;
	
	types.AddColumn("Type");
	types.AddColumn("Count");
	types.AddIndex("IDX");
	types <<= THISBACK(DataType);
	
	items.AddColumn("Item");
	//items.AddColumn("Description");
	items.AddIndex("IDX");
	items <<= THISBACK(DataItem);
	
	subitems0.AddColumn("Item");
	subitems0.AddColumn("Description");
	subitems0.AddIndex("IDX");
	subitems0 <<= THISBACK(DataSubItem0);
	
	subitems1.AddColumn("Item");
	subitems1.AddColumn("Description");
	subitems1.AddIndex("IDX");
	subitems1 <<= THISBACK(DataSubItem1);
	subitems1.ColumnWidths("6 1");
	subitems2.AddColumn("Item");
	subitems2.AddColumn("Description");
	subitems2.AddIndex("IDX");
	subitems2 <<= THISBACK(DataSubItem2);
	
	subitems3.AddColumn("Item");
	subitems3.AddColumn("Description");
	subitems3.AddIndex("IDX");
	subitems3 <<= THISBACK(DataSubItem3);
	
	
}

void DebugCtrl::OnValueChange() {
	
}

void DebugCtrl::ToolMenu(Bar& bar) {
	
}

void DebugCtrl::Do(int fn) {
	
}

void DebugCtrl::Data() {
	RegisterTypes();
	
	
	for(int i = 0; i < type_cbs.GetCount(); i++) {
		int count = 0;
		count_cbs[i](count);
		String name = type_cbs.GetKey(i);
		types.Set(i, 0, name);
		types.Set(i, 1, count);
		types.Set(i, "IDX", i);
	}
	INHIBIT_CURSOR(types);
	types.SetCount(type_cbs.GetCount());
	if (types.GetCount() && !types.IsCursor())
		types.SetCursor(0);
	
	DataType();
}

void DebugCtrl::DataType() {
	int cursor = items.IsCursor() ? items.GetCursor() : 0;
	items.Clear();
	subitems0.Clear();
	subitems1.Clear();
	subitems2.Clear();
	
	if (!types.IsCursor())
		return;
	
	int idx = types.Get("IDX");
	item_cbs.Clear();
	if (idx < type_cbs.GetCount())
		type_cbs[idx]();
	INHIBIT_CURSOR(items);
	if (cursor >= 0 && cursor < items.GetCount())
		items.SetCursor(cursor);
	
	DataItem();
}

void DebugCtrl::DataItem() {
	int cursor = subitems0.IsCursor() ? subitems0.GetCursor() : 0;
	subitems0.Clear();
	subitems1.Clear();
	subitems2.Clear();
	
	if (!types.IsCursor() || !items.IsCursor())
		return;
	
	int idx = items.Get("IDX");
	subitem0_cbs.Clear();
	if (idx < item_cbs.GetCount())
		item_cbs[idx]();
	INHIBIT_CURSOR(subitems0);
	if (cursor >= 0 && cursor < subitems0.GetCount())
		subitems0.SetCursor(cursor);
	
	DataSubItem0();
}

void DebugCtrl::DataSubItem0() {
	int cursor = subitems1.IsCursor() ? subitems1.GetCursor() : 0;
	subitems1.Clear();
	subitems2.Clear();
	
	if (!types.IsCursor() || !items.IsCursor() || !subitems0.IsCursor())
		return;
	
	int idx = subitems0.GetCursor();
	subitem1_cbs.Clear();
	if (idx < subitem0_cbs.GetCount())
		subitem0_cbs[idx]();
	INHIBIT_CURSOR(subitems1);
	if (cursor >= 0 && cursor < subitems1.GetCount())
		subitems1.SetCursor(cursor);
	
	DataSubItem1();
}

void DebugCtrl::DataSubItem1() {
	int cursor = subitems2.IsCursor() ? subitems2.GetCursor() : 0;
	subitems2.Clear();
	
	if (!types.IsCursor() || !items.IsCursor() || !subitems0.IsCursor() || !subitems1.IsCursor())
		return;
	
	int idx = subitems1.GetCursor();
	subitem2_cbs.Clear();
	if (idx < subitem1_cbs.GetCount())
		subitem1_cbs[idx]();
	INHIBIT_CURSOR(subitems2);
	if (cursor >= 0 && cursor < subitems2.GetCount())
		subitems2.SetCursor(cursor);
	
	DataSubItem2();
}

void DebugCtrl::DataSubItem2() {
	int cursor = subitems3.IsCursor() ? subitems3.GetCursor() : 0;
	subitems3.Clear();
	
	if (!types.IsCursor() || !items.IsCursor() || !subitems0.IsCursor() || !subitems1.IsCursor() || !subitems2.IsCursor())
		return;
	
	int idx = subitems2.GetCursor();
	subitem3_cbs.Clear();
	if (idx < subitem2_cbs.GetCount())
		subitem2_cbs[idx]();
	INHIBIT_CURSOR(subitems3);
	if (cursor >= 0 && cursor < subitems3.GetCount())
		subitems3.SetCursor(cursor);
	
	DataSubItem3();
}

void DebugCtrl::DataSubItem3() {
	
}


END_TEXTLIB_NAMESPACE
