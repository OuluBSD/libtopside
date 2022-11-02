#ifndef _AudioCore_SHAKERS_H
#define _AudioCore_SHAKERS_H


NAMESPACE_AUDIO_BEGIN


class Shakers : public Instrument {
public:

	Shakers( int type = 0 );
	void NoteOn( double instrument, double amplitude );
	void NoteOff( double amplitude );
	void ControlChange( int number, double value );
	double Tick( unsigned int channel = 0 );
	AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 );

	struct BiQuad : Moveable<BiQuad> {
		double gain;
		double b[3];
		double a[3];
		double inputs[3];
		double outputs[3];


		BiQuad() {
			gain = 0.0;

			for ( int i = 0; i < 3; i++ ) {
				b[i] = 0.0;
				a[i] = 0.0;
				inputs[i] = 0.0;
				outputs[i] = 0.0;
			}
		}
	};

protected:

	void SetType( int type );
	void SetResonance( BiQuad& filter, double frequency, double radius );
	double TickResonance( BiQuad& filter, double input );
	void SetEqualization( double b0, double b1, double b2 );
	double TickEqualize( double input );
	int RandomInt( int max );
	double RandomFloat( double max = 1.0 );
	double GetNoise();
	void WaterDrop();

	int shakerType_;
	unsigned int nResonances_;
	double shakeEnergy_;
	double soundDecay_;
	double systemDecay_;
	double nObjects_;
	double sndLevel_;
	double base_gain_;
	double currentGain_;
	double baseDecay_;
	double baseObjects_;
	double decayScale_;
	BiQuad equalizer_;
	double ratchetCount_;
	double ratchetDelta_;
	double baseRatchetDelta_;
	int lastRatchetValue_;

	Vector< BiQuad > filters_;
	Vector< double > baseFrequencies_;
	Vector< double > baseRadii_;
	Vector< bool > doVaryFrequency_;
	Vector< double > tempFrequencies_;
	double varyFactor_;
};

inline void Shakers::SetResonance( BiQuad& filter, double frequency, double radius ) {
	filter.a[1] = -2.0 * radius * cos( TWO_PI * frequency / Audio::GetSampleRate());
	filter.a[2] = radius * radius;
}

inline double Shakers::TickResonance( BiQuad& filter, double input ) {
	filter.outputs[0] = input * filter.gain * currentGain_;
	filter.outputs[0] -= filter.a[1] * filter.outputs[1] + filter.a[2] * filter.outputs[2];
	filter.outputs[2] = filter.outputs[1];
	filter.outputs[1] = filter.outputs[0];
	return filter.outputs[0];
}

inline void Shakers::SetEqualization( double b0, double b1, double b2 ) {
	equalizer_.b[0] = b0;
	equalizer_.b[1] = b1;
	equalizer_.b[2] = b2;
}

inline double Shakers::TickEqualize( double input ) {
	equalizer_.inputs[0] = input;
	equalizer_.outputs[0] = equalizer_.b[0] * equalizer_.inputs[0] + equalizer_.b[1] * equalizer_.inputs[1] + equalizer_.b[2] * equalizer_.inputs[2];
	equalizer_.inputs[2] = equalizer_.inputs[1];
	equalizer_.inputs[1] = equalizer_.inputs[0];
	return equalizer_.outputs[0];
}

inline int Shakers::RandomInt( int max ) {
	return (int) ((float)max * rand() / (RAND_MAX + 1.0) );
}

inline double Shakers::RandomFloat( double max ) {
	return (double) (max * rand() / (RAND_MAX + 1.0) );
}

inline double Shakers::GetNoise() {
	return ( (double) ( 2.0 * rand() / (RAND_MAX + 1.0) ) - 1.0 );
}

const double MIN_ENERGY = 0.001;
const double WATER_FREQ_SWEEP = 1.0001;

