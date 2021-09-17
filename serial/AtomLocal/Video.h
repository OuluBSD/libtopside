#ifndef _AtomLocal_Video_h_
#define _AtomLocal_Video_h_

NAMESPACE_SERIAL_BEGIN


class VideoInputFrame : public PacketBufferBase {
	
protected:
	friend class V4L2_DeviceManager;
	
public:
	RTTI_DECL1(VideoInputFrame, PacketBufferBase)
	
	
	Format fmt;
	
};

using VideoInputFrameRef = Ref<VideoInputFrame>;


class VideoOutputFrame : public PacketBufferBase {
	
protected:
	friend class V4L2_DeviceManager;
	
	
public:
	RTTI_DECL1(VideoOutputFrame, PacketBufferBase)
	
};

struct DataPtrVideoBuffer : public PacketBufferBasePtr {
	RTTI_DECL1(DataPtrVideoBuffer, PacketBufferBasePtr)
	
	
	void* data = 0;
	Format fmt;
	int type = 0;
	
	enum {
		UNKNOWN,
		OPENCV
	};
	
	void SetOpenCVFormat(Format fmt) {this->fmt = fmt; type = OPENCV;}
	
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
	
	bool AltInitialize(const Script::WorldState& ws) override;
	void AltUninitialize() override;
	void AltForward(FwdScope& fwd) override;
	void AltStorePacket(Packet& p) override;
	
	void Visit(RuntimeVisitor& vis) override {}
	
	void SetPreset(int i) {preset_i = i;}
	String GetLastError() const {return last_error;}
	
	
};


class AccelVideoGenBase :
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
	AccelVideoGenBase();
	
	bool AltInitialize(const Script::WorldState& ws) override;
	void AltUninitialize() override;
	void AltForward(FwdScope& fwd) override;
	void AltStorePacket(Packet& p) override;
	
	void Visit(RuntimeVisitor& vis) override {}
	
	void SetPreset(int i) {preset_i = i;}
	String GetLastError() const {return last_error;}
	
	
};


NAMESPACE_SERIAL_END

#endif
