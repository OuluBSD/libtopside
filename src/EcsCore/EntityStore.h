#ifndef _EcsCore_EntityStore_h_
#define _EcsCore_EntityStore_h_


NAMESPACE_ECS_BEGIN


class EntityStore : public System<EntityStore> {
    Vector<Entity*>					destroy_list;
	PoolVec							root;
	
	Mutex							lock;
	
	enum {
		READ,
		WRITE
	};
	
	void InitRoot();
public:
	SYS_RTTI(EntityStore)
	ECS_SYS_CTOR_(EntityStore) {InitRoot();}
	ECS_SYS_DEF_VISIT_(vis || root)
	
	PoolRef GetRoot()	{return *root.begin();}
	PoolVec& GetRootVec()	{return root;}
	
	EntityRef FindEntity(String path);
	void AddToDestroyList(Entity* e);
	
	
protected:
	void Update(double) override;
	bool Initialize() override;
	void Uninitialize() override;
	
	
};


NAMESPACE_ECS_END


#endif
