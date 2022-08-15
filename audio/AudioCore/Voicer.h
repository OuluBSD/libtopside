#ifndef _AudioCore_VOICER_H
#define _AudioCore_VOICER_H


NAMESPACE_AUDIO_BEGIN


class Voicer : public Audio, Moveable<Voicer> {
public:

	Voicer( double decayTime = 0.2 );
	void AddInstrument( Instrument* instrument, int group = 0 );
	void RemoveInstrument( Instrument* instrument );
	long NoteOn( double note_number, double amplitude, int group = 0 );
	void NoteOff( double note_number, double amplitude, int group = 0 );
	void NoteOff( long tag, double amplitude );
	void SetFrequency( double note_number, int group = 0 );
	void SetFrequency( long tag, double note_number );
	void PitchBend( double value, int group = 0 );
	void PitchBend( long tag, double value );
	void ControlChange( int number, double value, int group = 0 );
	void ControlChange( long tag, int number, double value );
	void Silence();

	unsigned int GetChannelsOut() const {
		return last_frame_.GetChannelCount();
	};

	const AudioFrames& GetLastFrame() const {
		return last_frame_;
	};

	double GetLastOut( unsigned int channel = 0 );
	double Tick( unsigned int channel = 0 );
	AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 );

protected:

	struct Voice : Moveable<Voice> {
		Instrument* instrument;
		long tag;
		double note_number;
		double frequency;
		int sounding;
		int group;


		Voice()
			: instrument(0), tag(0), note_number(-1.0), frequency(0.0), sounding(0), group(0) {}
	};

	Vector<Voice> voices_;
	long tags_;
	int mute_time_;
	AudioFrames last_frame_;
};

inline double Voicer::GetLastOut( unsigned int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= last_frame_.GetChannelCount() ) {
		LOG("Voicer::GetLastOut(): channel argument is invalid!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	return last_frame_[channel];
}


inline double Voicer::Tick( unsigned int channel ) {
	unsigned int j;

	for ( j = 0; j < last_frame_.GetChannelCount(); j++ ) last_frame_[j] = 0.0;

	for ( unsigned int i = 0; i < voices_.GetCount(); i++ ) {
		if ( voices_[i].sounding != 0 ) {
			voices_[i].instrument->Tick();

			for ( j = 0; j < voices_[i].instrument->GetChannelsOut(); j++ ) last_frame_[j] += voices_[i].instrument->GetLastOut( j );
		}

		if ( voices_[i].sounding < 0 )
			voices_[i].sounding++;

		if ( voices_[i].sounding == 0 )
			voices_[i].note_number = -1;
	}

	return last_frame_[channel];
}

inline AudioFrames& Voicer::Tick( AudioFrames& frames, unsigned int channel ) {
	unsigned int channel_count = last_frame_.GetChannelCount();
	#if defined(flagDEBUG)

	if ( channel > frames.GetChannelCount() - channel_count ) {
		LOG("Voicer::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	double* samples = &frames[channel];
	unsigned int j, step = frames.GetChannelCount() - channel_count;

	for ( unsigned int i = 0; i < frames.GetFrameCount(); i++, samples += step ) {
		Tick();

		for ( j = 0; j < channel_count; j++ )
			*samples++ = last_frame_[j];
	}

	return frames;
}

NAMESPACE_AUDIO_END

#endif
