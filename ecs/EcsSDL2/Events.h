#ifndef _EcsSDL2_Events_h_
#define _EcsSDL2_Events_h_

NAMESPACE_TOPSIDE_BEGIN


class SDL2EventsComponent :
	public Component<SDL2EventsComponent>,
	public EventSource
{
	
	struct Local : public SimpleBufferedEvent {
		
	};
	
	struct LocalStream : public SimpleBufferedEventStream {
		RTTI_DECL1(LocalStream, SimpleBufferedEventStream)
		SDL2EventsComponent& par;
		LocalStream(SDL2EventsComponent* par) :
			par(*par),
			SimpleBufferedEventStream(par->value) {}
		bool			IsOpen() const override;
		bool			Open(int fmt_idx) override;
		void			Close() override {par.obj->Close();}
		bool			IsEof() override {return par.obj.IsEmpty();}
		bool			ReadFrame() override {return par.ReadFrame();}
		bool			ProcessFrame() override {return par.ProcessFrame();}
		bool			ProcessOtherFrame() override {return false;}
		void			ClearPacketData() override {}
	};
	
	
	
	One<OOSDL2::Events> obj;
	Vector<byte> tmp_events;
	Local value;
	LocalStream stream;
	
	CtrlEvent& AddTmpEvent();
	
public:
	RTTI_COMP1(SDL2EventsComponent, EventSource)
	VIS_COMP_1_0(Event)
	COPY_PANIC(SDL2EventsComponent);
	IFACE_CB(EventSource);
	IFACE_GENERIC;
	
	SDL2EventsComponent() : stream(this) {}
	
	void				Initialize() override;
	void				Uninitialize() override;
	void				Visit(RuntimeVisitor& vis) override {}
	EventStream&		GetStream(EvCtx) override {return stream;}
	void				BeginStream(EvCtx) override {stream.FillBuffer();}
	void				EndStream(EvCtx) override {stream.DropBuffer();}
	
	bool				ReadFrame();
	bool				ProcessFrame();
	OOSDL2::Component&	GetObj() {return *obj;}
	OOSDL2::Events*		GetOOSDL2() {return &*obj;}
	
};


NAMESPACE_TOPSIDE_END

#endif
