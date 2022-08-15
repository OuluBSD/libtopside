#ifndef _AudioCore_BRASS_H
#define _AudioCore_BRASS_H


NAMESPACE_AUDIO_BEGIN


class Brass: public Instrument {
public:

	Brass( double lowest_freq = 8.0 );
	~Brass(  );
	void Clear(  );
	void SetFrequency( double frequency );
	void SetLip( double frequency );
	void StartBlowing( double amplitude, double rate );
	void StopBlowing( double rate );
	void NoteOn( double frequency, double amplitude );
	void NoteOff( double amplitude );
	void ControlChange( int number, double value );
	double Tick( unsigned int channel = 0 );
	AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 );

protected:

	DelayA   delay_line_;
	BiQuad   lip_filter_;
	PoleZero dc_block_;
	ADSR     adsr_;
	SineWave vibrato_;

	double lip_target_;
	double slide_target_;
	double vibrato_gain_;
	double max_pressure_;

};

inline double Brass::Tick( unsigned int ) {
	double breath_pressure = max_pressure_ * adsr_.Tick();
	breath_pressure += vibrato_gain_ * vibrato_.Tick();
	double mouth_pressure = 0.3 * breath_pressure;
	double bore_pressure = 0.85 * delay_line_.GetLastOut();
	double delta_pressure = mouth_pressure - bore_pressure;
	delta_pressure = lip_filter_.Tick( delta_pressure );
	delta_pressure *= delta_pressure;

	if ( delta_pressure > 1.0 ) delta_pressure = 1.0;

	last_frame_[0] = delta_pressure * mouth_pressure + ( 1.0 - delta_pressure) * bore_pressure;
	last_frame_[0] = delay_line_.Tick( dc_block_.Tick( last_frame_[0] ) );
	return last_frame_[0];
}

inline AudioFrames& Brass::Tick( AudioFrames& frames, unsigned int channel ) {
	unsigned int channel_count = last_frame_.GetChannelCount();
	#if defined(flagDEBUG)

	if ( channel > frames.GetChannelCount() - channel_count ) {
		LOG("Brass::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	double* samples = &frames[channel];
	unsigned int j, step = frames.GetChannelCount() - channel_count;

	if ( channel_count == 1 ) {
		for ( unsigned int i = 0; i < frames.GetFrameCount(); i++, samples += step )
			* samples++ = Tick();
	}
	else {
		for ( unsigned int i = 0; i < frames.GetFrameCount(); i++, samples += step ) {
			*samples++ = Tick();

			for ( j = 1; j < channel_count; j++ )
				*samples++ = last_frame_[j];
		}
	}

	return frames;
}

NAMESPACE_AUDIO_END

#endif
