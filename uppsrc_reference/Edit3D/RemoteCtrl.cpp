#include "Edit3D.h"

NAMESPACE_TOPSIDE_BEGIN

RemoteDebugCtrl::RemoteDebugCtrl(Edit3D* e) : e(e) {
	/*
	TabCtrl tabs;
	
	Splitter eng_horz;
	ArrayCtrl eng_entities, eng_components, eng_compdata;
	*/
	
	Add(tabs.SizePos());
	
	tabs.Add(eng_vert.SizePos(), "ECS");
	
	eng_vert << eng_horz << eng_log;
	eng_vert.Vert().SetPos(8000);
	eng_log.SetFont(Monospace(14));
	
	eng_horz.Horz();
	eng_horz << eng_entities << eng_components << eng_compdata;
	
}

void RemoteDebugCtrl::Update(double dt) {
	
}

void RemoteDebugCtrl::Data() {
	
}

NAMESPACE_TOPSIDE_END
