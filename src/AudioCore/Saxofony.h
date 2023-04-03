#ifndef _AudioCore_SAXOFONY_H
#define _AudioCore_SAXOFONY_H


NAMESPACE_AUDIO_BEGIN


class Saxofony : public Instrument {
public:

	Saxofony( float lowest_freq = DEFAULT_LOWEST_FREQ);
	~Saxofony();
	void Clear();
	void SetFrequency( float frequency );
	void SetBlowPosition( float aPosition );
	void StartBlowing( float amplitude, float rate );
	void StopBlowing( float rate );
	void NoteOn( float frequency, float amplitude );
	void NoteOff( float amplitude );
	void ControlChange( int number, float value );
	float Tick( int channel = 0 );
	AudioFrames& Tick( AudioFrames& frames, int channel = 0 );

protected:

	DelayL    delays_[2];
	ReedTable reed_table_;
	OneZero   filter_;
	Envelope  envelope_;
	Noise     noise_;
	SineWave vibrato_;

	float output_gain_;
	float noise_gain_;
	float vibrato_gain_;
	float position_;

};

inline float Saxofony::Tick( int ) {
	float pressure_diff;
	float breath_pressure;
	float temp;
	breath_pressure = envelope_.Tick();
	breath_pressure += breath_pressure * noise_gain_ * noise_.Tick();
	breath_pressure += breath_pressure * vibrato_gain_ * vibrato_.Tick();
	temp = -0.95f * filter_.Tick( delays_[0].GetLastOut() );
	last_frame_[0] = temp - delays_[1].GetLastOut();
	pressure_diff = breath_pressure - last_frame_[0];
	delays_[1].Tick( temp );
	delays_[0].Tick( breath_pressure - (pressure_diff * reed_table_.Tick(pressure_diff)) - temp );
	last_frame_[0] *= output_gain_;
	return last_frame_[0];
}

inline AudioFrames& Saxofony::Tick( AudioFrames& frames, int channel ) {
	int channel_count = last_frame_.GetChannelCount();
	#if defined(flagDEBUG)

	if ( channel > frames.GetChannelCount() - channel_count ) {
		LOG("Saxofony::Tick(): channel and AudioFrames arguments are incompatible!");
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
