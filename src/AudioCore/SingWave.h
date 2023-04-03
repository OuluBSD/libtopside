#ifndef _AudioCore_SINGWAVE_H
#define _AudioCore_SINGWAVE_H


NAMESPACE_AUDIO_BEGIN



class SingWave : public Generator {
public:

	SingWave( String file_name, bool raw = false );
	~SingWave();

	void Reset() {
		wave_.Reset();
		last_frame_[0] = 0.0f;
	};

	void Normalize() {
		wave_.Normalize();
	};

	void Normalize( float peak ) {
		wave_.Normalize( peak );
	};

	void SetFrequency( float frequency );

	void SetVibratoRate( float rate ) {
		modulator_.SetVibratoRate( rate );
	};

	void SetVibratoGain( float gain ) {
		modulator_.SetVibratoGain( gain );
	};

	void SetRandomGain( float gain ) {
		modulator_.SetRandomGain( gain );
	};

	void SetSweepRate( float rate ) {
		sweepRate_ = rate;
	};

	void SetGainRate( float rate ) {
		envelope_.SetRate( rate );
	};

	void SetGainTarget( float target ) {
		envelope_.SetTarget( target );
	};

	void NoteOn() {
		envelope_.KeyOn();
	};

	void NoteOff() {
		envelope_.KeyOff();
	};

	float GetLastOut() const {
		return last_frame_[0];
	};

	float Tick();
	AudioFrames& Tick( AudioFrames& frames, int channel = 0 );

protected:

	FileLoop wave_;
	Modulate modulator_;
	Envelope envelope_;
	Envelope pitchEnvelope_;
	float rate_;
	float sweepRate_;

};

inline float SingWave::Tick() {
	float new_rate = pitchEnvelope_.Tick();
	new_rate += new_rate * modulator_.Tick();
	wave_.SetRate( new_rate );
	last_frame_[0] = wave_.Tick();
	last_frame_[0] *= envelope_.Tick();
	return last_frame_[0];
}

inline AudioFrames& SingWave::Tick( AudioFrames& frames, int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() ) {
		LOG("SingWave::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	float* samples = &frames[channel];
	int step = frames.GetChannelCount();

	for ( int i = 0; i < frames.GetFrameCount(); i++, samples += step )
		* samples = SingWave::Tick();

	return frames;
}

NAMESPACE_AUDIO_END

#endif
