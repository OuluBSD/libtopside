#include "Local.h"


NAMESPACE_TOPSIDE_BEGIN


RenderingVerifier::RenderingVerifier() {
	
}

void RenderingVerifier::OnRealizeVar(String key, bool state_var) {
	if (vars.Find(key) >= 0)
		Panic("RenderingVerifier: variable '" + key + "' already added");
	
	RTLOG("RenderingVerifier::OnRealizeVar: realizing variable '" + key + "'");
	Var& v = vars.Add(key);
	v.key = key;
	v.updated = false;
	v.state_var = state_var;
}

void RenderingVerifier::OnUpdateVar(String key) {
	int i = vars.Find(key);
	if (i < 0)
		Panic("RenderingVerifier: variable '" + key + "' not realized");
	
	RTLOG("RenderingVerifier::OnUpdateVar: updating variable '" + key + "'");
	Var& v = vars[i];
	v.updated = true;
}

void RenderingVerifier::OnRealizeObject(int id) {
	if (objs.Find(id) >= 0)
		Panic("RenderingVerifier: object '" + IntStr(id) + "' already added");
	
	RTLOG("RenderingVerifier::OnRealizeVar: realizing variable '" + IntStr(id) + "'");
	Object& o = objs.Add(id);
	o.id = id;
	o.updated_view = false;
	o.updated_proj = false;
	o.updated_scale = false;
	o.updated_model = false;
}

void RenderingVerifier::OnUpdateObject(int id) {
	int i = objs.Find(id);
	if (i < 0)
		Panic("RenderingVerifier: object '" + IntStr(id) + "' not realized");
	
	RTLOG("RenderingVerifier::OnUpdateVar: updating object '" + IntStr(id) + "'");
	Object& o = objs.Add(id);
	o.updated_view = true;
	o.updated_proj = true;
	o.updated_scale = true;
	o.updated_model = true;
}

void RenderingVerifier::OnProcess() {
	String list;
	for (Var& v : vars.GetValues()) {
		if (v.state_var && !v.updated) {
			if (!list.IsEmpty()) list << ", ";
			list << v.key;
		}
		
		v.updated = false;
	}
	if (!list.IsEmpty()) {
		Panic("RenderingVerifier: variable(s) was not updated: " + list);
	}
	
	for (Object& o : objs.GetValues()) {
		if (!o.updated_view || !o.updated_proj || !o.updated_scale || !o.updated_model) {
			if (!list.IsEmpty()) list << ", ";
			list << o.id;
		}
		
		o.updated_view = false;
		o.updated_proj = false;
		o.updated_scale = false;
		o.updated_model = false;
	}
	if (!list.IsEmpty()) {
		Panic("RenderingVerifier: object(s) was not updated: " + list);
	}
	
	RTLOG("RenderingVerifier::OnProcess: ok");
}



NAMESPACE_TOPSIDE_END
