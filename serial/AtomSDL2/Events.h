#ifndef _AtomSDL2_Events_h_
#define _AtomSDL2_Events_h_

#if HAVE_MANUAL_SDL_CLASSES

NAMESPACE_SERIAL_BEGIN


class SDL2EventsBase :
	public SDL2BaseT<SDL2EventsBase>
{
	
	struct Local : public SimpleBufferedValue {
		
	};
	
	struct LocalStream : public SimpleBufferedStream {
		RTTI_DECL1(LocalStream, SimpleBufferedStream)
		SDL2EventsBase& par;
		LocalStream(SDL2EventsBase* par) :
			par(*par),
			SimpleBufferedStream(par->value) {}
		bool			IsOpen() const override;
		bool			Open(int fmt_idx) override;
		void			Close() override {par.obj->Close();}
		bool			IsEof() override {return par.obj.IsEmpty();}
		bool			ReadFrame() override {return par.ReadFrame();}
		bool			ProcessFrame() override {return par.ProcessFrame();}
		bool			ProcessOtherFrame() override {return false;}
		void			ClearPacketData() override {}
	};
	
	
	
	One<OOSDL2::Events>	obj;
	Vector<byte>		tmp_events;
	Local				value;
	LocalStream			stream;
	
	CtrlEvent& AddTmpEvent();
	
public:
	RTTI_DECL1(SDL2EventsBase, AltBaseT)
	COPY_PANIC(SDL2EventsBase)
	ATOM_DEF_VISIT
	
	SDL2EventsBase() : stream(this) {}
	
	bool				AltInitialize(const Script::WorldState& ws) override;
	void				AltUninitialize() override;
	
	/*EventStream&		GetStream(EvCtx) override {return stream;}
	void				BeginStream(EvCtx) override {stream.FillBuffer();}
	void				EndStream(EvCtx) override {stream.DropBuffer();}*/
	
	bool				ReadFrame();
	bool				ProcessFrame();
	OOSDL2::Component&	GetObj() override {return *obj;}
	OOSDL2::Events*		GetOOSDL2() {return &*obj;}
	
};


NAMESPACE_SERIAL_END

#endif
#endif
