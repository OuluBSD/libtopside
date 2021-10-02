#ifndef _AtomSDL2_Image_h_
#define _AtomSDL2_Image_h_

#if HAVE_MANUAL_SDL_CLASSES

NAMESPACE_SERIAL_BEGIN



class SDL2ImageBase :
	public SDL2BaseT<SDL2ImageBase>
{
	Vector<Image>				img;
	String						last_error;
	
public:
	RTTI_DECL1(SDL2ImageBase, AltBaseT)
	COPY_PANIC(SDL2ImageBase)
	ATOM_DEF_VISIT
	
	SDL2ImageBase();
	
	bool Initialize(const Script::WorldState& ws) override;
	void Uninitialize() override;
	bool LoadFileAny(String path);
	Size GetResolution() const;
	
	/*StaticStream&		GetStream(StcCtx) override;
	void				BeginStream(StcCtx) override;
	void				EndStream(StcCtx) override;*/
	
	bool				IsOpen() const {return !img.IsEmpty();}
	bool				Open(int) {return !img.IsEmpty();}
	void				Close() {img.Clear();}
	bool				ReadFrame() {return true;}
	bool				ProcessFrame() {return true;}
	void				ClearPacketData() {}
	String GetLastError() const {return last_error;}
	
	
};

using SDL2ImageBaseRef			= Ref<SDL2ImageBase,			RefParent1<Loop>>;


NAMESPACE_SERIAL_END

#endif
#endif
