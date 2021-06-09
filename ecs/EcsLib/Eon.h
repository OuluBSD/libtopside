#ifndef _EcsLib_Eon_h_
#define _EcsLib_Eon_h_

NAMESPACE_TOPSIDE_BEGIN



class EonLoader :
	public System<EonLoader>
{
	LinkedList<PathwayRouterRef> pathways;
	
	
	void Visit(RuntimeVisitor& vis) override {
		vis && pathways;
	}
	
public:
	SYS_RTTI(EonLoader)
	SYS_CTOR(EonLoader);
	
	bool LoadFile(String path);
	bool Load(String content, String filepath="temp");
	
protected:
	
    bool Initialize() override;
    void Start() override;
    void Update(double dt) override;
    void Stop() override;
    void Uninitialize() override;
    
    
};

using EonLoaderRef = Ref<EonLoader, RefParent1<Machine>>;



NAMESPACE_TOPSIDE_END

#endif
