#ifndef _AudioCore_SHAKERS_H
#define _AudioCore_SHAKERS_H


NAMESPACE_AUDIO_BEGIN


class Shakers : public Instrument {
public:

	Shakers( int type = 0 );
	void NoteOn( float instrument, float amplitude );
	void NoteOff( float amplitude );
	void ControlChange( int number, float value );
	float Tick( int channel = 0 );
	AudioFrames& Tick( AudioFrames& frames, int channel = 0 );

	struct BiQuad : Moveable<BiQuad> {
		float gain;
		float b[3];
		float a[3];
		float inputs[3];
		float outputs[3];


		BiQuad() {
			gain = 0.0f;

			for ( int i = 0; i < 3; i++ ) {
				b[i] = 0.0f;
				a[i] = 0.0f;
				inputs[i] = 0.0f;
				outputs[i] = 0.0f;
			}
		}
	};

protected:

	void SetType( int type );
	void SetResonance( BiQuad& filter, float frequency, float radius );
	float TickResonance( BiQuad& filter, float input );
	void SetEqualization( float b0, float b1, float b2 );
	float TickEqualize( float input );
	int RandomInt( int max );
	float RandomFloat( float max = 1.0f );
	float GetNoise();
	void WaterDrop();

	int shakerType_;
	int nResonances_;
	float shakeEnergy_;
	float soundDecay_;
	float systemDecay_;
	float nObjects_;
	float sndLevel_;
	float base_gain_;
	float currentGain_;
	float baseDecay_;
	float baseObjects_;
	float decayScale_;
	BiQuad equalizer_;
	float ratchetCount_;
	float ratchetDelta_;
	float baseRatchetDelta_;
	int lastRatchetValue_;

	Vector< BiQuad > filters_;
	Vector< float > baseFrequencies_;
	Vector< float > baseRadii_;
	Vector< bool > doVaryFrequency_;
	Vector< float > tempFrequencies_;
	float varyFactor_;
};

inline void Shakers::SetResonance( BiQuad& filter, float frequency, float radius ) {
	filter.a[1] = -2.0f * radius * cos( TWO_PI * frequency / Audio::GetSampleRate());
	filter.a[2] = radius * radius;
}

inline float Shakers::TickResonance( BiQuad& filter, float input ) {
	filter.outputs[0] = input * filter.gain * currentGain_;
	filter.outputs[0] -= filter.a[1] * filter.outputs[1] + filter.a[2] * filter.outputs[2];
	filter.outputs[2] = filter.outputs[1];
	filter.outputs[1] = filter.outputs[0];
	return filter.outputs[0];
}

inline void Shakers::SetEqualization( float b0, float b1, float b2 ) {
	equalizer_.b[0] = b0;
	equalizer_.b[1] = b1;
	equalizer_.b[2] = b2;
}

inline float Shakers::TickEqualize( float input ) {
	equalizer_.inputs[0] = input;
	equalizer_.outputs[0] = equalizer_.b[0] * equalizer_.inputs[0] + equalizer_.b[1] * equalizer_.inputs[1] + equalizer_.b[2] * equalizer_.inputs[2];
	equalizer_.inputs[2] = equalizer_.inputs[1];
	equalizer_.inputs[1] = equalizer_.inputs[0];
	return equalizer_.outputs[0];
}

inline int Shakers::RandomInt( int max ) {
	return (int) (max * rand() / (RAND_MAX + 1.0) );
}

inline float Shakers::RandomFloat( float max ) {
	return (float) (max * rand() / (RAND_MAX + 1.0) );
}

inline float Shakers::GetNoise() {
	return (float) ( ( 2.0 * rand() / (RAND_MAX + 1.0) ) - 1.0 );
}

const float MIN_ENERGY = 0.001f;
const float WATER_FREQ_SWEEP = 1.0001f;

