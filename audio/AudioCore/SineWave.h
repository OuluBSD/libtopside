#ifndef _AudioCore_SINEWAVE_H
#define _AudioCore_SINEWAVE_H



NAMESPACE_AUDIO_BEGIN

const unsigned long TABLE_SIZE = 2048;

class SineWave : public Generator {
public:

	SineWave();
	~SineWave();
	void Reset();
	
	void SetRate( double rate ) {
		rate_ = rate;
	};

	void SetFrequency( double frequency );
	void AddTime( double time );
	void AddPhase( double phase );
	void AddPhaseOffset( double phaseOffset );

	double GetLastOut() const {
		return last_frame_[0];
	};

	double Tick();
	AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 );

protected:

	void SampleRateChanged( double new_rate, double old_rate );

	static AudioFrames table_;
	double time_;
	double rate_;
	double phase_offset_;
	unsigned int iIndex_;
	double alpha_;

};

inline double SineWave::Tick() {
	while ( time_ < 0.0 )
		time_ += TABLE_SIZE;

	while ( time_ >= TABLE_SIZE )
		time_ -= TABLE_SIZE;

	iIndex_ = (unsigned int) time_;
	alpha_ = time_ - iIndex_;
	double tmp = table_[ iIndex_ ];
	tmp += ( alpha_ * ( table_[ iIndex_ + 1 ] - tmp ) );
	time_ += rate_;
	last_frame_[0] = tmp;
	return last_frame_[0];
}

inline AudioFrames& SineWave::Tick( AudioFrames& frames, unsigned int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() ) {
		LOG("SineWave::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	double* samples = &frames[channel];
	double tmp = 0.0;
	unsigned int step = frames.GetChannelCount();

	for ( unsigned int i = 0; i < frames.GetFrameCount(); i++, samples += step ) {
		while ( time_ < 0.0 )
			time_ += TABLE_SIZE;

		while ( time_ >= TABLE_SIZE )
			time_ -= TABLE_SIZE;

		iIndex_ = (unsigned int) time_;
		alpha_ = time_ - iIndex_;
		tmp = table_[ iIndex_ ];
		tmp += ( alpha_ * ( table_[ iIndex_ + 1 ] - tmp ) );
		*samples = tmp;
		time_ += rate_;
	}

	last_frame_[0] = tmp;
	return frames;
}

NAMESPACE_AUDIO_END

#endif