inline void Shakers::WaterDrop() {
	if ( RandomInt( 32767 ) < nObjects_) {
		sndLevel_ = shakeEnergy_;
		unsigned int j = RandomInt( 3 );

		if ( j == 0 && filters_[0].gain == 0.0 ) {
			tempFrequencies_[0] = baseFrequencies_[1] * (0.75 + (0.25 * GetNoise()));
			filters_[0].gain = fabs( GetNoise() );
		}
		else if (j == 1 && filters_[1].gain == 0.0) {
			tempFrequencies_[1] = baseFrequencies_[1] * (1.0 + (0.25 * GetNoise()));
			filters_[1].gain = fabs( GetNoise() );
		}
		else if ( filters_[2].gain == 0.0 ) {
			tempFrequencies_[2] = baseFrequencies_[1] * (1.25 + (0.25 * GetNoise()));
			filters_[2].gain = fabs( GetNoise() );
		}
	}

	for ( unsigned int i = 0; i < 3; i++ ) {
		filters_[i].gain *= baseRadii_[i];

		if ( filters_[i].gain > 0.001 ) {
			tempFrequencies_[i] *= WATER_FREQ_SWEEP;
			filters_[i].a[1] = -2.0 * baseRadii_[i] * cos( TWO_PI * tempFrequencies_[i] / Audio::GetSampleRate() );
		}
		else
			filters_[i].gain = 0.0;
	}
}

inline double Shakers::Tick( unsigned int ) {
	unsigned int iTube = 0;
	double input = 0.0;

	if ( shakerType_ == 19 || shakerType_ == 20 ) {
		if ( ratchetCount_ <= 0 ) return last_frame_[0] = 0.0;

		shakeEnergy_ -= ( ratchetDelta_ + ( 0.002 * shakeEnergy_ ) );

		if ( shakeEnergy_ < 0.0 ) {
			shakeEnergy_ = 1.0;
			ratchetCount_--;
		}

		if ( RandomFloat( 1024 ) < nObjects_ )
			sndLevel_ += shakeEnergy_ * shakeEnergy_;

		input = sndLevel_ * GetNoise() * shakeEnergy_;
	}
	else {
		if ( shakeEnergy_ < MIN_ENERGY ) return last_frame_[0] = 0.0;

		shakeEnergy_ *= systemDecay_;

		if ( shakerType_ == 21 ) {
			WaterDrop();
			input = sndLevel_;
		}
		else {
			if ( RandomFloat( 1024.0 ) < nObjects_ ) {
				sndLevel_ += shakeEnergy_;
				input = sndLevel_;

				for ( unsigned int i = 0; i < nResonances_; i++ ) {
					if ( doVaryFrequency_[i] ) {
						double tempRand = baseFrequencies_[i] * ( 1.0 + ( varyFactor_ * GetNoise() ) );
						filters_[i].a[1] = -2.0 * baseRadii_[i] * cos( TWO_PI * tempRand / Audio::GetSampleRate() );
					}
				}

				if ( shakerType_ == 22 ) iTube = RandomInt( 7 );
			}
		}
	}

	sndLevel_ *= soundDecay_;
	last_frame_[0] = 0.0;

	if ( shakerType_ == 22 ) {
		for ( unsigned int i = 0; i < nResonances_; i++ ) {
			if ( i == iTube )
				last_frame_[0] += TickResonance( filters_[i], input );
			else
				last_frame_[0] += TickResonance( filters_[i], 0.0 );
		}
	}
	else {
		for ( unsigned int i = 0; i < nResonances_; i++ )
			last_frame_[0] += TickResonance( filters_[i], input );
	}

	last_frame_[0] = TickEqualize( last_frame_[0] );
	return last_frame_[0];
}

inline AudioFrames& Shakers::Tick( AudioFrames& frames, unsigned int channel ) {
	unsigned int channel_count = last_frame_.GetChannelCount();
	#if defined(flagDEBUG)

	if ( channel > frames.GetChannelCount() - channel_count ) {
		LOG("Shakers::Tick(): channel and AudioFrames arguments are incompatible!");
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
