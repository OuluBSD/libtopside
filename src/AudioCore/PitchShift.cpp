#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

PitchShift::PitchShift() {
	delay_length_ = max_delay - 24;
	half_length_ = delay_length_ / 2;
	delay_[0] = 12;
	delay_[1] = max_delay / 2;
	delay_line_[0].SetMaximumDelay( max_delay );
	delay_line_[0].SetDelay( delay_[0] );
	delay_line_[1].SetMaximumDelay( max_delay );
	delay_line_[1].SetDelay( delay_[1] );
	effect_mix_ = 0.5;
	rate_ = 1.0f;
}

void PitchShift::Clear() {
	delay_line_[0].Clear();
	delay_line_[1].Clear();
	last_frame_[0] = 0.0f;
}

void PitchShift::SetShift( float shift ) {
	if ( shift < 1.0f )
		rate_ = 1.0f - shift;
	else if ( shift > 1.0f )
		rate_ = 1.0f - shift;
	else {
		rate_ = 0.0f;
		delay_[0] = half_length_ + 12;
	}
}

AudioFrames& PitchShift::Tick( AudioFrames& frames, int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() ) {
		LOG("PitchShift::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	float* samples = &frames[channel];
	int step = frames.GetChannelCount();

	for ( int i = 0; i < frames.GetFrameCount(); i++, samples += step )
		* samples = Tick( *samples );

	return frames;
}

AudioFrames& PitchShift::Tick( AudioFrames& in_frames, AudioFrames& out_frames, int in_channel, int out_channel ) {
	#if defined(flagDEBUG)

	if ( in_channel >= in_frames.GetChannelCount() || out_channel >= out_frames.GetChannelCount() ) {
		LOG("PitchShift::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	float* in_samples = &in_frames[in_channel];
	float* out_samples = &out_frames[out_channel];
	int in_step = in_frames.GetChannelCount(), out_step = out_frames.GetChannelCount();

	for ( int i = 0; i < in_frames.GetFrameCount(); i++, in_samples += in_step, out_samples += out_step )
		* out_samples = Tick( *in_samples );

	return in_frames;
}

NAMESPACE_AUDIO_END
