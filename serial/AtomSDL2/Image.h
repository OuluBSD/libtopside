#ifndef _AtomSDL2_Image_h_
#define _AtomSDL2_Image_h_

#if HAVE_MANUAL_SDL_CLASSES

NAMESPACE_SERIAL_BEGIN



class SDL2ImageBase :
	public SDL2BaseT<SDL2ImageBase>
{
	struct Local : public SimpleBufferedValue {
		RTTI_DECL1(Local, SimpleBufferedValue)
		SDL2ImageBase& par;
		Local(SDL2ImageBase* par) : par(*par) {}
		
	};
	struct LocalStream : public SimpleBufferedStream {
		RTTI_DECL1(LocalStream, SimpleBufferedStream)
		SDL2ImageBase& par;
		LocalStream(SDL2ImageBase* par) : par(*par), SimpleBufferedStream(par->svalue) {}
		bool			IsOpen() const override {return par.IsOpen();}
		bool			Open(int fmt_idx) override {ASSERT(fmt_idx == 0); return par.Open(fmt_idx);}
		void			Close() override {par.Close();}
		bool			IsEof() override {return !par.IsOpen();}
		bool			ReadFrame() override {return par.ReadFrame();}
		bool			ProcessFrame() override {return par.ProcessFrame();}
		bool			ProcessOtherFrame() override {return false;}
		void			ClearPacketData() override {par.ClearPacketData();}
	};
	
	Vector<Image>				img;
	String						last_error;
	Local						svalue;
	LocalStream					sstream;
	
public:
	RTTI_DECL1(SDL2ImageBase, AltBaseT)
	COPY_PANIC(SDL2ImageBase)
	ATOM_DEF_VISIT
	
	SDL2ImageBase();
	
	bool AltInitialize(const Script::WorldState& ws) override;
	void AltUninitialize() override;
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
	
	static bool AllowDuplicates() {return true;}
	
};

using SDL2ImageBaseRef			= Ref<SDL2ImageBase,			RefParent1<Loop>>;


NAMESPACE_SERIAL_END

#endif
#endif
