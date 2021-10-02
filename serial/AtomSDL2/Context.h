#ifndef _AtomSDL2_Context_h_
#define _AtomSDL2_Context_h_


#if HAVE_MANUAL_SDL_CLASSES

NAMESPACE_SERIAL_BEGIN


class SDL2ContextBase :
	public SDL2BaseT<SDL2ContextBase>,
	public CenterDriver
{
	One<OOSDL2::Context>		obj;
	LinkedList<AtomBaseRef>		atoms;
	
public:
	RTTI_DECL2(SDL2ContextBase, AltBaseT, CenterDriver)
	COPY_PANIC(SDL2ContextBase);
	
	SDL2ContextBase();
	
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<AltBaseT>(this); vis.VisitThis<CenterDriver>(this);}
	bool Initialize(const Script::WorldState& ws) override;
	void Uninitialize() override;
	void Forward(FwdScope& fwd) override;
	bool PostInitialize() override;
	
	OOSDL2::Context* GetOOSDL2() {return &*obj;}
	OOSDL2::Component& GetObj() override {Panic("never"); NEVER();}
	
	void Add(AtomBaseRef sdlbase);
	
};

using SDL2ContextBaseRef		= Ref<SDL2ContextBase,			RefParent1<Loop>>;


NAMESPACE_SERIAL_END

#endif
#endif
