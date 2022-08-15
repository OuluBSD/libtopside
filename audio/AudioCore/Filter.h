#ifndef _AudioCore_FILTER_H
#define _AudioCore_FILTER_H


NAMESPACE_AUDIO_BEGIN


class Filter : public Audio {
public:

	Filter() {
		gain_ = 1.0;
		in_chan_count_ = 1;
		last_frame_.SetCount( 1, 1, 0.0 );
	};

	unsigned int GetChannelsIn() const {
		return in_chan_count_;
	};

	unsigned int GetChannelsOut() const {
		return last_frame_.GetChannelCount();
	};

	virtual void Clear();


	void SetGain( double gain ) {
		gain_ = gain;
	};

	double GetGain() const {
		return gain_;
	};

	double GetPhaseDelay( double frequency );

	const AudioFrames& GetLastFrame() const {
		return last_frame_;
	};

	virtual AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 ) = 0;

protected:

	double gain_;
	unsigned int in_chan_count_;
	AudioFrames last_frame_;

	Vector<double> b_;
	Vector<double> a_;
	AudioFrames outputs_;
	AudioFrames inputs_;

};

inline void Filter::Clear() {
	unsigned int i;

	for ( i = 0; i < inputs_.GetCount(); i++ )
		inputs_[i] = 0.0;

	for ( i = 0; i < outputs_.GetCount(); i++ )
		outputs_[i] = 0.0;

	for ( i = 0; i < last_frame_.GetCount(); i++ )
		last_frame_[i] = 0.0;
}

inline double Filter::GetPhaseDelay( double frequency ) {
	if ( frequency <= 0.0 || frequency > 0.5 * Audio::GetSampleRate() ) {
		LOG("Filter::GetPhaseDelay: argument (" << frequency << ") is out of range!");
		HandleError( AudioError::WARNING );
		return 0.0;
	}

	double omegaT = 2 * PI * frequency / Audio::GetSampleRate();
	double real = 0.0, imag = 0.0;

	for ( unsigned int i = 0; i < b_.GetCount(); i++ ) {
		real += b_[i] * std::cos( i * omegaT );
		imag -= b_[i] * std::sin( i * omegaT );
	}

	real *= gain_;
	imag *= gain_;
	double phase = atan2( imag, real );
	real = 0.0, imag = 0.0;

	for ( unsigned int i = 0; i < a_.GetCount(); i++ ) {
		real += a_[i] * std::cos( i * omegaT );
		imag -= a_[i] * std::sin( i * omegaT );
	}

	phase -= std::atan2( imag, real );
	phase = std::fmod( -phase, 2 * PI );
	return phase / omegaT;
}

NAMESPACE_AUDIO_END

#endif
