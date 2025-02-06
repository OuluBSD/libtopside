#ifndef _Edit3D_Remote_h_
#define _Edit3D_Remote_h_

NAMESPACE_TOPSIDE_BEGIN


class DbgComponent {
	
public:
	struct RefLink : Moveable<RefLink> {
		Vector<String> path;
		dword type;
	};
	
	ArrayMap<String, Object> vars;
	Vector<RefLink> refs;
	String cls_name;
	
public:
	
	void Clear() {
		vars.Clear();
		refs.Clear();
		cls_name.Clear();
	}
	
	template <class T>
	T& AddVar(String name) {
		int i = vars.Find(name);
		if (i >= 0) {
			Object& o = vars[i];
			if (o.Is<T>())
				return o.Get<T>();
			return o.Create<T>();
		}
		Object& o = vars.Add(name);
		return o.Create<T>();
	}
	
	String GetTreeString(int indent=0) const;
	
};

class DbgEntity {
	
public:
	Array<DbgComponent> comps;
	String name;
	
public:
	
	void Clear() {
		name.Clear();
	}
	
	void LoadObject(GeomObject& obj);
	
	DbgComponent& GetAddComponent(String cls_name);
	String GetTreeString(int indent=0) const;
	
};

class DbgPool {
	
public:
	Array<DbgPool> pools;
	Array<DbgEntity> ents;
	String name;
	
public:
	
	void Clear() {
		pools.Clear();
		ents.Clear();
		name.Clear();
	}
	
	void LoadScene(GeomScene& scene);
	void LoadCamera(GeomCamera& cam);
	
	String ToString() const {return GetTreeString();}
	String GetTreeString(int indent=0) const;
	
};

class EngineSerializer {
	
	
public:
	DbgPool pool;
	
public:
	void Etherize(Ether& e);
	void Load(GeomScene& scene, GeomCamera& camera);
	
	static void EtherizePool(Ether& e, DbgPool& p);
	static void EtherizeEntity(Ether& e, DbgEntity& p);
	static void EtherizeComponent(Ether& e, DbgComponent& c);
	
	
	RWMutex lock;
	
};

class RemoteExchange {
	GeomProject* prj = 0;
	GeomWorldState* state = 0;
	GeomAnim* anim = 0;
	GeomStagedVideo* video = 0;
	
	bool data_sync = false;
	bool keypoint_sync = false;
	
	
	void SyncData(const GeomObjectState& o);
	void SyncEntity(const GeomObjectState& o);
	
public:
	typedef RemoteExchange CLASSNAME;
	RemoteExchange();
	
	void SetTarget(GeomProject& p, GeomWorldState& s, GeomAnim& a, GeomStagedVideo& v);
	void SetRequireAllSync();
	void SetRequireDataSync();
	void SetRequireKeypointSync();
	
	bool Update();
	bool UpdateEcsEngine();
	bool UpdateGeomSerializer();
	
	
	
	GeomSerializer write;
	EngineSerializer engine;
	
};



class RemoteDebugCtrl : public Ctrl {
	Edit3D* e;
	RemoteExchange* ex = 0;
	
	TabCtrl tabs;
	
	Splitter vert, horz;
	TreeCtrl tree;
	ArrayCtrl entities, components, compdata;
	DocEdit log;
	
public:
	typedef RemoteDebugCtrl CLASSNAME;
	
	RemoteDebugCtrl(Edit3D* e);
	void Update(double dt);
	void Data();
	void SetRemoteData(RemoteExchange& e) {ex = &e;}
	void RefreshPools(bool has_lock);
	void RefreshTreePool(int tree_id, DbgPool& pool);
	void RefreshPool(bool has_lock);
	void RefreshEntity(bool has_lock);
	void RefreshComponent(bool has_lock);
	
	DbgPool* GetPool(int tree_id);
	RemoteExchange* GetExchange() const {return ex;}
	
};

NAMESPACE_TOPSIDE_END

#endif
