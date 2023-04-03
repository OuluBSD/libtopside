#include "IAudioFileOut.h"
#include <AudioCore/AudioCore.h>


NAMESPACE_PARALLEL_BEGIN


struct AFOCoreAudio::NativeSink {
	Audio::FileWaveOut waveout;
	int size = 0;
	
};


bool AFOCoreAudio::Sink_Create(NativeSink*& dev) {
	dev = new NativeSink;
	return true;
}

void AFOCoreAudio::Sink_Destroy(NativeSink*& dev) {
	delete dev;
}

bool AFOCoreAudio::Sink_Initialize(NativeSink& dev, AtomBase& a, const Script::WorldState& ws) {
	String filepath = ws.GetString(".filepath", "");
	
	if (filepath.IsEmpty()) {
		filepath = AppendFileName(GetHomeDirectory(), "audio-out.wav");
	}
	
	Audio::Audio::AudioFormat fmt = Audio::Audio::AUDIO_FLOAT32;
	if (!dev.waveout.OpenFile(filepath, 2, Audio::FileWrite::FILE_WAV, fmt)) {
		LOG("AFOCoreAudio::Sink_Initialize: error: could not open file " << filepath);
		return false;
	}
	
	return true;
}

bool AFOCoreAudio::Sink_PostInitialize(NativeSink& dev, AtomBase& a) {
	return true;
}

bool AFOCoreAudio::Sink_Start(NativeSink&, AtomBase&) {
	return true;
}

void AFOCoreAudio::Sink_Stop(NativeSink&, AtomBase&) {
	
}

void AFOCoreAudio::Sink_Uninitialize(NativeSink& dev, AtomBase& a) {
	LOG("AFOCoreAudio::Sink_Uninitialize: info: wrote " << dev.size << " bytes");
	dev.waveout.CloseFile();
}

bool AFOCoreAudio::Sink_Send(NativeSink&, AtomBase&, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	return true;
}

void AFOCoreAudio::Sink_Visit(NativeSink&, AtomBase&, RuntimeVisitor& vis) {
	
}

bool AFOCoreAudio::Sink_Recv(NativeSink& dev, AtomBase& a, int ch, const Packet& p) {
	Format fmt = p->GetFormat();
	
	if (fmt.IsAudio()) {
		AudioFormat& afmt = fmt;
		
		if (afmt.IsSampleFloat()) {
			const Vector<byte>& data = p->GetData();
			int count = data.GetCount() / sizeof(float);
			if (count % 2) count--;
			const float* from = (const float*)(const byte*)data.Begin();
			const float* end = from + count;
			
			
			while (from != end) {
				dev.waveout.Tick(from[0], from[1]);
				from += 2;
			}
			
			dev.size += data.GetCount();
			
			float frame_time = (float)afmt.GetFrameSeconds();
			GlobalAudioTime::Local().Add(frame_time);
		}
	}
	return true;
}

void AFOCoreAudio::Sink_Finalize(NativeSink&, AtomBase&, RealtimeSourceConfig&) {
	
}

bool AFOCoreAudio::Sink_IsReady(NativeSink& dev, AtomBase& a, PacketIO& io) {
	return io.active_sink_mask && !io.full_src_mask;
}


NAMESPACE_PARALLEL_END
