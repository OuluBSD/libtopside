#include "Local.h"


NAMESPACE_TOPSIDE_BEGIN


int default_width = 1280;
int default_height = 720;




RenderingVerifier::RenderingVerifier() {
	
}

void RenderingVerifier::OnClearVars() {
	vars.Clear();
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
	// TODO fix: id is per state, not global
	#if 0
	if (objs.Find(id) >= 0)
		Panic("RenderingVerifier: object '" + IntStr(id) + "' already added");
	
	RTLOG("RenderingVerifier::OnRealizeVar: realizing variable '" + IntStr(id) + "'");
	Object& o = objs.Add(id);
	o.id = id;
	o.updated_view = false;
	o.updated_proj = false;
	o.updated_scale = false;
	o.updated_model = false;
	#endif
}

void RenderingVerifier::OnUpdateObject(int id, int var) {
	// TODO fix: id is per state, not global
	#if 0
	int i = objs.Find(id);
	if (i < 0)
		Panic("RenderingVerifier: object '" + IntStr(id) + "' not realized");
	
	RTLOG("RenderingVerifier::OnUpdateObject: updating object '" + IntStr(id) + "'");
	Object& o = objs[i];
	switch (var) {
		case VIEW:		o.updated_view = true; break;
		case PROJECT:	o.updated_proj = true; break;
		case SCALE:		o.updated_scale = true; break;
		case MODEL:		o.updated_model = true; break;
		default: Panic("invalid var");
	}
	#endif
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
			list << o.id << "(";
			for(int i = 0, j = 0; i < 4; i++) {
				bool b;
				const char* s;
				switch (i) {
					case 0: b = o.updated_view; s = "view"; break;
					case 1: b = o.updated_proj; s = "proj"; break;
					case 2: b = o.updated_scale; s = "scale"; break;
					case 3: b = o.updated_model; s = "model"; break;
				}
				if (!b) {
					if (j++ > 0) list << ", ";
					list << s;
				}
			}
			list << ")";
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
