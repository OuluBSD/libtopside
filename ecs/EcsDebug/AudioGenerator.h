#ifndef _EcsDebug_AudioGenerator_h_
#define _EcsDebug_AudioGenerator_h_

NAMESPACE_ECS_BEGIN

using namespace Ecs;

template <class T>
class DebugSoundGenerator
{
	Vector<T> frame;
	int frame_part_size = 0;
	
public:
	DebugSoundGenerator() {}
	void Play(int frame_offset, const Packet& p) {
		int total_bytes = frame.GetCount() * sizeof(T);
		frame_offset = frame_offset % total_bytes;
		int copy_size = p->GetFormat().GetFrameSize();
		p->Data().SetCount(copy_size, 0);
		int frame_remaining = total_bytes - frame_offset;
		byte* dst = p->Data().Begin();
		byte* src = (byte*)(void*)frame.Begin() + frame_offset;
		
		// 2 parts
		if (frame_remaining < copy_size) {
			int right_side = frame_remaining;
			int left_side = copy_size - frame_remaining;
			memcpy(dst, src, right_side);
			src = (byte*)(void*)frame.Begin();
			memcpy(dst, src, left_side);
			//frame_offset = left_side;
		}
		// 1part
		else {
			memcpy(dst, src, copy_size);
			//frame_offset = (frame_offset + copy_size) % total_bytes;
		}
	}
	
	void GenerateStereoSine(const AudioFormat& fmt) {
		ASSERT(fmt.IsSampleType<T>());
		double pan_loop_seconds = 2.0;
		int tone_mul = 4;
		int pan_frames = (int)(fmt.freq * pan_loop_seconds / fmt.sample_rate);
		int pan_samples = pan_frames * fmt.sample_rate;
		int pan_i = 0;
		frame_part_size = fmt.sample_rate * fmt.channels;
		int size = frame_part_size * pan_frames;
		frame.SetCount(size);
		T* f = frame.Begin();
		for (int p = 0; p < pan_frames; p++) {
			for(int i = 0; i < fmt.sample_rate; i++) {
				double tonerad = tone_mul * M_2PI * (double)i / (double)fmt.sample_rate;
				double tonesin = FastSin(tonerad);
				double tonevol = (tonesin + 1.0) * 0.5;
				double panrad = M_2PI * (double)pan_i / (double)pan_samples;
				double pansin = FastSin(panrad);
				double panvol = (pansin + 1.0) * 0.5;
				for(int j = 0; j < fmt.channels; j++) {
					double pan = (j % 2 == 0) ? panvol : (1.0 - panvol);
					//pan = j == 0  ? 1.0 : 0.0;
					double value = pan * tonesin;
					//value = tonesin;
					*f = ConvertAudioSample<double, T>(value);
					f++;
				}
				pan_i++;
			}
		}
		ASSERT(f == frame.End());
	}
};




class DebugAudioGeneratorExt :
	public AudioInputExt
{
	DebugSoundGenerator<uint8> gen;
	Ecs::Format fmt;
	String last_error;
	int mode = 0;
	int preset_i = -1;
	
	enum {
		MODE_NONE,
		MODE_TRACK_NUM,
	};
	
	void GenerateStereoSine(const AudioFormat& fmt);
	
public:
	DebugAudioGeneratorExt();
	
	bool Initialize(const Eon::WorldState& ws) override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
	void Forward(FwdScope& fwd) override;
	void StorePacket(int sink_ch,  int src_ch, Packet& p) override;
	
	EXT_MAKE_ACTION_BEGIN
	if (cls.sub == SubCompCls::INPUT) {
		EXT_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.src.dbg_generator")
	}
	else if (cls.sub == SubCompCls::CONVERTER) {
		TODO
		/*ASSERT(cls.src.val.type == ValCls::AUDIO);
		String s = cls.sink.GetActionName() + ".convert." + cls.src.val.GetActionName() + ".dbg";
		EXT_MAKE_ACTION_UNDEF_TO_TRUE(s)*/
	}
	EXT_MAKE_ACTION_END
	
	
	static EcsTypeCls::Type		GetEcsType() {return EcsTypeCls::EXT_DBG_AUDIO_IN;}
	
	void SetPreset(int i) {preset_i = i;}
	String GetLastError() const {return last_error;}
	
	
};


NAMESPACE_ECS_END

#endif
