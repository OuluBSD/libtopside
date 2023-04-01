#include "ParallelLib.h"

#if defined flagSCREEN

NAMESPACE_PARALLEL_BEGIN


DebugVideoGenerator::DebugVideoGenerator() {
	
}

void DebugVideoGenerator::Play(int frame_offset, PacketValue& p) {
	int total_bytes = frame.GetCount() * sizeof(T);
	frame_offset = frame_offset % total_bytes;
	int copy_size = p.GetFormat().GetFrameSize();
	p.Data().SetCount(copy_size, 0);
	int frame_remaining = total_bytes - frame_offset;
	byte* dst = p.Data().Begin();
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

void Play(int frame_offset, BufferWriterBase& buf) {
	TODO
}

void DebugVideoGenerator::GenerateNoise(const VideoFormat& fmt) {
	ASSERT(BinarySample::GetPackedSingleSize<T>() == sizeof(T));
	double pan_loop_seconds = 0.5;
	int tone_mul = 4;
	int pack_size = fmt.GetPackedCount();
	int pan_frames = (int)(fmt.freq * pan_loop_seconds / fmt.sample_rate);
	int frame_samples = fmt.res[0] * fmt.res[1] * pack_size;
	int frame_size = frame_samples * fmt.GetPackedSingleSize();
	int wavelen = 17;
	int pan_i = 0;
	//int pan_samples = fmt.res[0] / 4;
	frame_part_size = frame_size;
	int size = frame_size * pan_frames;
	frame.SetCount(size);
	T* f = frame.Begin();
	bool fast_int = !fmt.IsSampleFloat();
	auto& rng = RNG::Local();
	int dbg_wrote = 0;
	if (fast_int) {
		rng.WriteMemory(frame.Begin(), size);
	}
	else {
		// Never, but anyway...
		bool fast_dw = sizeof(T) == 1 && fmt.GetSampleSize() == 4 && !fmt.IsSampleFloat();
		bool fast_byte = sizeof(T) == 1 && !fmt.IsSampleFloat();
		
		for (int p = 0; p < pan_frames; p++) {
			union {
				dword dw[2];
				byte b[8];
				uint64 u64;
			};
			
			for(int i = 0; i < frame_samples; i++) {
				if (fast_dw) {
					int mod = i % 2;
					if (mod == 0)
						u64 = rng.Get64();
					*(dword*)f = dw[mod];
					f += pack_size;
					i += pack_size - 1;
					dbg_wrote += pack_size;
				}
				else if (fast_byte) {
					int mod = i % 8;
					if (mod == 0)
						u64 = rng.Get64();
					*f++ = b[mod];
					dbg_wrote++;
				}
				else {
					*f++ = ConvertAudioSample<double, T>(rng.Randomf());
					dbg_wrote++;
				}
			}
		}
		ASSERT(dbg_wrote == size);
		ASSERT(f == frame.End());
	}
}


void DebugVideoGenerator::GenerateSine(const VideoFormat& fmt) {
	ASSERT(BinarySample::GetPackedSingleSize<T>() == sizeof(T));
	double pan_loop_seconds = 0.25;
	int tone_mul = 4;
	int pack_size = fmt.GetPackedCount();
	int pan_frames = (int)(fmt.freq * pan_loop_seconds / fmt.sample_rate);
	int frame_samples = fmt.res[0] * fmt.res[1] * pack_size;
	int frame_size = frame_samples * fmt.GetSampleSize();
	int pan_i = 0;
	int pan_samples = fmt.res[0] / 4;
	frame_part_size = frame_size;
	int size = frame_size * pan_frames;
	frame.SetCount(size);
	T* f = frame.Begin();
	for (int p = 0; p < pan_frames; p++) {
		int pmod = p % 16 - 8;
		int wavelen = 300 + pmod;
		for(int i = 0; i < frame_samples; i++) {
			double tonerad = tone_mul * M_2PI * (double)i / (double)wavelen;
			double tonesin = FastSin(tonerad);
			//double tonevol = (tonesin + 1.0) * 0.5;
			double panrad = M_2PI * (double)pan_i / (double)pan_samples;
			double pansin = FastSin(panrad);
			double panvol = (pansin + 1.0) * 0.5;
			for(int j = 0; j < pack_size; j++) {
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











VideoGenBase::VideoGenBase() {
	fmt.SetVideo(DevCls::CENTER, LightSampleFD::U8_LE_ABC, TS::default_width, TS::default_height, 60, 1);
	
}

bool VideoGenBase::Initialize(const Script::WorldState& ws) {
	String mode = ws.Get(".mode");
	if (mode == "sine")
		gen.GenerateSine(fmt);
	else
		gen.GenerateNoise(fmt);
	
	const int src_ch_i = 0;
	
	Value& src_val = GetSource()->GetSourceValue(src_ch_i);
	src_val.SetFormat(fmt);
	return true;
}

void VideoGenBase::Uninitialize() {
	
}

bool VideoGenBase::Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	int frame = fmt.GetFrameSize();
	dword off = out.GetOffset().value;
	int64 offset = (int64)off * (int64)frame;
	int64 max_offset = gen.GetMaxOffset();
	offset = offset % max_offset;
	ASSERT(offset < (int64)std::numeric_limits<int>::max());
	double time = off * fmt.GetFrameSeconds();
	out.Set(fmt, time);
	out.ClearDataType(); // remove default InternalPacketData type
	out.Data().SetCount(frame, 0);
	gen.Play((int)offset, out);
	
	RTLOG("VideoGenBase::Send: " << out.ToStringWithHash());
	return true;
}


NAMESPACE_PARALLEL_END

#endif
