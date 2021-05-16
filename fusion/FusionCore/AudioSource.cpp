#include "FusionCore.h"

NAMESPACE_TOPSIDE_BEGIN


void FusionAudioSource::Initialize() {
	FusionComponent::Initialize();
	
	AddToSystem<AudioSystem>(AsRef<AudioSource>());
}

void FusionAudioSource::Uninitialize() {
	RemoveFromSystem<AudioSystem>(AsRef<AudioSource>());
	
	FusionComponent::Uninitialize();
}

void FusionAudioSource::Reset() {
	auto* stream = Stream();
	if (stream) {
		//stream->aframe_time.Reset();
		stream->audio_last_sync_sec = 0;
	}
}

void FusionAudioSource::PreProcess() {
	// pass
}

void FusionAudioSource::PostProcess() {
	/*auto* stream = Stream();
	if (stream) {
		stream->aframe_time.Reset();
	}*/
}

void FusionAudioSource::UpdateTexBuffers() {
	auto* stream = Stream();
	if (stream) {
		ClearTex();
#ifdef flagOPENGL
		int sr = max(stream->aud_fmt.sample_rate, 1);
		int ch = max(stream->aud_fmt.channels, 1);
		Ogl_CreateTex(
			Size(sr, 1), ch,
			0, 0,
			FusionComponentInput::FILTER_LINEAR,
			FusionComponentInput::WRAP_CLAMP);
		audio_buf.SetCount(sr * ch, 0);
#endif
	}
}

bool FusionAudioSource::LoadResources() {
	return true;
}

/*void FusionAudioSource::EmitAudioSource(double dt) {
	DefaultEmitAudioSource(dt, 1);
}*/

/*void FusionAudioSource::Play(const RealtimeSourceConfig& config, Audio& aud) {
	const char* fn_name = "Play";
	auto* stream = Stream();
	if (!stream || !ctx || !IsOpen())
		return;
	
	stream->sys_aud = &aud;
	stream->is_audio_sync = config.sync;
	stream->asink_frame = config.sink_frame;
	stream->aframes_after_sync = config.frames_after_sync;
	
	AudioFormat cur_fmt = aud.GetAudioFormat();
	if (cur_fmt != stream->aud_fmt) {
		stream->aud_fmt = cur_fmt;
		ctx->UpdateSoundBuffers();
	}
	ctx->Play();
	
}*/

void FusionAudioSource::UseRenderedFramebuffer() {
	const char* fn_name = "UseRenderedFramebuffer";
	auto* stream = Stream();
	ASSERT(stream);
	if (!stream) return;
	if (!stream->sys_aud) return;
	Audio& aud = *stream->sys_aud;
	const AudioFormat& fmt = stream->aud_fmt;
	
#ifdef flagOPENGL
	ASSERT(color_buf[buf_i] > 0);
	glReadBuffer(GL_COLOR_ATTACHMENT0_EXT);
	glReadPixels(0, 0, fmt.sample_rate, 1, GetOglChCode(fmt.channels), GL_FLOAT, audio_buf.Begin());
#endif
	
	if (fmt.var_size != 4 || !fmt.is_var_float) {
		OnError(fn_name, "TODO type conversion: f32 -> ...");
	}
	else {
		TODO // Exchange
		//snd.Put((void*)audio_buf.Begin(), audio_buf.GetCount() * sizeof(float), stream->is_audio_sync);
	}
	
	stream->sys_aud = 0;
}

AudioStream& FusionAudioSource::GetAudioSource() {
	TODO
}

void FusionAudioSource::BeginAudioSource() {
	TODO
}

void FusionAudioSource::EndAudioSource() {
	TODO
}



NAMESPACE_TOPSIDE_END
