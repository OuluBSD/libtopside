#ifndef _AudioCore_TWANG_H
#define _AudioCore_TWANG_H


NAMESPACE_AUDIO_BEGIN

class Twang : public Audio, Moveable<Twang> {
public:

	Twang( double lowest_freq = 50.0 );

	void Clear();
	void SetLowestFrequency( double frequency );
	void SetFrequency( double frequency );
	void SetPluckPosition( double position );
	void SetLoopGain( double loopGain );
	void SetLoopFilter( Vector<double> coefficients );
	
	double GetLastOut() {
		return last_output_;
	};

	double Tick( double input );
	AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 );
	AudioFrames& Tick( AudioFrames& in_frames, AudioFrames& out_frames, unsigned int in_channel = 0, unsigned int out_channel = 0 );

protected:

	DelayA   delay_line_;
	DelayL   comb_delay_;
	Fir      loop_filter_;

	double last_output_;
	double frequency_;
	double loop_gain_;
	double pluck_position_;
};

inline double Twang::Tick( double input ) {
	last_output_ = delay_line_.Tick( input + loop_filter_.Tick( delay_line_.GetLastOut() ) );
	last_output_ -= comb_delay_.Tick( last_output_ );
	last_output_ *= 0.5;
	return last_output_;
}

inline AudioFrames& Twang::Tick( AudioFrames& frames, unsigned int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() ) {
		LOG("Twang::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	double* samples = &frames[channel];
	unsigned int step = frames.GetChannelCount();

	for ( unsigned int i = 0; i < frames.GetFrameCount(); i++, samples += step )
		* samples = Tick( *samples );

	return frames;
}

inline AudioFrames& Twang::Tick( AudioFrames& in_frames, AudioFrames& out_frames, unsigned int in_channel, unsigned int out_channel ) {
	#if defined(flagDEBUG)

	if ( in_channel >= in_frames.GetChannelCount() || out_channel >= out_frames.GetChannelCount() ) {
		LOG("Twang::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	double* in_samples = &in_frames[in_channel];
	double* out_samples = &out_frames[out_channel];
	unsigned int in_step = in_frames.GetChannelCount(), out_step = out_frames.GetChannelCount();

	for ( unsigned int i = 0; i < in_frames.GetFrameCount(); i++, in_samples += in_step, out_samples += out_step )
		* out_samples = Tick( *in_samples );

	return in_frames;
}

NAMESPACE_AUDIO_END

#endif

