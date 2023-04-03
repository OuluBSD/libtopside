#ifndef _AudioCore_SINEWAVE_H
#define _AudioCore_SINEWAVE_H



NAMESPACE_AUDIO_BEGIN

const int TABLE_SIZE = 2048;

class SineWave : public Generator {
public:

	SineWave();
	~SineWave();
	void Reset();
	
	void SetRate( float rate ) {
		rate_ = rate;
	};

	void SetFrequency( float frequency );
	void AddTime( float time );
	void AddPhase( float phase );
	void AddPhaseOffset( float phaseOffset );

	float GetLastOut() const {
		return last_frame_[0];
	};

	float Tick();
	AudioFrames& Tick( AudioFrames& frames, int channel = 0 );

protected:

	void SampleRateChanged( float new_rate, float old_rate );

	static AudioFrames table_;
	float time_;
	float rate_;
	float phase_offset_;
	int iIndex_;
	float alpha_;

};

inline float SineWave::Tick() {
	while ( time_ < 0.0f )
		time_ += TABLE_SIZE;

	while ( time_ >= TABLE_SIZE )
		time_ -= TABLE_SIZE;

	iIndex_ = (int) time_;
	alpha_ = time_ - iIndex_;
	float tmp = table_[ iIndex_ ];
	tmp += ( alpha_ * ( table_[ iIndex_ + 1 ] - tmp ) );
	time_ += rate_;
	last_frame_[0] = tmp;
	return last_frame_[0];
}

inline AudioFrames& SineWave::Tick( AudioFrames& frames, int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() ) {
		LOG("SineWave::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	float* samples = &frames[channel];
	float tmp = 0.0f;
	int step = frames.GetChannelCount();

	for ( int i = 0; i < frames.GetFrameCount(); i++, samples += step ) {
		while ( time_ < 0.0f )
			time_ += TABLE_SIZE;

		while ( time_ >= TABLE_SIZE )
			time_ -= TABLE_SIZE;

		iIndex_ = (int) time_;
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