inline void Shakers::WaterDrop() {
	if ( RandomInt( 32767 ) < nObjects_) {
		sndLevel_ = shakeEnergy_;
		int j = RandomInt( 3 );

		if ( j == 0 && filters_[0].gain == 0.0f ) {
			tempFrequencies_[0] = baseFrequencies_[1] * (0.75f + (0.25f * GetNoise()));
			filters_[0].gain = fabs( GetNoise() );
		}
		else if (j == 1 && filters_[1].gain == 0.0f) {
			tempFrequencies_[1] = baseFrequencies_[1] * (1.0f + (0.25f * GetNoise()));
			filters_[1].gain = fabs( GetNoise() );
		}
		else if ( filters_[2].gain == 0.0f ) {
			tempFrequencies_[2] = baseFrequencies_[1] * (1.25f + (0.25f * GetNoise()));
			filters_[2].gain = fabs( GetNoise() );
		}
	}

	for ( int i = 0; i < 3; i++ ) {
		filters_[i].gain *= baseRadii_[i];

		if ( filters_[i].gain > 0.001f ) {
			tempFrequencies_[i] *= WATER_FREQ_SWEEP;
			filters_[i].a[1] = -2.0f * baseRadii_[i] * cos( TWO_PI * tempFrequencies_[i] / Audio::GetSampleRate() );
		}
		else
			filters_[i].gain = 0.0f;
	}
}

inline float Shakers::Tick( int ) {
	int iTube = 0;
	float input = 0.0f;

	if ( shakerType_ == 19 || shakerType_ == 20 ) {
		if ( ratchetCount_ <= 0 ) return last_frame_[0] = 0.0f;

		shakeEnergy_ -= ( ratchetDelta_ + ( 0.002f * shakeEnergy_ ) );

		if ( shakeEnergy_ < 0.0f ) {
			shakeEnergy_ = 1.0f;
			ratchetCount_--;
		}

		if ( RandomFloat( 1024 ) < nObjects_ )
			sndLevel_ += shakeEnergy_ * shakeEnergy_;

		input = sndLevel_ * GetNoise() * shakeEnergy_;
	}
	else {
		if ( shakeEnergy_ < MIN_ENERGY ) return last_frame_[0] = 0.0f;

		shakeEnergy_ *= systemDecay_;

		if ( shakerType_ == 21 ) {
			WaterDrop();
			input = sndLevel_;
		}
		else {
			if ( RandomFloat( 1024.0f ) < nObjects_ ) {
				sndLevel_ += shakeEnergy_;
				input = sndLevel_;

				for ( int i = 0; i < nResonances_; i++ ) {
					if ( doVaryFrequency_[i] ) {
						float tempRand = baseFrequencies_[i] * ( 1.0f + ( varyFactor_ * GetNoise() ) );
						filters_[i].a[1] = -2.0f * baseRadii_[i] * cos( TWO_PI * tempRand / Audio::GetSampleRate() );
					}
				}

				if ( shakerType_ == 22 ) iTube = RandomInt( 7 );
			}
		}
	}

	sndLevel_ *= soundDecay_;
	last_frame_[0] = 0.0f;

	if ( shakerType_ == 22 ) {
		for ( int i = 0; i < nResonances_; i++ ) {
			if ( i == iTube )
				last_frame_[0] += TickResonance( filters_[i], input );
			else
				last_frame_[0] += TickResonance( filters_[i], 0.0f );
		}
	}
	else {
		for ( int i = 0; i < nResonances_; i++ )
			last_frame_[0] += TickResonance( filters_[i], input );
	}

	last_frame_[0] = TickEqualize( last_frame_[0] );
	return last_frame_[0];
}

inline AudioFrames& Shakers::Tick( AudioFrames& frames, int channel ) {
	int channel_count = last_frame_.GetChannelCount();
	#if defined(flagDEBUG)

	if ( channel > frames.GetChannelCount() - channel_count ) {
		LOG("Shakers::Tick(): channel and AudioFrames arguments are incompatible!");
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
