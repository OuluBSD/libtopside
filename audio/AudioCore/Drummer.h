#ifndef _AudioCore_DRUMMER_H
#define _AudioCore_DRUMMER_H


NAMESPACE_AUDIO_BEGIN


const int DRUM_NUMWAVES = 11;
const int DRUM_POLYPHONY = 4;

class Drummer : public Instrument {
public:

	Drummer();
	~Drummer();
	void NoteOn( double instrument, double amplitude );
	void NoteOff( double amplitude );
	double Tick( unsigned int channel = 0 );
	AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 );

protected:

	FileWaveIn waves_[DRUM_POLYPHONY];
	OnePole  filters_[DRUM_POLYPHONY];
	Vector<int> sound_order_;
	Vector<int> sound_number_;
	int sounding_count;
};

inline double Drummer::Tick( unsigned int ) {
	last_frame_[0] = 0.0;

	if ( sounding_count == 0 ) return last_frame_[0];

	for ( int i = 0; i < DRUM_POLYPHONY; i++ ) {
		if ( sound_order_[i] >= 0 ) {
			if ( waves_[i].IsFinished() ) {
				for ( int j = 0; j < DRUM_POLYPHONY; j++ ) {
					if ( sound_order_[j] > sound_order_[i] )
						sound_order_[j] -= 1;
				}

				sound_order_[i] = -1;
				sounding_count--;
			}
			else
				last_frame_[0] += filters_[i].Tick( waves_[i].Tick() );
		}
	}

	return last_frame_[0];
}

inline AudioFrames& Drummer::Tick( AudioFrames& frames, unsigned int channel ) {
	unsigned int channel_count = last_frame_.GetChannelCount();
	#if defined(flagDEBUG)

	if ( channel > frames.GetChannelCount() - channel_count ) {
		LOG("Drummer::Tick(): channel and AudioFrames arguments are incompatible!");
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
