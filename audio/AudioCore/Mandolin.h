#ifndef _AudioCore_MANDOLIN_H
#define _AudioCore_MANDOLIN_H


NAMESPACE_AUDIO_BEGIN


class Mandolin : public Instrument {
public:

	Mandolin( double lowest_freq );
	~Mandolin();
	void Clear();
	void SetDetune( double detune );
	void SetBodySize( double size );
	void SetPluckPosition( double position );
	void SetFrequency( double frequency );
	void Pluck( double amplitude );
	void Pluck( double amplitude, double position );
	void NoteOn( double frequency, double amplitude );
	void NoteOff( double amplitude );
	void ControlChange( int number, double value );
	double Tick( unsigned int channel = 0 );
	AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 );

protected:

	Twang strings_[2];
	FileWaveIn soundfile_[12];

	int mic_;
	double detuning_;
	double frequency_;
	double pluck_amplitude_;
};

inline double Mandolin::Tick( unsigned int ) {
	double temp = 0.0;

	if ( !soundfile_[mic_].IsFinished() )
		temp = soundfile_[mic_].Tick() * pluck_amplitude_;

	last_frame_[0] = strings_[0].Tick( temp );
	last_frame_[0] += strings_[1].Tick( temp );
	last_frame_[0] *= 0.2;
	return last_frame_[0];
}

inline AudioFrames& Mandolin::Tick( AudioFrames& frames, unsigned int channel ) {
	unsigned int channel_count = last_frame_.GetChannelCount();
	#if defined(flagDEBUG)

	if ( channel > frames.GetChannelCount() - channel_count ) {
		LOG("Mandolin::Tick(): channel and AudioFrames arguments are incompatible!");
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
