#ifndef _AudioCore_ECHO_H
#define _AudioCore_ECHO_H


NAMESPACE_AUDIO_BEGIN


class Echo : public Effect {
public:
	Echo( int maximum_delay = (int) Audio::GetSampleRate() );
	void Clear() override;
	void SetMaximumDelay( int delay );
	void SetDelay( int delay );

	float GetLastOut() const {
		return last_frame_[0];
	};

	float Tick( float input, int channel = 0 ) override;
	AudioFrames& Tick( AudioFrames& frames, int channel = 0 );
	AudioFrames& Tick( AudioFrames& in_frames, AudioFrames& out_frames, int in_channel = 0, int out_channel = 0 );

protected:

	Delay delay_line_;
	int size_;

};

inline float Echo::Tick( float input, int channel ) {
	last_frame_[0] = effect_mix_ * ( delay_line_.Tick( input ) - input ) + input;
	return last_frame_[0];
}

inline AudioFrames& Echo::Tick( AudioFrames& frames, int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() ) {
		LOG("Echo::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	float* samples = &frames[channel];
	int step = frames.GetChannelCount();

	for ( int i = 0; i < frames.GetFrameCount(); i++, samples += step )
		* samples = effect_mix_ * ( delay_line_.Tick( *samples ) - *samples ) + *samples;

	last_frame_[0] = *(samples - step);
	return frames;
}

inline AudioFrames& Echo::Tick( AudioFrames& in_frames, AudioFrames& out_frames, int in_channel, int out_channel ) {
	#if defined(flagDEBUG)

	if ( in_channel >= in_frames.GetChannelCount() || out_channel >= out_frames.GetChannelCount() ) {
		LOG("Echo::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	float* in_samples = &in_frames[in_channel];
	float* out_samples = &out_frames[out_channel];
	int in_step = in_frames.GetChannelCount(), out_step = out_frames.GetChannelCount();

	for ( int i = 0; i < in_frames.GetFrameCount(); i++, in_samples += in_step, out_samples += out_step )
		* out_samples = effect_mix_ * ( delay_line_.Tick( *in_samples ) - *in_samples ) + *in_samples;

	last_frame_[0] = *(out_samples - out_step);
	return in_frames;
}

NAMESPACE_AUDIO_END

#endif

