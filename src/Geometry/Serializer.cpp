#include "Geometry.h"

NAMESPACE_TOPSIDE_BEGIN


GeomSerializer::GeomSerializer() {
	
}

void GeomSerializer::Etherize(Ether& e) {
	
	if (e.IsLoading()) {
		model_cache.Clear();
		
		int c = 0;
		e.Get(&c, sizeof(c));
		items.SetCount(0);
		items.SetCount(c);
		
		for (Item& item : items) {
			e.Get(&item.type, sizeof(item.type));
			
			switch (item.type) {
			case GEOMVAR_ENTITY_KEY:
				e.Get(&item.hash, sizeof(item.hash));
				break;
			case GEOMVAR_RESET_ENTITY_KEY:
				// pass
				break;
			case GEOMVAR_SYSTEM_PATH:
				item.str = e.GetString();
				break;
			case GEOMVAR_ORIENTATION:
				e.Get(item.f, sizeof(item.f[0]) * 4);
				break;
			case GEOMVAR_POSITION:
				e.Get(item.f, sizeof(item.f[0]) * 3);
				break;
			case GEOMVAR_MODEL:
				item.mdl = &model_cache.Add();
				const_cast<Model*>(item.mdl)->Etherize(e);
				break;
				
			case GEOMVAR_NULL:
				break;
			default:
				TODO
			}
		}
	}
	else if (e.IsStoring()) {
		int c = items.GetCount();
		e.Put(&c, sizeof(c));
		
		for (Item& item : items) {
			e.Put(&item.type, sizeof(item.type));
			
			switch (item.type) {
			case GEOMVAR_ENTITY_KEY:
				e.Put(&item.hash, sizeof(item.hash));
				break;
			case GEOMVAR_RESET_ENTITY_KEY:
				// pass
				break;
			case GEOMVAR_SYSTEM_PATH:
				e.Put(item.str);
				break;
			case GEOMVAR_ORIENTATION:
				e.Put(item.f, sizeof(item.f[0]) * 4);
				break;
			case GEOMVAR_POSITION:
				e.Put(item.f, sizeof(item.f[0]) * 3);
				break;
			case GEOMVAR_MODEL:
				if (!item.mdl) {
					e.SetError();
					return;
				}
				const_cast<Model*>(item.mdl)->Etherize(e);
				break;
				
			case GEOMVAR_NULL:
				break;
			default:
				TODO
			}
		}
	}
}

void GeomSerializer::Clear() {
	items.Clear();
}

void GeomSerializer::BindEntity(hash_t key) {
	Item& i = items.Add();
	i.type = GEOMVAR_ENTITY_KEY;
	i.hash = key;
}

void GeomSerializer::UnbindEntity() {
	Item& i = items.Add();
	i.type = GEOMVAR_RESET_ENTITY_KEY;
}

void GeomSerializer::GeomSerializer::Set(GeomVar t, const Model& mdl) {
	Item& i = items.Add();
	i.type = t;
	i.mdl = &mdl;
}

void GeomSerializer::Set(GeomVar t, const String& s) {
	Item& i = items.Add();
	i.type = t;
	i.str = s;
}

void GeomSerializer::Set(GeomVar t, float f) {
	Item& i = items.Add();
	i.type = t;
	i.f[0] = f;
}

void GeomSerializer::Set(GeomVar t, const vec2& v) {
	Item& i = items.Add();
	i.type = t;
	for(int j = 0; j < 2; j++)
		i.f[j] = v.data[j];
}

void GeomSerializer::Set(GeomVar t, const vec3& v) {
	Item& i = items.Add();
	i.type = t;
	for(int j = 0; j < 3; j++)
		i.f[j] = v.data[j];
}

void GeomSerializer::Set(GeomVar t, const vec4& v) {
	Item& i = items.Add();
	i.type = t;
	for(int j = 0; j < 4; j++)
		i.f[j] = v.data[j];
}

void GeomSerializer::Set(GeomVar t, const quat& q) {
	Item& i = items.Add();
	i.type = t;
	for(int j = 0; j < 4; j++)
		i.f[j] = q.data[j];
}


NAMESPACE_TOPSIDE_END
