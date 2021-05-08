#ifndef _EcsCore_EntityStore_h_
#define _EcsCore_EntityStore_h_


NAMESPACE_OULU_BEGIN


class EntityStore : public System<EntityStore> {
	PoolVec							root;
	
	LinkedList<ConnectorBase*>		refresh_poolcomps[2];
	Mutex							lock;
	
	void Visit(RuntimeVisitor& vis) override {
		vis || root;
	}
	enum {
		READ,
		WRITE
	};
public:
	EntityStore(Machine& m) : RefScopeParent<RefParent1<Machine>>(m) {
		root.Add().SetParent(PoolParent(this,0));
	}
	
	PoolRef GetRoot()	{return *root.begin();}
	PoolVec& GetRootVec()	{return root;}
	
	
	int64 PostRefresh(int64 last_refresh, ConnectorBase* comp);
	
protected:
	void Update(double) override;
	bool Initialize() override;
	void Uninitialize() override;
	
	
};


NAMESPACE_OULU_END


#endif
