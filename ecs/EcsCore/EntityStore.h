#ifndef _EcsCore_EntityStore_h_
#define _EcsCore_EntityStore_h_


NAMESPACE_TOPSIDE_BEGIN


class EntityStore : public System<EntityStore> {
	PoolVec							root;
	
	//LinkedList<ConnectorBase*>		refresh_poolcomps[2];
	Mutex							lock;
	
	enum {
		READ,
		WRITE
	};
	
	void InitRoot();
public:
	SYS_RTTI(EntityStore)
	SYS_CTOR_(EntityStore) {InitRoot();}
	SYS_DEF_VISIT_(vis || root)
	
	PoolRef GetRoot()	{return *root.begin();}
	PoolVec& GetRootVec()	{return root;}
	
	
	//int64 PostRefresh(int64 last_refresh, ConnectorBase* comp);
	
protected:
	void Update(double) override;
	bool Initialize() override;
	void Uninitialize() override;
	
	
};


NAMESPACE_TOPSIDE_END


#endif
