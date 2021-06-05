#ifndef _EcsSDL2_Context_h_
#define _EcsSDL2_Context_h_

NAMESPACE_TOPSIDE_BEGIN



class SDL2ContextConnector :
	public Connector<SDL2ContextConnector>
{
	One<OOSDL2::Context> obj;
	LinkedList<ComponentBaseRef> comps;
	
public:
	RTTI_CONN0(SDL2ContextConnector)
	COPY_PANIC(SDL2ContextConnector);
	
	SDL2ContextConnector();
	
	void Initialize() override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
	
	OOSDL2::Context* GetOOSDL2() {return &*obj;}
	
};

using SDL2ContextConnectorRef		= Ref<SDL2ContextConnector,			RefParent1<Entity>>;


NAMESPACE_TOPSIDE_END

#endif
