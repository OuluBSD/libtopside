#include "OOSDL2.h"

NAMESPACE_SDL2_BEGIN


AudioOutput::AudioOutput(Context* ctx) : Component(ctx) {
	SDL_zero(audio_fmt);
	SetDesiredAudioFmt(
		44100,
		4, true, // 32bit float
		2,
		1024
	);
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
	
	TODO
	
	#if 0
	
	if (buf.IsEmpty() || !output) {
		if (0) {
			RTLOG("AudioOutput::SinkCallback: empty buffer");
		}
		return;
	}
	
	if (consumer.IsEmptySource())
		consumer.SetSource(buf);

	AudioFormat fmt = buf.GetFormat();
	ASSERT(size == fmt.GetFrameSize());
	
	if (buf.GetQueueSize() > 0 || consumer.HasLeftover()) {
		
		off32 begin_offset = buf.GetOffset();
		if (0) {
			RTLOG("AudioOutput::SinkCallback: trying to consume " << begin_offset.ToString());
			RTLOG("AudioOutput::SinkCallback: dumping");
			buf.Dump();
		}
		
		//consumer.TestSetOffset(begin_offset);
		
		consumer.SetDestination(fmt, output, size);
		consumer.ConsumeAll(false);
		consumer.ClearDestination();
		
		off32 end_offset = consumer.GetOffset();
		off32 diff = off32::GetDifference(begin_offset, end_offset);
		if (diff) {
			RTLOG("AudioOutput::SinkCallback: device consumed count=" << diff.ToString());
			buf.RemoveFirst(diff.value);
		}
		else if (consumer.HasLeftover()) {
			RTLOG("AudioOutput::SinkCallback: device consumed packet partially");
		}
		else if (!consumer.HasLeftover()) {
			RTLOG("error: AudioOutput::SinkCallback: device error");
		}
	}
	else {
		#if DEBUG_RT_PIPE
		RTLOG("error: AudioOutput::SinkCallback: got empty data");
		#endif
		
		memset(output, 0, size);
	}
	
	frames++;
	
	#endif
	
}

bool AudioOutput::Open0() {
	TODO
	
	#if 0
	
	SDL_zero(audio_fmt);
	audio_dev = SDL_OpenAudioDevice(NULL, 0, &audio_desired, &audio_fmt, SDL_AUDIO_ALLOW_FORMAT_CHANGE);
	if (audio_dev == 0) {
	    LOG("OOSDL2::AudioOutput::Open0: error: failed to open audio: " << SDL_GetError());
	    return false;
	}
	else {
	    if (audio_fmt.format != audio_desired.format) {
			// we let this one thing change.
	        LOG("OOSDL2::AudioOutput::Open0: warning: couldn't get desired audio format.");
	    }
	    
	    AudioFormat fmt;
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
	    fmt.channels = audio_fmt.channels;
		
	    buf.SetFormat(fmt, 4*MIN_AUDIO_BUFFER_SAMPLES);
		
	    SDL_PauseAudioDevice(audio_dev, 0); // start audio playing.
	    
	    LOG("OOSDL2::AudioOutput::Open0: opened format: " << fmt.ToString());
	    
	    return true;
	}
	#endif
}

void AudioOutput::Close0() {
	if (audio_dev) {
		SDL_PauseAudioDevice(audio_dev, 1);
		SDL_CloseAudioDevice(audio_dev);
		buf.Clear();
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
