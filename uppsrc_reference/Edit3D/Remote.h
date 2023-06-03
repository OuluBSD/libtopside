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
	DbgPool pool;
	
public:
	void Etherize(Ether& e);
	static void EtherizePool(Ether& e, DbgPool& p);
	static void EtherizeEntity(Ether& e, DbgEntity& p);
	static void EtherizeComponent(Ether& e, DbgComponent& c);
	
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
	
	TabCtrl tabs;
	
	Splitter eng_vert, eng_horz;
	ArrayCtrl eng_entities, eng_components, eng_compdata;
	DocEdit eng_log;
	
public:
	typedef RemoteDebugCtrl CLASSNAME;
	
	RemoteDebugCtrl(Edit3D* e);
	void Update(double dt);
	void Data();
	
	
};

NAMESPACE_TOPSIDE_END

#endif
