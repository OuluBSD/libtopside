#ifndef _AccelCore_AccelSystem_h_
#define _AccelCore_AccelSystem_h_

NAMESPACE_TOPSIDE_BEGIN



class AccelSystem : public System<AccelSystem> {
	LinkedList<AccelContextComponentRef>	ctxs;
	/*#define IFACE(x) LinkedList<Accel##x##ComponentRef> comps_##x;
	IFACE_LIST
	#undef IFACE*/
	
	void Visit(RuntimeVisitor& vis) override {
		vis && ctxs
		/*#define IFACE(x) && comps_##x;
		IFACE_LIST
		#undef IFACE*/
			;
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
	
	/*#define IFACE(x) \
		void Add(Accel##x##ComponentRef comp) {comps_##x.FindAdd(comp);} \
		void Remove(Accel##x##ComponentRef comp) {comps_##x.RemoveKey(comp);}
	IFACE_LIST
	#undef IFACE*/
    
    void UpdateTexBuffers();
    
};


NAMESPACE_TOPSIDE_END

#endif
