#ifndef _Geometry_Serializer_h_
#define _Geometry_Serializer_h_

NAMESPACE_TOPSIDE_BEGIN


typedef enum : byte {
	GEOMVAR_NULL,
	GEOMVAR_ENTITY_KEY,			// hash_t
	GEOMVAR_RESET_ENTITY_KEY,
	GEOMVAR_SYSTEM_PATH,		// string
	GEOMVAR_ORIENTATION,		// quat
	GEOMVAR_POSITION,			// vec3
	GEOMVAR_MODEL,				// Model
} GeomVar;


class GeomSerializer {
	
protected:
	friend class EcsService;
	
	struct Item : Moveable<Item> {
		GeomVar type;
		hash_t hash;
		union {
			const Model* mdl;
			void* ptr;
		};
		String str;
		float f[16];
	};
	Vector<Item> items;
	
	Array<Model> model_cache;
	
public:
	GeomSerializer();
	
	void Etherize(Ether& e);
	void Clear();
	
	void BindEntity(hash_t key);
	void UnbindEntity();
	void Set(GeomVar t, const Model& mdl);
	void Set(GeomVar t, const String& s);
	void Set(GeomVar t, float f);
	void Set(GeomVar t, const vec2& v);
	void Set(GeomVar t, const vec3& v);
	void Set(GeomVar t, const vec4& v);
	void Set(GeomVar t, const quat& v);
	
	int GetCount() const {return items.GetCount();}
	const Item& Get(int i) const {return items[i];}
	
};

NAMESPACE_TOPSIDE_END

#endif
