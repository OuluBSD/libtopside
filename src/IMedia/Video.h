#ifndef _IMedia_Video_h_
#define _IMedia_Video_h_

NAMESPACE_PARALLEL_BEGIN


template <class Backend>
class VideoCodecFormatT {
	
public:
	uint32			pix_fmt = 0;
	
};

template <class Backend>
class VideoSourceFormatResolutionT {
	
protected:
	friend class V4L2_DeviceManager;
	
	VideoFormat		fmt;
	
public:
	
	VideoFormat		GetFormat() const {return fmt;}
	
	void			SetFormat(VideoFormat fmt) {this->fmt = fmt;}
	
};

template <class Backend>
class VideoSourceFormatT {
	
protected:
	friend class V4L2_DeviceManager;
	
	using VideoCodecFormat = VideoCodecFormatT<Backend>;
	using VideoSourceFormatResolution = VideoSourceFormatResolutionT<Backend>;
	
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
	
	
};




template <class Backend>
class VideoInputFrameT : public PacketBufferBase {
	
public:
	RTTI_DECL1(VideoInputFrameT, PacketBufferBase)
	
	
	Format fmt;
	
	const Format&		GetFormat() const {return fmt;}
	
};

template <class Backend>
class VideoOutputFrameT : public PacketBufferBase {
	
public:
	RTTI_DECL1(VideoOutputFrameT, PacketBufferBase)
	
};








template <class Backend>
class VideoLoaderBaseT :
	public AtomBase
{
	String	filepath;
	bool	vflip = false;
	
public:
	VideoLoaderBaseT();
	
	bool Initialize(const Script::WorldState& ws) override;
	void Uninitialize() override;
	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override;
	void Visit(RuntimeVisitor& vis) override {}
	
	bool LoadFile();
	
};


NAMESPACE_PARALLEL_END

#endif
