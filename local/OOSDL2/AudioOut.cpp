#include "OOSDL2.h"
#include <SerialCore/SerialCore.h>

NAMESPACE_SDL2_BEGIN


AudioOutput::AudioOutput(Context* ctx, AtomBase* ab) : Component(ctx, ab) {
	SDL_zero(audio_fmt);
	SetDesiredAudioFmt(
		44100,
		4, true, // 32bit float
		2,
		1024
	);
	
	
	fmt.SetAudio(DevCls::CENTER, SoundSample::FLT_LE, 2, 44100, 1024);
	
}

int AudioOutput::GetSampleSize() {
	int sample_size = 0;
	switch(audio_fmt.format) {
		case AUDIO_S8:  sample_size = 1; break;
		case AUDIO_S16: sample_size = 2; break;
		case AUDIO_S32: sample_size = 4; break;
		case AUDIO_F32: sample_size = 4; break;
		default: break;
	}
	return sample_size;
}

bool AudioOutput::IsSampleFloating() const {
	return audio_fmt.format == AUDIO_F32;
}

bool AudioOutput::IsSampleSigned() const {
	return	audio_fmt.format == AUDIO_F32 ||
			audio_fmt.format == AUDIO_S8 ||
			audio_fmt.format == AUDIO_S16 ||
			audio_fmt.format == AUDIO_S32
			;
}

void AudioOutput::SinkCallback(Uint8* output, int size) {
	RTLOG("AudioOutput::SinkCallback");
	
	/*PacketBuffer& sink_buf = GetSinkBuffer();
	
	if (sink_buf.IsEmpty() || !output) {
		if (0) {
			RTLOG("AudioOutput::SinkCallback: empty buffer");
		}
		return;
	}*/
	
	#ifdef flagDEBUG
	ab->dbg_async_race = true;
	#endif
	
	
	if (!ab->ForwardAsyncMem(output, size)) {
		RTLOG("AudioOutput::SinkCallback: reading memory failed");
		memset(output, 0, size);
	}
	
	
	#if 0
	int dbg_i = 0;
	for (float* b = (float*)output, *end = (float*)output+size/sizeof(float); b != end; b++) {
		float f = *b;
		int got = ((f + 1.0001) * 0.5) * 255;
		if (got != val) {DUMP(f); DUMP(dbg_i); DUMP((int)got); DUMP((int)val);}
		ASSERT(got == val++);
		dbg_i++;
	}
	LOG("Check successful");
	memset(output,0,size);
	#elif 0
	int dbg_i = 0;
	for (float* b = (float*)output, *end = (float*)output+size/sizeof(float); b != end; b++) {
		float f = *b;
		LOG(dbg_i << ": " << f);
		dbg_i++;
	}
	LOG("");
	#elif 0
	int dbg_i = 0;
	for (float* b = (float*)output, *end = (float*)output+size/sizeof(float); b != end; b++) {
		float f = *b;
		if (f == 0.0) {
			LOG(dbg_i << ": " << f);
		}
		dbg_i++;
	}
	#elif 0
	for (float* b = (float*)output, *end = (float*)output+size/sizeof(float); b != end; b++) {
		float f = sin(flt);
		flt += M_2PI / 1000.0;
		if (flt > M_2PI)
			flt -= M_2PI;
	}
	
	
	#endif
	
	#if 0
	if (consumer.IsEmptySource())
		consumer.SetSource(sink_buf);

	ASSERT(size == fmt.GetFrameSize());
	
	if (sink_buf.GetCount() > 0 || consumer.HasLeftover()) {
		consumer.SetDestination(fmt, output, size);
		consumer.ConsumeAll(false);
		consumer.ClearDestination();
		
		if (1) {
			for (const Packet& p : consumer.consumed_packets) {
				RTLOG("AudioOutput::SinkCallback: consumed: " << p->ToStringWithHash());
			}
		}
		
		if (consumer.GetLastMemoryBytes() != size) {
			RTLOG("OOSDL2::AudioOutput::SinkCallback: error: consumed " << consumer.GetLastMemoryBytes() << " (expected " << size << ")");
		}
		
		int consumed_count = consumer.GetCount();
		if (consumed_count) {
			RTLOG("OOSDL2::AudioOutput::SinkCallback: device consumed count=" << consumed_count);
		}
		
		ab->PacketsConsumed(consumer.consumed_packets);
		ab->PostContinueForward();
	}
	else {
		RTLOG("AudioOutput::SinkCallback: error: got empty data");
		
		memset(output, 0, size);
	}
	#endif
	
	
	#ifdef flagDEBUG
	ab->dbg_async_race = false;
	#endif
	
	frames++;
}

