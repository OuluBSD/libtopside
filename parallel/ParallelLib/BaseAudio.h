#ifndef _ParallelLib_BaseAudio_h_
#define _ParallelLib_BaseAudio_h_


NAMESPACE_PARALLEL_BEGIN


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
	
	void GenerateNoise(const AudioFormat& fmt) {
		ASSERT(fmt.IsSampleType<T>());
		double pan_loop_seconds = 2.0;
		int tone_mul = 4;
		int pan_frames = (int)(fmt.freq * pan_loop_seconds / fmt.sample_rate);
		int pan_samples = pan_frames * fmt.sample_rate;
		frame_part_size = fmt.sample_rate * fmt.res[0];
		int size = frame_part_size * pan_frames;
		frame.SetCount(size);
		T* f = frame.Begin();
		auto& rng = RNG::Local();
		for (int p = 0; p < pan_frames; p++) {
			for(int i = 0; i < fmt.sample_rate; i++) {
				for(int j = 0; j < fmt.res[0]; j++) {
					*f = ConvertAudioSample<double, T>(rng.Randomf());
					f++;
				}
			}
		}
		ASSERT(f == frame.End());
	}
	
	void GenerateStereoSine(const AudioFormat& fmt) {
		ASSERT(fmt.IsSampleType<T>());
		double pan_loop_seconds = 2.0;
		int tone_mul = 4;
		int pan_frames = (int)(fmt.freq * pan_loop_seconds / fmt.sample_rate);
		int pan_samples = pan_frames * fmt.sample_rate;
		int pan_i = 0;
		frame_part_size = fmt.sample_rate * fmt.res[0];
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
				for(int j = 0; j < fmt.res[0]; j++) {
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


class AudioGenBase :
	public Atom
{
	DebugSoundGenerator<uint8> gen;
	Format fmt;
	String last_error;
	int mode = 0;
	int preset_i = -1;
	
	byte val = 0;
	
	enum {
		MODE_NONE,
		MODE_TRACK_NUM,
	};
	
	void GenerateNoise(const AudioFormat& fmt);
	void GenerateStereoSine(const AudioFormat& fmt);
	
public:
	AudioGenBase();
	
	bool Initialize(const Script::WorldState& ws) final;
	void Uninitialize() final;
	//void Forward(FwdScope& fwd) final;
	bool ProcessPacket(PacketValue& v) override;
	
	void Visit(RuntimeVisitor& vis) override {}
	
	void SetPreset(int i) {preset_i = i;}
	String GetLastError() const {return last_error;}
	
	
};


NAMESPACE_PARALLEL_END

#endif
