#ifndef _EcsSDL2_Events_h_
#define _EcsSDL2_Events_h_

NAMESPACE_TOPSIDE_BEGIN


class SDL2EventsComponent :
	public Component<SDL2EventsComponent>,
	public DeviceSource
{
	
	struct LocalDevice : public SimpleBufferedDevice {
		
	};
	
	struct LocalDeviceStream : public SimpleBufferedDeviceStream {
		RTTI_DECL1(LocalDeviceStream, SimpleBufferedDeviceStream)
		SDL2EventsComponent& par;
		LocalDeviceStream(SDL2EventsComponent* par) :
			par(*par),
			SimpleBufferedDeviceStream(par->value) {}
		bool			IsOpen() const override;
		bool			Open(int fmt_idx) override;
		void			Close() override {par.obj->Close();}
		bool			IsEof() override {return par.obj.IsEmpty();}
		bool			ReadFrame() override {return par.ReadFrame();}
		bool			ProcessFrame() override {return par.ProcessDeviceFrame();}
		bool			ProcessOtherFrame() override {return false;}
		void			ClearPacketData() override {}
	};
	
	
	
	One<OOSDL2::Events> obj;
	Vector<byte> tmp_events;
	LocalDevice value;
	LocalDeviceStream stream;
	
	CtrlEvent& AddTmpEvent();
	
public:
	RTTI_COMP1(SDL2EventsComponent, DeviceSource)
	VIS_COMP_1_0(Device)
	COPY_PANIC(SDL2EventsComponent);
	IFACE_CB(DeviceSource);
	IFACE_GENERIC;
	
	SDL2EventsComponent() : stream(this) {}
	
	void				Initialize() override;
	void				Uninitialize() override;
	void				Visit(RuntimeVisitor& vis) override {}
	DeviceStream&		GetStream(DevCtx) override {return stream;}
	void				BeginStream(DevCtx) override {stream.FillBuffer();}
	void				EndStream(DevCtx) override {stream.DropBuffer();}
	
	bool				ReadFrame();
	bool				ProcessDeviceFrame();
	OOSDL2::Component&	GetObj() {return *obj;}
	OOSDL2::Events*		GetOOSDL2() {return &*obj;}
	
};


NAMESPACE_TOPSIDE_END

#endif
