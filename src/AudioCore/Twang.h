#ifndef _AudioCore_TWANG_H
#define _AudioCore_TWANG_H


NAMESPACE_AUDIO_BEGIN

class Twang : public Audio, Moveable<Twang> {
public:

	Twang( float lowest_freq = 50.0f );

	void Clear();
	void SetLowestFrequency( float frequency );
	void SetFrequency( float frequency );
	void SetPluckPosition( float position );
	void SetLoopGain( float loopGain );
	void SetLoopFilter( Vector<float> coefficients );
	
	float GetLastOut() {
		return last_output_;
	};

	float Tick( float input );
	AudioFrames& Tick( AudioFrames& frames, int channel = 0 );
	AudioFrames& Tick( AudioFrames& in_frames, AudioFrames& out_frames, int in_channel = 0, int out_channel = 0 );

protected:

	DelayA   delay_line_;
	DelayL   comb_delay_;
	Fir      loop_filter_;

	float last_output_;
	float frequency_;
	float loop_gain_;
	float pluck_position_;
};

inline float Twang::Tick( float input ) {
	last_output_ = delay_line_.Tick( input + loop_filter_.Tick( delay_line_.GetLastOut() ) );
	last_output_ -= comb_delay_.Tick( last_output_ );
	last_output_ *= 0.5;
	return last_output_;
}

inline AudioFrames& Twang::Tick( AudioFrames& frames, int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() ) {
		LOG("Twang::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	float* samples = &frames[channel];
	int step = frames.GetChannelCount();

	for ( int i = 0; i < frames.GetFrameCount(); i++, samples += step )
		* samples = Tick( *samples );

	return frames;
}

inline AudioFrames& Twang::Tick( AudioFrames& in_frames, AudioFrames& out_frames, int in_channel, int out_channel ) {
	#if defined(flagDEBUG)

	if ( in_channel >= in_frames.GetChannelCount() || out_channel >= out_frames.GetChannelCount() ) {
		LOG("Twang::Tick(): channel and AudioFrames arguments are incompatible!");
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

#endif

