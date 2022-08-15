#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN


unsigned char genMIDIMap[128] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 1, 0, 2, 0,
	2, 3, 6, 3, 6, 4, 7, 4,
	5, 8, 5, 0, 0, 0, 10, 0,
	9, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0
};

char waveNames[DRUM_NUMWAVES][16] = {
	"dope.raw",
	"bassdrum.raw",
	"snardrum.raw",
	"tomlowdr.raw",
	"tommiddr.raw",
	"tomhidrm.raw",
	"hihatcym.raw",
	"ridecymb.raw",
	"crashcym.raw",
	"cowbell1.raw",
	"tambourn.raw"
};

Drummer::Drummer() : Instrument() {
	sounding_count = 0;
	sound_order_.SetCount(DRUM_POLYPHONY, -1);
	sound_number_.SetCount(DRUM_POLYPHONY, -1);
}

Drummer::~Drummer() {
}

void Drummer::NoteOn( double instrument, double amplitude ) {
	if ( amplitude < 0.0 || amplitude > 1.0 ) {
		LOG("Drummer::noteOn: amplitude parameter is out of bounds!");
		HandleError( AudioError::WARNING );
		return;
	}

	int note_number = (int) ( ( 12 * log( instrument / 220.0 ) / log( 2.0 ) ) + 57.01 );
	int iWave;

	for ( iWave = 0; iWave < DRUM_POLYPHONY; iWave++ ) {
		if ( sound_number_[iWave] == note_number ) {
			if ( waves_[iWave].IsFinished() ) {
				sound_order_[iWave] = sounding_count;
				sounding_count++;
			}

			waves_[iWave].Reset();
			filters_[iWave].SetPole( 0.999 - (amplitude * 0.6) );
			filters_[iWave].SetGain( amplitude );
			break;
		}
	}

	if ( iWave == DRUM_POLYPHONY ) {
		if ( sounding_count < DRUM_POLYPHONY ) {
			for ( iWave = 0; iWave < DRUM_POLYPHONY; iWave++ )
				if ( sound_order_[iWave] < 0 ) break;

			sounding_count += 1;
		}
		else {
			for ( iWave = 0; iWave < DRUM_POLYPHONY; iWave++ )
				if ( sound_order_[iWave] == 0 ) break;

			for ( int j = 0; j < DRUM_POLYPHONY; j++ ) {
				if ( sound_order_[j] > sound_order_[iWave] )
					sound_order_[j] -= 1;
			}
		}

		sound_order_[iWave] = sounding_count - 1;
		sound_number_[iWave] = note_number;
		waves_[iWave].OpenFile( (Audio::GetRawWavePath() + waveNames[ genMIDIMap[ note_number ] ]).Begin(), true );

		if ( Audio::GetSampleRate() != 22050.0 )
			waves_[iWave].SetRate( 22050.0 / Audio::GetSampleRate() );

		filters_[iWave].SetPole( 0.999 - (amplitude * 0.6) );
		filters_[iWave].SetGain( amplitude );
	}
}

void Drummer::NoteOff( double amplitude ) {
	int i = 0;

	while ( i < sounding_count ) filters_[i++].SetGain( amplitude * 0.01 );
}

NAMESPACE_AUDIO_END
