#ifndef _AtomSDL2_Image_h_
#define _AtomSDL2_Image_h_

#if HAVE_MANUAL_SDL_CLASSES

NAMESPACE_SERIAL_BEGIN



class SDL2ImageBase :
	public SDL2BaseT<SDL2ImageBase>
{
	One<OOSDL2::Image>			obj;
	Vector<Image>				imgs;
	String						last_error;
	
public:
	RTTI_DECL1(SDL2ImageBase, AltBaseT)
	COPY_PANIC(SDL2ImageBase)
	ATOM_DEF_VISIT
	
	SDL2ImageBase();
	
	bool			Initialize(const Script::WorldState& ws) override;
	void			Uninitialize() override;
	bool			ProcessPackets(PacketIO& io) override;
	bool			IsReady(PacketIO& io) override;
	
	OOSDL2::Component&	GetObj() override {return *obj;}
	OOSDL2::Image*		GetOOSDL2() {return &*obj;}
	
	bool			LoadFileAny(String path);
	Size			GetResolution() const;
	
	bool			IsOpen() const {return !imgs.IsEmpty();}
	bool			Open(int) {return !imgs.IsEmpty();}
	void			Close() {imgs.Clear();}
	bool			ReadFrame() {return true;}
	bool			ProcessFrame() {return true;}
	void			ClearPacketData() {}
	
	String GetLastError() const {return last_error;}
	
	
};

using SDL2ImageBaseRef			= Ref<SDL2ImageBase,			AtomParent>;


NAMESPACE_SERIAL_END

#endif
#endif
