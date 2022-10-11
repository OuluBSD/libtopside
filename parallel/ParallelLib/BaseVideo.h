#ifndef _ParallelLib_BaseVideo_h_
#define _ParallelLib_BaseVideo_h_

#if defined flagSCREEN

NAMESPACE_PARALLEL_BEGIN


struct BufferWriterBase {
	
};


class DebugVideoGenerator {
	using T = byte;
	
	Vector<T> frame;
	int frame_part_size = 0;
	
	
public:
	typedef DebugVideoGenerator CLASSNAME;
	DebugVideoGenerator();
	
	
	void Play(int frame_offset, PacketValue& p);
	void Play(int frame_offset, BufferWriterBase& buf);
	void GenerateNoise(const VideoFormat& fmt);
	void GenerateSine(const VideoFormat& fmt);
	uint64 GetMaxOffset() const {return frame.GetCount();}
	
	
};

class VideoGenBase :
	public virtual Atom
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
	RTTI_DECL1(VideoGenBase, Atom)
	VideoGenBase();
	
	bool Initialize(const Script::WorldState& ws) override;
	void Uninitialize() override;
	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override;
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	void SetPreset(int i) {preset_i = i;}
	String GetLastError() const {return last_error;}
	
	
};


NAMESPACE_PARALLEL_END

#endif
#endif
