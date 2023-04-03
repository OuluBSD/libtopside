#ifndef _AudioCore_MODAL_H
#define _AudioCore_MODAL_H


NAMESPACE_AUDIO_BEGIN


class Modal : public Instrument {
public:

	Modal( int modes = 4 );
	virtual ~Modal();
	void Clear();
	virtual void SetFrequency( float frequency );
	void SetRatioAndRadius( int modeIndex, float ratio, float radius );
	
	void SetMasterGain( float aGain ) {
		masterGain_ = aGain;
	};

	void SetDirectGain( float aGain ) {
		directGain_ = aGain;
	};

	void SetModeGain( int modeIndex, float gain );
	virtual void Strike( float amplitude );
	void Damp( float amplitude );
	void NoteOn( float frequency, float amplitude );
	void NoteOff( float amplitude );
	virtual void ControlChange( int number, float value ) = 0;
	float Tick( int channel = 0 );
	AudioFrames& Tick( AudioFrames& frames, int channel = 0 );

protected:

	Envelope envelope_;
	FileWaveIn* wave_;
	BiQuad** filters_;
	OnePole  onepole_;
	SineWave vibrato_;

	int mode_count_;
	Vector<float> ratios_;
	Vector<float> radii_;

	float vibrato_gain_;
	float masterGain_;
	float directGain_;
	float stickHardness_;
	float strike_position_;
	float base_frequency_;
};

inline float Modal::Tick( int ) {
	float temp = masterGain_ * onepole_.Tick( wave_->Tick() * envelope_.Tick() );
	float temp2 = 0.0f;

	for ( int i = 0; i < mode_count_; i++ )
		temp2 += filters_[i]->Tick(temp);

	temp2  -= temp2 * directGain_;
	temp2 += directGain_ * temp;

	if ( vibrato_gain_ != 0.0f ) {
		temp = 1.0f + ( vibrato_.Tick() * vibrato_gain_ );
		temp2 = temp * temp2;
	}

	last_frame_[0] = temp2;
	return last_frame_[0];
}

inline AudioFrames& Modal::Tick( AudioFrames& frames, int channel ) {
	int channel_count = last_frame_.GetChannelCount();
	#if defined(flagDEBUG)

	if ( channel > frames.GetChannelCount() - channel_count ) {
		LOG("Modal::Tick(): channel and AudioFrames arguments are incompatible!");
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
