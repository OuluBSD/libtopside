#ifndef _AtomSDL2_GameController_h_
#define _AtomSDL2_GameController_h_

#if HAVE_MANUAL_SDL_CLASSES

NAMESPACE_SERIAL_BEGIN



class SDL2GameControllerBase :
	public SDL2BaseT<SDL2GameControllerBase>
{
	One<OOSDL2::GameController> obj;
	
public:
	RTTI_DECL1(SDL2GameControllerBase, AltBaseT)
	COPY_PANIC(SDL2GameControllerBase)
	ATOM_DEF_VISIT
	
	SDL2GameControllerBase() = default;
	
	bool AltInitialize(const Script::WorldState& ws) override;
	void AltUninitialize() override;
	//bool IsSupported(CtrlType type) override {return type == CTRL_GAMEPAD;}
	/*HumanStream&		GetStream(HumCtx) override {TODO}
	void				BeginStream(HumCtx) override {TODO}
	void				EndStream(HumCtx) override {TODO}*/
	
	OOSDL2::Component& GetObj() override {return *obj;}
	OOSDL2::GameController* GetOOSDL2() {return &*obj;}
	
};



NAMESPACE_SERIAL_END

#endif
#endif
