#ifndef _VirtualGui3D_Direct_h_
#define _VirtualGui3D_Direct_h_


NAMESPACE_ECS_BEGIN


class DirectWindow :
	public Component<DirectWindow>
{
	//static uint32 prev_ticks;
	
	
public:
	COPY_PANIC(DirectWindow)
	COMP_DEF_VISIT
	
	//IFACE_CB(DisplaySink);
	//IFACE_CB(AudioSink);
	//IFACE_CB(ControllerSource);
	//IFACE_CB(ReadFileSink);
	//IFACE_CB(VideoSink);
	
	
	DirectWindow();
	
	void Initialize() override;
	void Uninitialize() override;
	
	/*void EmitCtrlEvent(const CtrlEvent& e) override;
	
	void RecvDisplay(DisplaySource& src, double dt) override;
	void RecvAudio(AudioSource& src, double dt) override;
	
	void SetTitle(String title) override;*/
	
	Callback WhenClose;
	
};


NAMESPACE_ECS_END


#endif
