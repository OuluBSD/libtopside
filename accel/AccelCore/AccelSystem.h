#ifndef _AccelCore_AccelSystem_h_
#define _AccelCore_AccelSystem_h_

NAMESPACE_TOPSIDE_BEGIN


class AccelComponent;
class AccelContextComponent;

using AccelComponentRef				= Ref<AccelComponent,				RefParent1<Entity>>;
using AccelContextComponentRef		= Ref<AccelContextComponent,		RefParent1<Entity>>;


class AccelContextComponent :
	public Component<AccelContextComponent>
{
	RTTI_COMP0(AccelContextComponent)
	VIS_COMP_0_0
	
	
public:
	COPY_PANIC(AccelContextComponent);
	
	AccelContextComponent() {}
	
	void		Initialize() override;
	void		Uninitialize() override;
    void		Update(double dt);
	
};


class AccelComponent : public RefScopeEnabler<AccelComponent,Entity> {
	RTTI_DECL_R0(AccelComponent)
	
	
public:
	COPY_PANIC(AccelComponent);
	
	AccelComponent();
	
	void Update0(double dt);
	
};


class AccelSystem : public System<AccelSystem> {
	LinkedList<AccelContextComponentRef>	ctxs;
	LinkedList<AccelComponentRef>			comps;
	
	void Visit(RuntimeVisitor& vis) override {
		vis && ctxs
			&& comps;
	}
public:
	SYS_RTTI(AccelSystem)
	SYS_CTOR(AccelSystem);
	
protected:
	
    bool Initialize() override;
    void Start() override;
    void Update(double dt) override;
    void Stop() override;
    void Uninitialize() override;
    
protected:
	friend class AccelContextComponent;
	friend class AccelComponent;
	
    void Add(AccelContextComponentRef ctx);
    void Add(AccelComponentRef comp);
    void Remove(AccelContextComponentRef ctx);
    void Remove(AccelComponentRef comp);
    
    void UpdateTexBuffers();
    
};


NAMESPACE_TOPSIDE_END

#endif
