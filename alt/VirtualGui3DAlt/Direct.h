#ifndef _VirtualGui3DAlt_Direct_h_
#define _VirtualGui3DAlt_Direct_h_


NAMESPACE_OULU_BEGIN


class DirectWindow :
	public Component<CoreWindow>
{
    DisplaySink* scr = 0;
	//static uint32 prev_ticks;
	
	
public:
	
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


NAMESPACE_OULU_END


#endif
