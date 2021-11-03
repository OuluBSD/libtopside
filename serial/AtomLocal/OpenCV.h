#ifndef _AtomLocal_OpenCV_h_
#define _AtomLocal_OpenCV_h_

#if HAVE_OPENCV

NAMESPACE_SERIAL_BEGIN


class OpenCVBase :
	public virtual AtomBase
{
	Format					fmt;
	String					last_error;
	OpenCVCaptureDevice*	cap = 0;
	V4L2_DeviceManager		devmgr;
	Size					def_cap_sz;
	int						def_cap_fps;
	int						prev_frame_i = -1;
	bool					vflip = false;
	
	
public:
	OpenCVBase();
	
	bool			Initialize(const Script::WorldState& ws) override;
	void			Uninitialize() override;
	bool			ProcessPackets(PacketIO& io) override;
	bool			IsReady(PacketIO& io) override;
	void			Visit(RuntimeVisitor& vis) override {/*vis % devmgr;*/}
	String			GetLastError() const {return last_error;}
	
	
	
};


NAMESPACE_SERIAL_END

#endif
#endif
