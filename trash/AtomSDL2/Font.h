#ifndef _AtomSDL2_Font_h_
#define _AtomSDL2_Font_h_

#if HAVE_MANUAL_SDL_CLASSES

NAMESPACE_SERIAL_BEGIN



class SDL2FontBase :
	public SDL2BaseT<SDL2FontBase>
{
	Font fnt;
	
public:
	RTTI_DECL1(SDL2FontBase, AltBaseT)
	COPY_PANIC(SDL2FontBase)
	ATOM_DEF_VISIT
	
	SDL2FontBase() = default;
	
	bool Initialize(const Script::WorldState& ws) override;
	void Uninitialize() override;
	
	
};

 

NAMESPACE_SERIAL_END

#endif
#endif
