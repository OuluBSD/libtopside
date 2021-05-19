#ifndef _Local_Display_h_
#define _Local_Display_h_

NAMESPACE_TOPSIDE_BEGIN


struct DisplayFormat {
	VideoFormat vid;
	double fps;
	
	void Clear() {vid.Clear();}
	bool IsValid() const {return vid.IsValid();}
	double GetFrameSeconds() const {return 1.0 / fps;}
	bool operator!=(const DisplayFormat& fmt) const {return !(*this == fmt);}
	bool operator==(const DisplayFormat& fmt) const {
		return	vid == fmt.vid &&
				fps == fmt.fps
				;
	}
	
};


LOCAL_CTX(Display, DummyValueBase, DummyStreamBase)
#define DISCTX DisplayContext::Static()
#define DisCtx DisplayContext&


NAMESPACE_TOPSIDE_END

#endif
