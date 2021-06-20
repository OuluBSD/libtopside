#ifndef _EcsLib_Router_h_
#define _EcsLib_Router_h_

NAMESPACE_TOPSIDE_BEGIN


class PathwayRouter :
	public Connector<PathwayRouter>,
	public ManualConnector
{
	struct Item : RTTIBase {
		EntityRef e;
		String eon_code;
		
		RTTI_DECL0(Item)
		void Visit(RuntimeVisitor& vis) {vis & e;}
	};
	
	
	LinkedList<Item> add_queue, maintained;
	
public:
	RTTI_CONN0(PathwayRouter)
	COPY_PANIC(PathwayRouter);
	
	void Initialize() override;
	void Uninitialize() override;
	TypeCls GetType() const override {return AsTypeCls<PathwayRouter>();}
	void CopyTo(ConnectorBase* component) const override {}
	void Update(double dt) override;
	void Visit(RuntimeVisitor& vis) override {vis || add_queue || maintained;}
	void UnlinkAll() override;
	
	void Add(EntityRef e, String eon_code);
	void Remove(EntityRef e);
	void ProcessAddQueue();
	
};

using PathwayRouterRef = RefT_Pool<PathwayRouter>;



class PathwaySystem :
	public System<PathwaySystem>
{
	LinkedList<PathwayRouterRef> pathways;
	
	
public:
	SYS_RTTI(PathwaySystem)
	SYS_CTOR(PathwaySystem);
	SYS_DEF_VISIT_(vis && pathways)
	
	
protected:
	
    bool Initialize() override;
    void Start() override;
    void Update(double dt) override;
    void Stop() override;
    void Uninitialize() override;
    
protected:
	friend class PathwayRouter;
	
    void Add(PathwayRouterRef p);
    void Remove(PathwayRouterRef p);
    
};

using PathwaySystemRef = Ref<PathwaySystem, RefParent1<Machine>>;


NAMESPACE_TOPSIDE_END

#endif
