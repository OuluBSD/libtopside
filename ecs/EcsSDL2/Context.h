#ifndef _EcsSDL2_Context_h_
#define _EcsSDL2_Context_h_

NAMESPACE_TOPSIDE_BEGIN



class SDL2ContextComponent :
	public Component<SDL2ContextComponent>
{
	One<OOSDL2::Context> obj;
	LinkedList<ComponentBaseRef> comps;
	
public:
	RTTI_COMP0(SDL2ContextComponent)
	VIS_COMP_0_0
	COPY_PANIC(SDL2ContextComponent);
	
	SDL2ContextComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
	
	OOSDL2::Context* GetOOSDL2() {return &*obj;}
	
};

using SDL2ContextComponentRef		= Ref<SDL2ContextComponent,			RefParent1<Entity>>;


NAMESPACE_TOPSIDE_END

#endif
