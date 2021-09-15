#ifndef _AtomSDL2_Context_h_
#define _AtomSDL2_Context_h_


#if HAVE_MANUAL_SDL_CLASSES

NAMESPACE_SERIAL_BEGIN


class SDL2ContextBase :
	public SDL2BaseT<SDL2ContextBase>
{
	One<OOSDL2::Context>		obj;
	LinkedList<AtomBaseRef>		atoms;
	
public:
	RTTI_DECL1(SDL2ContextBase, AltBaseT)
	COPY_PANIC(SDL2ContextBase);
	ATOM_DEF_VISIT
	
	SDL2ContextBase();
	
	bool AltInitialize(const Script::WorldState& ws) override;
	void AltUninitialize() override;
	void AltForward(FwdScope& fwd) override;
	bool AltPostInitialize() override;
	
	OOSDL2::Context* GetOOSDL2() {return &*obj;}
	OOSDL2::Component& GetObj() override {Panic("never"); NEVER();}
	
	void Add(AtomBaseRef sdlbase);
	
};

using SDL2ContextBaseRef		= Ref<SDL2ContextBase,			RefParent1<Loop>>;


NAMESPACE_SERIAL_END

#endif
#endif
