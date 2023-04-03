#ifndef _AudioCore_MANDOLIN_H
#define _AudioCore_MANDOLIN_H


NAMESPACE_AUDIO_BEGIN


class Mandolin : public Instrument {
public:

	Mandolin( float lowest_freq = DEFAULT_LOWEST_FREQ);
	~Mandolin();
	void Clear();
	void SetDetune( float detune );
	void SetBodySize( float size );
	void SetPluckPosition( float position );
	void SetFrequency( float frequency );
	void Pluck( float amplitude );
	void Pluck( float amplitude, float position );
	void NoteOn( float frequency, float amplitude );
	void NoteOff( float amplitude );
	void ControlChange( int number, float value );
	float Tick( int channel = 0 );
	AudioFrames& Tick( AudioFrames& frames, int channel = 0 );

protected:

	Twang strings_[2];
	FileWaveIn soundfile_[12];

	int mic_;
	float detuning_;
	float frequency_;
	float pluck_amplitude_;
};

inline float Mandolin::Tick( int ) {
	float temp = 0.0f;

	if ( !soundfile_[mic_].IsFinished() )
		temp = soundfile_[mic_].Tick() * pluck_amplitude_;

	last_frame_[0] = strings_[0].Tick( temp );
	last_frame_[0] += strings_[1].Tick( temp );
	last_frame_[0] *= 0.2f;
	return last_frame_[0];
}

inline AudioFrames& Mandolin::Tick( AudioFrames& frames, int channel ) {
	int channel_count = last_frame_.GetChannelCount();
	#if defined(flagDEBUG)

	if ( channel > frames.GetChannelCount() - channel_count ) {
		LOG("Mandolin::Tick(): channel and AudioFrames arguments are incompatible!");
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
