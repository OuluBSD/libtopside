#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

Voicer::Voicer( float decayTime ) {
	if ( decayTime < 0.0f ) {
		LOG("Voicer::Voicer: argument (" << decayTime << ") must be positive!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	tags_ = 23456;
	mute_time_ = (int) ( decayTime * Audio::GetSampleRate() );
	last_frame_.SetCount( 1, 1, 0.0f );
}

void Voicer::AddInstrument( Instrument* instrument, int group ) {
	Voicer::Voice voice;
	voice.instrument = instrument;
	voice.group = group;
	voice.note_number = -1;
	voices_.Add( voice );

	if ( instrument->GetChannelsOut() > last_frame_.GetChannelCount() ) {
		int StartChannel = last_frame_.GetChannelCount();
		last_frame_.SetCount( 1, instrument->GetChannelsOut() );

		for ( int i = StartChannel; i < last_frame_.GetCount(); i++ )
			last_frame_[i] = 0.0f;
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
		int maxChannels = 1;

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

long Voicer::NoteOn(float note_number, float amplitude, int group ) {
	int i;
	float frequency = (float) 220.0f * powf( 2.0, (note_number - 57.0f) / 12.0 );

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

void Voicer::NoteOff( float note_number, float amplitude, int group ) {
	for ( int i = 0; i < voices_.GetCount(); i++ ) {
		if ( voices_[i].note_number == note_number && voices_[i].group == group ) {
			voices_[i].instrument->NoteOff( amplitude * ONE_OVER_128 );
			voices_[i].sounding = -mute_time_;
		}
	}
}

void Voicer::NoteOff( long tag, float amplitude ) {
	for ( int i = 0; i < voices_.GetCount(); i++ ) {
		if ( voices_[i].tag == tag ) {
			voices_[i].instrument->NoteOff( amplitude * ONE_OVER_128 );
			voices_[i].sounding = -mute_time_;
			break;
		}
	}
}

void Voicer::SetFrequency( float note_number, int group ) {
	float frequency = (float) 220.0f * powf( 2.0, (note_number - 57.0f) / 12.0 );

	for ( int i = 0; i < voices_.GetCount(); i++ ) {
		if ( voices_[i].group == group ) {
			voices_[i].note_number = note_number;
			voices_[i].frequency = frequency;
			voices_[i].instrument->SetFrequency( frequency );
		}
	}
}

void Voicer::SetFrequency( long tag, float note_number ) {
	float frequency = (float) 220.0f * powf( 2.0, (note_number - 57.0f) / 12.0 );

	for ( int i = 0; i < voices_.GetCount(); i++ ) {
		if ( voices_[i].tag == tag ) {
			voices_[i].note_number = note_number;
			voices_[i].frequency = frequency;
			voices_[i].instrument->SetFrequency( frequency );
			break;
		}
	}
}

void Voicer::PitchBend( float value, int group ) {
	float pitchScaler;

	if ( value < 8192.0 )
		pitchScaler = powf( 0.5, (8192.0 - value) / 8192.0 );
	else
		pitchScaler = powf( 2.0, (value - 8192.0f) / 8192.0 );

	for ( int i = 0; i < voices_.GetCount(); i++ ) {
		if ( voices_[i].group == group )
			voices_[i].instrument->SetFrequency( (float) (voices_[i].frequency * pitchScaler) );
	}
}

void Voicer::PitchBend( long tag, float value ) {
	float pitchScaler;

	if ( value < 8192.0 )
		pitchScaler = powf( 0.5, (8192.0 - value) / 8192.0 );
	else
		pitchScaler = powf( 2.0, (value - 8192.0f) / 8192.0 );

	for ( int i = 0; i < voices_.GetCount(); i++ ) {
		if ( voices_[i].tag == tag ) {
			voices_[i].instrument->SetFrequency( (float) (voices_[i].frequency * pitchScaler) );
			break;
		}
	}
}

void Voicer::ControlChange( int number, float value, int group ) {
	for ( int i = 0; i < voices_.GetCount(); i++ ) {
		if ( voices_[i].group == group )
			voices_[i].instrument->ControlChange( number, value );
	}
}

void Voicer::ControlChange( long tag, int number, float value ) {
	for ( int i = 0; i < voices_.GetCount(); i++ ) {
		if ( voices_[i].tag == tag ) {
			voices_[i].instrument->ControlChange( number, value );
			break;
		}
	}
}

void Voicer::Silence() {
	for ( int i = 0; i < voices_.GetCount(); i++ ) {
		if ( voices_[i].sounding > 0 )
			voices_[i].instrument->NoteOff( 0.5f );
	}
}

NAMESPACE_AUDIO_END
