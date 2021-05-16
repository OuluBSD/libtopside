#ifndef _VirtualGui3DAlt_Direct_h_
#define _VirtualGui3DAlt_Direct_h_


NAMESPACE_TOPSIDE_BEGIN


class DirectWindow :
	public Component<CoreWindow>
{
    DisplaySinkRef scr;
	//static uint32 prev_ticks;
	
	
public:
	VIS_COMP_0_0
	void Visit(RuntimeVisitor& vis) override {}
	
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


NAMESPACE_TOPSIDE_END


#endif
