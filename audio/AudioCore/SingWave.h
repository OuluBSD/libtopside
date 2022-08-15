#ifndef _AudioCore_SINGWAVE_H
#define _AudioCore_SINGWAVE_H


NAMESPACE_AUDIO_BEGIN



class SingWave : public Generator {
public:

	SingWave( String file_name, bool raw = false );
	~SingWave();

	void Reset() {
		wave_.Reset();
		last_frame_[0] = 0.0;
	};

	void Normalize() {
		wave_.Normalize();
	};

	void Normalize( double peak ) {
		wave_.Normalize( peak );
	};

	void SetFrequency( double frequency );

	void SetVibratoRate( double rate ) {
		modulator_.SetVibratoRate( rate );
	};

	void SetVibratoGain( double gain ) {
		modulator_.SetVibratoGain( gain );
	};

	void SetRandomGain( double gain ) {
		modulator_.SetRandomGain( gain );
	};

	void SetSweepRate( double rate ) {
		sweepRate_ = rate;
	};

	void SetGainRate( double rate ) {
		envelope_.SetRate( rate );
	};

	void SetGainTarget( double target ) {
		envelope_.SetTarget( target );
	};

	void NoteOn() {
		envelope_.KeyOn();
	};

	void NoteOff() {
		envelope_.KeyOff();
	};

	double GetLastOut() const {
		return last_frame_[0];
	};

	double Tick();
	AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 );

protected:

	FileLoop wave_;
	Modulate modulator_;
	Envelope envelope_;
	Envelope pitchEnvelope_;
	double rate_;
	double sweepRate_;

};

inline double SingWave::Tick() {
	double new_rate = pitchEnvelope_.Tick();
	new_rate += new_rate * modulator_.Tick();
	wave_.SetRate( new_rate );
	last_frame_[0] = wave_.Tick();
	last_frame_[0] *= envelope_.Tick();
	return last_frame_[0];
}

inline AudioFrames& SingWave::Tick( AudioFrames& frames, unsigned int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() ) {
		LOG("SingWave::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	double* samples = &frames[channel];
	unsigned int step = frames.GetChannelCount();

	for ( unsigned int i = 0; i < frames.GetFrameCount(); i++, samples += step )
		* samples = SingWave::Tick();

	return frames;
}

NAMESPACE_AUDIO_END

#endif
