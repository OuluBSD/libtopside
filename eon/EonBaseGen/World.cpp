#include "EonBaseGen.h"

NAMESPACE_EONGEN_BEGIN


World::World() {
	
}

void World::OnError(String msg) {
	LOG("World: error: " << msg);
}

bool World::LoadJSON(String json) {
	Object o = ParseJSON(json);
	//LOG(GetObjectTreeString(o));
	
	if (!o.IsMap())
		return false;
	
	ObjectMap& m = o.GetMap();
	
	for(int i = 0; i < m.GetCount(); i++) {
		Object& sub = m[i];
		String key = m.GetKey(i);
		
		if (key == "bases") {
			if (!sub.IsMap()) {
				OnError("Expected map");
				return false;
			}
			
			if (!LoadBases(sub.GetMap()))
				return false;
		}
		else if (key == "headers") {
			if (!sub.IsMap()) {
				OnError("Expected map");
				return false;
			}
			
			if (!LoadHeaders(sub.GetMap()))
				return false;
		}
		else TODO
		
	}
	
	
	return true;
}

bool World::LoadBases(ObjectMap& m) {
	LOG(GetObjectTreeString(m));
	
	for(int i = 0; i < m.GetCount(); i++) {
		Object& sub = m[i];
		String key = m.GetKey(i);
		
		if (!sub.IsMap()) {
			OnError("Expected map");
			return false;
		}
		
		if (!LoadBase(key, sub.GetMap()))
			return false;
	}
	
	return true;
}

bool World::LoadBase(String key, ObjectMap& m) {
	//LOG(GetObjectTreeString(m));
	
	int i = units.Find(key);
	if (i >= 0) {
		OnError("Unit '" + key + "' already exists");
		return false;
	}
	
	Object* sink = m.TryFind("sink");
	Object* side = m.TryFind("side");
	Object* src  = m.TryFind("src");
	if (!sink || !sink->IsString()) {OnError("Base '" + key + "' is missing sink string");   return false;}
	if (!src  || !src->IsString())  {OnError("Base '" + key + "' is missing source string"); return false;}
	if (!side || !side->IsString()) {OnError("Base '" + key + "' is missing side string");   return false;}
	
	Unit& unit = units.Add(key);
	unit.key = key;
	
	if (!ParseValDev(sink->Get<String>(), unit.sink)) return false;
	if (!ParseValDev(src->Get<String>(),  unit.src)) return false;
	
	
	String side_str = side->Get<String>();
	if (side_str == "src") {
		unit.side_src = true;
	}
	else if (side_str == "sink") {
		unit.side_src = false;
	}
	else {
		OnError("Unexpected side id '" + side_str + "'");
		return false;
	}
	
	
	
	return true;
}

#define ERR(msg) OnError(":" + IntStr(p.GetLine()) + ":" + IntStr(p.GetColumn()) + ": " + msg);

bool World::ParseValDev(String s, ValDevCls& vd) {
	CParser p(s);
	if (!p.IsId()) {
		ERR("Expected id in '" + s + "'")
		return false;
	}
	String dev_str = p.ReadId();
	
	if (!p.Char('-')) {
		ERR("Expected char '-' in '" + s + "'");
		return false;
	}
	
	if (!p.IsId()) {
		ERR("Expected id in '" + s + "'")
		return false;
	}
	String val_str = p.ReadId();
	
	
	vd.dev = DevCls::Get(dev_str);
	if (vd.dev == DevCls::INVALID) {
		ERR("Invalid device id '" + dev_str + "'");
		return false;
	}
	
	
	vd.val = ValCls::Get(val_str);
	if (vd.val == ValCls::INVALID) {
		ERR("Invalid value id '" + val_str + "'");
		return false;
	}
	
	return true;
}

bool World::LoadHeaders(ObjectMap& m) {
	LOG(GetObjectTreeString(m));
	
	TODO
	
}


NAMESPACE_EONGEN_END
