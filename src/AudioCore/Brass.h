#ifndef _AudioCore_BRASS_H
#define _AudioCore_BRASS_H


NAMESPACE_AUDIO_BEGIN


class Brass: public Instrument {
public:

	Brass( float lowest_freq = 8.0 );
	~Brass(  );
	void Clear(  );
	void SetFrequency( float frequency );
	void SetLip( float frequency );
	void StartBlowing( float amplitude, float rate );
	void StopBlowing( float rate );
	void NoteOn( float frequency, float amplitude );
	void NoteOff( float amplitude );
	void ControlChange( int number, float value );
	float Tick( int channel = 0 );
	AudioFrames& Tick( AudioFrames& frames, int channel = 0 );

protected:

	DelayA   delay_line_;
	BiQuad   lip_filter_;
	PoleZero dc_block_;
	ADSR     adsr_;
	SineWave vibrato_;

	float lip_target_;
	float slide_target_;
	float vibrato_gain_;
	float max_pressure_;

};

inline float Brass::Tick( int ) {
	float breath_pressure = max_pressure_ * adsr_.Tick();
	breath_pressure += vibrato_gain_ * vibrato_.Tick();
	float mouth_pressure = 0.3f * breath_pressure;
	float bore_pressure = 0.85f * delay_line_.GetLastOut();
	float delta_pressure = mouth_pressure - bore_pressure;
	delta_pressure = lip_filter_.Tick( delta_pressure );
	delta_pressure *= delta_pressure;

	if ( delta_pressure > 1.0f ) delta_pressure = 1.0f;

	last_frame_[0] = delta_pressure * mouth_pressure + ( 1.0f - delta_pressure) * bore_pressure;
	last_frame_[0] = delay_line_.Tick( dc_block_.Tick( last_frame_[0] ) );
	return last_frame_[0];
}

inline AudioFrames& Brass::Tick( AudioFrames& frames, int channel ) {
	int channel_count = last_frame_.GetChannelCount();
	#if defined(flagDEBUG)

	if ( channel > frames.GetChannelCount() - channel_count ) {
		LOG("Brass::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	float* samples = &frames[channel];
	int j, step = frames.GetChannelCount() - channel_count;

	if ( channel_count == 1 ) {
		for ( int i = 0; i < frames.GetFrameCount(); i++, samples += step )
			* samples++ = Tick();
	}
	else {
		for ( int i = 0; i < frames.GetFrameCount(); i++, samples += step ) {
			*samples++ = Tick();

			for ( j = 1; j < channel_count; j++ )
				*samples++ = last_frame_[j];
		}
	}

	return frames;
}

NAMESPACE_AUDIO_END

#endif
