#ifndef _AudioCore_MODAL_H
#define _AudioCore_MODAL_H


NAMESPACE_AUDIO_BEGIN


class Modal : public Instrument {
public:

	Modal( unsigned int modes = 4 );
	virtual ~Modal();
	void Clear();
	virtual void SetFrequency( double frequency );
	void SetRatioAndRadius( unsigned int modeIndex, double ratio, double radius );
	
	void SetMasterGain( double aGain ) {
		masterGain_ = aGain;
	};

	void SetDirectGain( double aGain ) {
		directGain_ = aGain;
	};

	void SetModeGain( unsigned int modeIndex, double gain );
	virtual void Strike( double amplitude );
	void Damp( double amplitude );
	void NoteOn( double frequency, double amplitude );
	void NoteOff( double amplitude );
	virtual void ControlChange( int number, double value ) = 0;
	double Tick( unsigned int channel = 0 );
	AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 );

protected:

	Envelope envelope_;
	FileWaveIn* wave_;
	BiQuad** filters_;
	OnePole  onepole_;
	SineWave vibrato_;

	unsigned int mode_count_;
	Vector<double> ratios_;
	Vector<double> radii_;

	double vibrato_gain_;
	double masterGain_;
	double directGain_;
	double stickHardness_;
	double strike_position_;
	double base_frequency_;
};

inline double Modal::Tick( unsigned int ) {
	double temp = masterGain_ * onepole_.Tick( wave_->Tick() * envelope_.Tick() );
	double temp2 = 0.0;

	for ( unsigned int i = 0; i < mode_count_; i++ )
		temp2 += filters_[i]->Tick(temp);

	temp2  -= temp2 * directGain_;
	temp2 += directGain_ * temp;

	if ( vibrato_gain_ != 0.0 ) {
		temp = 1.0 + ( vibrato_.Tick() * vibrato_gain_ );
		temp2 = temp * temp2;
	}

	last_frame_[0] = temp2;
	return last_frame_[0];
}

inline AudioFrames& Modal::Tick( AudioFrames& frames, unsigned int channel ) {
	unsigned int channel_count = last_frame_.GetChannelCount();
	#if defined(flagDEBUG)

	if ( channel > frames.GetChannelCount() - channel_count ) {
		LOG("Modal::Tick(): channel and AudioFrames arguments are incompatible!");
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
