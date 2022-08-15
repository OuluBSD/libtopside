#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

Voicer::Voicer( double decayTime ) {
	if ( decayTime < 0.0 ) {
		LOG("Voicer::Voicer: argument (" << decayTime << ") must be positive!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	tags_ = 23456;
	mute_time_ = (int) ( decayTime * Audio::GetSampleRate() );
	last_frame_.SetCount( 1, 1, 0.0 );
}

void Voicer::AddInstrument( Instrument* instrument, int group ) {
	Voicer::Voice voice;
	voice.instrument = instrument;
	voice.group = group;
	voice.note_number = -1;
	voices_.Add( voice );

	if ( instrument->GetChannelsOut() > last_frame_.GetChannelCount() ) {
		unsigned int StartChannel = last_frame_.GetChannelCount();
		last_frame_.SetCount( 1, instrument->GetChannelsOut() );

		for ( unsigned int i = StartChannel; i < last_frame_.GetCount(); i++ )
			last_frame_[i] = 0.0;
	}
}

void Voicer::RemoveInstrument( Instrument* instrument ) {
	bool found = false;

	for ( int i = 0; i != voices_.GetCount(); ++i ) {
		if ( (instrument != voices_[i].instrument ) ) continue;

		voices_.Remove( i );
		found = true;
		i--;
		break;
	}

	if ( found ) {
		unsigned int maxChannels = 1;

		for ( int i = 0; i != voices_.GetCount(); ++i ) {
			Voice& voice = voices_[i];

			if ( voice.instrument->GetChannelsOut() > maxChannels )
				maxChannels = voice.instrument->GetChannelsOut();
		}

		if ( maxChannels < last_frame_.GetChannelCount() )
			last_frame_.SetCount( 1, maxChannels );
	}
	else {
		LOG("Voicer::RemoveInstrument: instrument pointer not found in current voices!");
		HandleError( AudioError::WARNING );
	}
}

long Voicer::NoteOn(double note_number, double amplitude, int group ) {
	unsigned int i;
	double frequency = (double) 220.0 * pow( 2.0, (note_number - 57.0) / 12.0 );

	for ( i = 0; i < voices_.GetCount(); i++ ) {
		if (voices_[i].note_number < 0 && voices_[i].group == group) {
			voices_[i].tag = tags_++;
			voices_[i].group = group;
			voices_[i].note_number = note_number;
			voices_[i].frequency = frequency;
			voices_[i].instrument->NoteOn( frequency, amplitude * ONE_OVER_128 );
			voices_[i].sounding = 1;
			return voices_[i].tag;
		}
	}

	int voice = -1;

	for ( i = 0; i < voices_.GetCount(); i++ ) {
		if ( voices_[i].group == group ) {
			if ( voice == -1 ) voice = i;
			else if ( voices_[i].tag < voices_[voice].tag ) voice = (int) i;
		}
	}

	if ( voice >= 0 ) {
		voices_[voice].tag = tags_++;
		voices_[voice].group = group;
		voices_[voice].note_number = note_number;
		voices_[voice].frequency = frequency;
		voices_[voice].instrument->NoteOn( frequency, amplitude * ONE_OVER_128 );
		voices_[voice].sounding = 1;
		return voices_[voice].tag;
	}

	return -1;
}

void Voicer::NoteOff( double note_number, double amplitude, int group ) {
	for ( unsigned int i = 0; i < voices_.GetCount(); i++ ) {
		if ( voices_[i].note_number == note_number && voices_[i].group == group ) {
			voices_[i].instrument->NoteOff( amplitude * ONE_OVER_128 );
			voices_[i].sounding = -mute_time_;
		}
	}
}

void Voicer::NoteOff( long tag, double amplitude ) {
	for ( unsigned int i = 0; i < voices_.GetCount(); i++ ) {
		if ( voices_[i].tag == tag ) {
			voices_[i].instrument->NoteOff( amplitude * ONE_OVER_128 );
			voices_[i].sounding = -mute_time_;
			break;
		}
	}
}

void Voicer::SetFrequency( double note_number, int group ) {
	double frequency = (double) 220.0 * pow( 2.0, (note_number - 57.0) / 12.0 );

	for ( unsigned int i = 0; i < voices_.GetCount(); i++ ) {
		if ( voices_[i].group == group ) {
			voices_[i].note_number = note_number;
			voices_[i].frequency = frequency;
			voices_[i].instrument->SetFrequency( frequency );
		}
	}
}

void Voicer::SetFrequency( long tag, double note_number ) {
	double frequency = (double) 220.0 * pow( 2.0, (note_number - 57.0) / 12.0 );

	for ( unsigned int i = 0; i < voices_.GetCount(); i++ ) {
		if ( voices_[i].tag == tag ) {
			voices_[i].note_number = note_number;
			voices_[i].frequency = frequency;
			voices_[i].instrument->SetFrequency( frequency );
			break;
		}
	}
}

void Voicer::PitchBend( double value, int group ) {
	double pitchScaler;

	if ( value < 8192.0 )
		pitchScaler = pow( 0.5, (8192.0 - value) / 8192.0 );
	else
		pitchScaler = pow( 2.0, (value - 8192.0) / 8192.0 );

	for ( unsigned int i = 0; i < voices_.GetCount(); i++ ) {
		if ( voices_[i].group == group )
			voices_[i].instrument->SetFrequency( (double) (voices_[i].frequency * pitchScaler) );
	}
}

void Voicer::PitchBend( long tag, double value ) {
	double pitchScaler;

	if ( value < 8192.0 )
		pitchScaler = pow( 0.5, (8192.0 - value) / 8192.0 );
	else
		pitchScaler = pow( 2.0, (value - 8192.0) / 8192.0 );

	for ( unsigned int i = 0; i < voices_.GetCount(); i++ ) {
		if ( voices_[i].tag == tag ) {
			voices_[i].instrument->SetFrequency( (double) (voices_[i].frequency * pitchScaler) );
			break;
		}
	}
}

void Voicer::ControlChange( int number, double value, int group ) {
	for ( unsigned int i = 0; i < voices_.GetCount(); i++ ) {
		if ( voices_[i].group == group )
			voices_[i].instrument->ControlChange( number, value );
	}
}

void Voicer::ControlChange( long tag, int number, double value ) {
	for ( unsigned int i = 0; i < voices_.GetCount(); i++ ) {
		if ( voices_[i].tag == tag ) {
			voices_[i].instrument->ControlChange( number, value );
			break;
		}
	}
}

void Voicer::Silence() {
	for ( unsigned int i = 0; i < voices_.GetCount(); i++ ) {
		if ( voices_[i].sounding > 0 )
			voices_[i].instrument->NoteOff( 0.5 );
	}
}

NAMESPACE_AUDIO_END
