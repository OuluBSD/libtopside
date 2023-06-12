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
	
};

class DbgEntity {
	
public:
	Array<DbgComponent> comps;
	String name;
	
public:
	
	void Clear() {
		name.Clear();
	}
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
};

class EngineSerializer {
public:
	DbgPool pool;
	
public:
	void Etherize(Ether& e);
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
	
	
	
	GeomSerializer write;
	EngineSerializer read;
	
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
	
};

NAMESPACE_TOPSIDE_END

#endif
