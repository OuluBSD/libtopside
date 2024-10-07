#include "OrgCtrl.h"


BEGIN_TEXTLIB_NAMESPACE


ServicesCtrl::ServicesCtrl() {
	Add(hsplit.SizePos());
	
	hsplit.Horz() << vsplit << placeholder;
	hsplit.SetPos(1100);
	
	vsplit.Vert(src, mode);
	
	src.AddColumn(t_("Source"));
	
	mode.AddColumn(t_("Mode"));
	
}

void ServicesCtrl::Init() {
	
	
}

void ServicesCtrl::Data() {
	
	
}

void ServicesCtrl::ToolMenu(Bar& bar) {
	
	
}


END_TEXTLIB_NAMESPACE

