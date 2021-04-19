#ifndef _Multimedia_System_h_
#define _Multimedia_System_h_

#include <EcsLib/EcsLib.h>
#include "Multimedia.h"

NAMESPACE_OULU_BEGIN


struct MultiMediaInput : Moveable<MultiMediaInput> {
	String path;
	RunningFlagSingle flag;
	TimeStop step_time;
	String last_error;
	MediaStream* cap = 0;
	bool new_frame = false;
	
	
	typedef MultiMediaInput CLASSNAME;
	MultiMediaInput() {}
	~MultiMediaInput() {Stop(); Clear();}
	
	void Clear();
	void Start();
	void Stop();
	void Process();
#ifdef flagOPENGL
	void PaintOpenGL(GLuint active_tex);
#endif
	bool TestClearNewFrame() {bool b = new_frame; new_frame = false; return b;}
	
	String GetLastError() const {return last_error;}
	
	Callback WhenError;
	
};


class MultiMediaComponent :
	public Component<MultiMediaComponent>,
	public MediaSource
{
	String last_error;
	MediaDeviceManager devmgr;
	MultiMediaInput vi;
	MediaPtrBuffer media_buf;
	Size def_cap_sz;
	int def_cap_fps;
	
public:
	COPY_PANIC(MultiMediaComponent);
	IFACE_CB(MediaSource);
	IFACE_GENERIC;
	
	MultiMediaComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	
	bool LoadFileAny(String path) override;
	void EmitMedia() override;
	
	bool LoadInput(int id);
	
	String GetLastError() const {return last_error;}
	
	MultiMediaInput& GetInput() {return vi;}
	MediaPtrBuffer& GetMedia() {return media_buf;}
	
	static bool AllowDuplicates() {return true;}
	
};



NAMESPACE_OULU_END

#endif
