#ifndef _AtomSDL2_System_h_
#define _AtomSDL2_System_h_

#if 0

#if HAVE_MANUAL_SDL_CLASSES

NAMESPACE_SERIAL_BEGIN



class SDL2System : public System<SDL2System> {
	LinkedList<AtomBaseRef> atoms;
	
	TS::Serial::OOSDL2::Context ctx;
	OOSDL2::Image img;
	OOSDL2::Font fnt;
	
	
public:
	SYS_RTTI(SDL2System)
	SYS_CTOR(SDL2System)
	SYS_DEF_VISIT_(vis && atoms)
	const LinkedList<AtomBaseRef>& GetContext() const {return atoms;}
	
protected:
	friend class Font;
	friend class CoreWindow;
	
    bool AltInitialize(const Script::WorldState& ws) override;
    void Start() override;
    void Update(double dt) override;
    void Stop() override;
    void AltUninitialize() override;
    
protected:
	friend class SDL2Context;
	void AddContext(AtomBaseRef comp);
	void RemoveContext(AtomBaseRef comp);
	
};




NAMESPACE_SERIAL_END

#endif
#endif
#endif
