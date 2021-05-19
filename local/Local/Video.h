#ifndef _Local_Video_h_
#define _Local_Video_h_

NAMESPACE_TOPSIDE_BEGIN


struct VideoFormat {
	Size res = {0,0};
	int depth = 0; // volume video is a thing
	double fps = 0;
	int var_size = 0;
	int channels = 0;
	int pitch = 0;
	String codec;
	
	void Clear();
	bool IsValid() const {return res.cx > 0 && res.cy > 0 && depth > 0 && fps > 0 && var_size > 0 && channels > 0 && pitch >= GetMinPitch();}
	int GetMinPitch() const {return res.cx * channels * var_size;}
	void SetLinePadding(int bytes) {ASSERT(bytes >= 0); pitch = GetMinPitch() + bytes;}
	void SetPitch(int bytes) {pitch = bytes; ASSERT(bytes >= GetMinPitch());}
	Size GetSize() const {return res;}
	int GetDepth() const {return depth;}
	int GetFrameBytes() const {return res.cy * pitch;}
	bool operator!=(const VideoFormat& fmt) const {return !(*this == fmt);}
	bool operator==(const VideoFormat& fmt) const {
		return	res == fmt.res &&
				depth == fmt.depth &&
				fps == fmt.fps &&
				var_size == fmt.var_size &&
				channels == fmt.channels &&
				pitch == fmt.pitch &&
				codec == fmt.codec
				;
	}
	
};

VideoFormat MakeVideoFormat(Size res, double fps, int var_size, int channels, int pitch, int depth=1, String codec=String());


LOCAL_CTX(Video, DummyValueBase, DummyStreamBase)
#define VIDCTX VideoContext::Static()
#define VidCtx VideoContext&


NAMESPACE_TOPSIDE_END

#endif
