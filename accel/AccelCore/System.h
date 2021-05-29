#ifndef _AccelCore_AccelSystem_h_
#define _AccelCore_AccelSystem_h_

NAMESPACE_TOPSIDE_BEGIN



class AccelSystem : public System<AccelSystem> {
	LinkedList<AccelContextComponentRef>	ctxs;
	LinkedList<AccelComponentRef> comps;
	
	void Visit(RuntimeVisitor& vis) override {
		vis && ctxs;
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
    void Remove(AccelContextComponentRef ctx);
	void Add(AccelComponentRef comp) {comps.FindAdd(comp);}
	void Remove(AccelComponentRef comp) {comps.RemoveKey(comp);}
    
    
};


NAMESPACE_TOPSIDE_END

#endif
