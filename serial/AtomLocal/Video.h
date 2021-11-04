#ifndef _AtomLocal_Video_h_
#define _AtomLocal_Video_h_

NAMESPACE_SERIAL_BEGIN


struct VideoCodecFormat {
	uint32			pix_fmt = 0;
	
};

class VideoSourceFormatResolution {
	
protected:
	friend class V4L2_DeviceManager;
	
	VideoFormat		fmt;
	
public:
	
	VideoFormat		GetFormat() const {return fmt;}
	
	void			SetFormat(VideoFormat fmt) {this->fmt = fmt;}
	
};

class VideoSourceFormat {
	
protected:
	friend class V4L2_DeviceManager;
	
	String								desc;
	VideoCodecFormat					codec;
	Array<VideoSourceFormatResolution>	res;
	
	VideoSourceFormatResolution&		GetResolution(int i) {return res[i];}
	
	
public:
	
	VideoSourceFormatResolution&		Add() {return res.Add();}
	void								SetDescription(String s) {desc = s;}
	
	String								GetDescription() const {return desc;}
	int									GetResolutionCount() const {return res.GetCount();}
	const VideoSourceFormatResolution&	GetResolution(int i) const {return res[i];}
	VideoCodecFormat					GetCodecFormat() const {return codec;}
	
	VideoSourceFormatResolution&		operator[](int i) {return res[i];}
	const VideoSourceFormatResolution&	operator[](int i) const {return res[i];}
	
	// IsMJPEG(): is src v4l2 and pix_fmt V4L2_PIX_FMT_MJPEG
	
};




class VideoInputFrame : public PacketBufferBase {
	
protected:
	friend class V4L2_DeviceManager;
	
public:
	RTTI_DECL1(VideoInputFrame, PacketBufferBase)
	
	
	Format fmt;
	
	const Format&		GetFormat() const {return fmt;}
	
};

using VideoInputFrameRef = Ref<VideoInputFrame>;


class VideoOutputFrame : public PacketBufferBase {
	
protected:
	friend class V4L2_DeviceManager;
	
	
public:
	RTTI_DECL1(VideoOutputFrame, PacketBufferBase)
	
};








class DebugVideoGenerator {
	using T = byte;
	
	Vector<T> frame;
	int frame_part_size = 0;
	
	
public:
	typedef DebugVideoGenerator CLASSNAME;
	DebugVideoGenerator();
	
	
	void Play(int frame_offset, const Packet& p);
	void GenerateNoise(const VideoFormat& fmt);
	void GenerateSine(const VideoFormat& fmt);
	uint64 GetMaxOffset() const {return frame.GetCount();}
	
};

class VideoGenBase :
	public virtual AtomBase
{
	DebugVideoGenerator		gen;
	Format					fmt;
	String					last_error;
	int						mode = 0;
	int						preset_i = -1;
	
	enum {
		MODE_NONE,
		MODE_TRACK_NUM,
	};
	
	void GenerateStereoSine(const VideoFormat& fmt);
	
public:
	VideoGenBase();
	
	bool Initialize(const Script::WorldState& ws) override;
	void Uninitialize() override;
	void Forward(FwdScope& fwd) override;
	bool ProcessPackets(PacketIO& io) override;
	void Visit(RuntimeVisitor& vis) override {}
	
	void SetPreset(int i) {preset_i = i;}
	String GetLastError() const {return last_error;}
	
	
};

class VideoLoaderBase :
	public virtual AtomBase
{
	String	filepath;
	bool	vflip = false;
	
public:
	VideoLoaderBase();
	
	bool Initialize(const Script::WorldState& ws) override;
	void Uninitialize() override;
	void Forward(FwdScope& fwd) override;
	bool ProcessPackets(PacketIO& io) override;
	void Visit(RuntimeVisitor& vis) override {}
	
	bool LoadFile();
	
};


NAMESPACE_SERIAL_END

#endif
