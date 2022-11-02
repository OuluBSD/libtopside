#ifndef _AudioCore_CHORUS_H
#define _AudioCore_CHORUS_H


NAMESPACE_AUDIO_BEGIN


class Chorus : public Effect {
public:
	Chorus( double baseDelay = 6000 );
	void Clear() override;
	void SetModDepth( double depth );
	void SetModFrequency( double frequency );
	double GetLastOut( unsigned int channel = 0 );
	double Tick( double input, unsigned int channel = 0 ) override;
	AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 );
	AudioFrames& Tick( AudioFrames& in_frames, AudioFrames& out_frames, unsigned int in_channel = 0, unsigned int out_channel = 0 );

protected:

	DelayL delay_line_[2];
	SineWave mods_[2];
	double baseLength_;
	double mod_depth_;

};

inline double Chorus::GetLastOut( unsigned int channel ) {
	#if defined(flagDEBUG)

	if ( channel > 1 ) {
		LOG("Chorus::GetLastOut(): channel argument must be less than 2!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	return last_frame_[channel];
}

inline double Chorus::Tick( double input, unsigned int channel ) {
	#if defined(flagDEBUG)

	if ( channel > 1 ) {
		LOG("Chorus::Tick(): channel argument must be less than 2!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	delay_line_[0].SetDelay( baseLength_ * 0.707 * ( 1.0 + mod_depth_ * mods_[0].Tick() ) );
	delay_line_[1].SetDelay( baseLength_  * 0.5 *  ( 1.0 - mod_depth_ * mods_[1].Tick() ) );
	last_frame_[0] = effect_mix_ * ( delay_line_[0].Tick( input ) - input ) + input;
	last_frame_[1] = effect_mix_ * ( delay_line_[1].Tick( input ) - input ) + input;
	return last_frame_[channel];
}

inline AudioFrames& Chorus::Tick( AudioFrames& frames, unsigned int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() - 1 ) {
		LOG("Chorus::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	double* samples = &frames[channel];
	unsigned int step = frames.GetChannelCount() - 1;

	for ( unsigned int i = 0; i < frames.GetFrameCount(); i++, samples += step ) {
		delay_line_[0].SetDelay( baseLength_ * 0.707 * ( 1.0 + mod_depth_ * mods_[0].Tick() ) );
		delay_line_[1].SetDelay( baseLength_  * 0.5 *  ( 1.0 - mod_depth_ * mods_[1].Tick() ) );
		*samples = effect_mix_ * ( delay_line_[0].Tick( *samples ) - *samples ) + *samples;
		samples++;
		*samples = effect_mix_ * ( delay_line_[1].Tick( *samples ) - *samples ) + *samples;
	}

	last_frame_[0] = *(samples - step);
	last_frame_[1] = *(samples - step + 1);
	return frames;
}

inline AudioFrames& Chorus::Tick( AudioFrames& in_frames, AudioFrames& out_frames, unsigned int in_channel, unsigned int out_channel ) {
	#if defined(flagDEBUG)

	if ( in_channel >= in_frames.GetChannelCount() || out_channel >= out_frames.GetChannelCount() - 1 ) {
		LOG("Chorus::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	double* in_samples = &in_frames[in_channel];
	double* out_samples = &out_frames[out_channel];
	unsigned int in_step = in_frames.GetChannelCount(), out_step = out_frames.GetChannelCount();

	for ( unsigned int i = 0; i < in_frames.GetFrameCount(); i++, in_samples += in_step, out_samples += out_step ) {
		delay_line_[0].SetDelay( baseLength_ * 0.707 * ( 1.0 + mod_depth_ * mods_[0].Tick() ) );
		delay_line_[1].SetDelay( baseLength_  * 0.5 *  ( 1.0 - mod_depth_ * mods_[1].Tick() ) );
		*out_samples = effect_mix_ * ( delay_line_[0].Tick( *in_samples ) - *in_samples ) + *in_samples;
		*(out_samples + 1) = effect_mix_ * ( delay_line_[1].Tick( *in_samples ) - *in_samples ) + *in_samples;
	}

	last_frame_[0] = *(out_samples - out_step);
	last_frame_[1] = *(out_samples - out_step + 1);
	return in_frames;
}

NAMESPACE_AUDIO_END

#endif