bool AudioOutput::Open0() {
	RTLOG("AudioOutput::Open0");
	auto& fmt = this->fmt.aud;
	SDL_zero(audio_fmt);
	audio_dev = SDL_OpenAudioDevice(NULL, 0, &audio_desired, &audio_fmt, SDL_AUDIO_ALLOW_FORMAT_CHANGE);
	if (audio_dev == 0) {
	    RTLOG("OOSDL2::AudioOutput::Open0: error: failed to open audio: " << SDL_GetError());
	    return false;
	}
	else {
	    if (audio_fmt.format != audio_desired.format) {
			// we let this one thing change.
	        RTLOG("OOSDL2::AudioOutput::Open0: warning: couldn't get desired audio format.");
	    }
	    
	    #if CPU_LITTLE_ENDIAN
	    if (IsSampleFloating()) {
	        fmt.type = GetSampleSize() == 4 ? SoundSample::FLT_LE : SoundSample::DBL_LE;
	    }
	    else {
	        int sz = GetSampleSize();
	        if (IsSampleSigned()) {
	            switch (sz) {
	                case 1: fmt.type = SoundSample::S8_LE; break;
	                case 2: fmt.type = SoundSample::S16_LE; break;
	                case 3: fmt.type = SoundSample::S24_LE; break;
	                case 4: fmt.type = SoundSample::S32_LE; break;
	                case 8: fmt.type = SoundSample::S64_LE; break;
	                default: LOG("OOSDL2::AudioOutput::Open0: error: unexpected format"); return false;
	            }
	        }
	        else  {
	            switch (sz) {
	                case 1: fmt.type = SoundSample::U8_LE; break;
	                case 2: fmt.type = SoundSample::U16_LE; break;
	                case 3: fmt.type = SoundSample::U24_LE; break;
	                case 4: fmt.type = SoundSample::U32_LE; break;
	                case 8: fmt.type = SoundSample::U64_LE; break;
	                default: LOG("OOSDL2::AudioOutput::Open0: error: unexpected format"); return false;
	            }
	        }
	    }
	    #else
	    #error TODO
	    #endif
	    fmt.freq = audio_fmt.freq;
	    fmt.sample_rate = audio_fmt.samples;
	    fmt.res[0] = audio_fmt.channels;
		
	    //buf.SetFormat(fmt, 4*MIN_AUDIO_BUFFER_SAMPLES);
		
	    SDL_PauseAudioDevice(audio_dev, 0); // start audio playing.
	    
	    RTLOG("OOSDL2::AudioOutput::Open0: opened format: " << fmt.ToString());
	    
	    UpdateSinkFormat();
	    
	    return true;
	}
}

void AudioOutput::UpdateSinkFormat() {
	InterfaceSinkRef sink_iface = ab->GetSink();
	int sink_count = sink_iface->GetSinkCount();
	for(int i = 0; i < sink_count; i++) {
		Value& val = sink_iface->GetValue(i);
		Format val_fmt = val.GetFormat();
		if (val_fmt.vd.val == ValCls::AUDIO && val_fmt != fmt) {
			RTLOG("AudioOutput::UpdateSinkFormat: updating sink #" << i << " format to " << fmt.ToString());
			val.SetFormat(fmt);
		}
	}
}

void AudioOutput::Close0() {
	PacketBuffer& sink_buf = GetSinkBuffer();
	
	if (audio_dev) {
		SDL_PauseAudioDevice(audio_dev, 1);
		SDL_CloseAudioDevice(audio_dev);
		sink_buf.Clear();
		audio_dev = 0;
	}
}



void StaticAudioOutputSinkCallback(void* userdata, Uint8* stream, int len) {
	if (userdata)
		((AudioOutput*)userdata)->SinkCallback(stream, len);
	else
		memset(stream, 0, len);
}

void AudioOutput::SetDesiredAudioFmt(int sample_freq, int sample_bytes, bool is_var_floating, int channels, int sample_rate) {
	SDL_zero(audio_desired);
	audio_desired.freq = sample_freq;
	audio_desired.format = AUDIO_S16;
	if (!is_var_floating) {
		switch (sample_bytes) {
			case 1:	audio_desired.format = AUDIO_S8; break;
			case 2:	audio_desired.format = AUDIO_S16; break;
			case 4:
			case 8:
			default:
					audio_desired.format = AUDIO_S32; break;
		}
	}
	else {
		audio_desired.format = AUDIO_F32;
	}
	audio_desired.channels = channels;
	audio_desired.samples = sample_rate;
	audio_desired.callback = StaticAudioOutputSinkCallback;
	audio_desired.userdata = this;
}



NAMESPACE_SDL2_END
