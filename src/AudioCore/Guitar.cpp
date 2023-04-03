#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

#define BASE_COUPLING_GAIN 0.01

Guitar::Guitar( int nStrings, String bodyfile ) {
	strings_.SetCount( nStrings );
	stringState_.SetCount( nStrings, 0 );
	decayCounter_.SetCount( nStrings, 0 );
	filePointer_.SetCount( nStrings, 0 );
	pluckGains_.SetCount( nStrings, 0 );
	SetBodyFile( bodyfile );
	couplingGain_ = BASE_COUPLING_GAIN;
	couplingFilter_.SetPole( 0.9f );
	pick_filter_.SetPole( 0.95f );
	last_frame_.SetCount(1, 1, 0.0f);
}

void Guitar::Clear() {
	for ( int i = 0; i < strings_.GetCount(); i++ ) {
		strings_[i].Clear();
		stringState_[i] = 0;
		filePointer_[i] = 0;
	}
}

void Guitar::SetBodyFile( String bodyfile ) {
	bool fileLoaded = false;

	if ( bodyfile != "" ) {
		try {
			FileWaveIn file( bodyfile );
			excitation_.SetCount( (int) ( 0.5f + ( file.GetSize() * Audio::GetSampleRate() / file.GetFileRate() ) ) );
			file.Tick( excitation_ );
			fileLoaded = true;
		}
		catch ( AudioError& error ) {
			LOG("Guitar::SetBodyFile: file error (" << error.GetMessage() << ") ... using noise excitation.");
			HandleError( AudioError::WARNING );
		}
	}

	if ( !fileLoaded ) {
		int M = 200;
		excitation_.SetCount( M );
		Noise noise;
		noise.Tick( excitation_ );
		int N = (int) M * 0.2f;

		for ( int n = 0; n < N; n++ ) {
			float weight = 0.5f * ( 1.0f - cos( n * PI / (N - 1) ) );
			excitation_[n] *= weight;
			excitation_[M - n - 1] *= weight;
		}
	}

	pick_filter_.Tick( excitation_ );
	float mean = 0.0f;

	for ( int i = 0; i < excitation_.GetFrameCount(); i++ )
		mean += excitation_[i];

	mean /= excitation_.GetFrameCount();

	for ( int i = 0; i < excitation_.GetFrameCount(); i++ )
		excitation_[i] -= mean;

	for ( int i = 0; i < strings_.GetCount(); i++ )
		filePointer_[i] = 0;
}


void Guitar::SetPluckPosition( float position, int string ) {
	if ( position < 0.0f || position > 1.0f ) {
		LOG("WARNING: Guitar::SetPluckPosition: position parameter out of range!");
		return;
	}

	if ( string >= (int) strings_.GetCount() ) {
		LOG("WARNING: Guitar::SetPluckPosition: string parameter is greater than number of strings!");
		return;
	}

	if ( string < 0 )
		for ( int i = 0; i < strings_.GetCount(); i++ )
			strings_[i].SetPluckPosition( position );
	else
		strings_[string].SetPluckPosition( position );
}

void Guitar::SetLoopGain( float gain, int string ) {
	if ( gain < 0.0f || gain > 1.0f ) {
		LOG("WARNING: Guitar::SetLoopGain: gain parameter out of range!");
		return;
	}

	if ( string >= (int) strings_.GetCount() ) {
		LOG("WARNING: Guitar::SetLoopGain: string parameter is greater than number of strings!");
		return;
	}

	if ( string < 0 )
		for ( int i = 0; i < strings_.GetCount(); i++ )
			strings_[i].SetLoopGain( gain );
	else
		strings_[string].SetLoopGain( gain );
}

void Guitar::SetFrequency( float frequency, int string ) {
	#if defined(flagDEBUG)

	if ( frequency <= 0.0f ) {
		LOG("Guitar::SetFrequency: frequency parameter is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	if ( string >= strings_.GetCount() ) {
		LOG("Guitar::SetFrequency: string parameter is greater than number of strings!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	strings_[string].SetFrequency( frequency );
}

void Guitar::NoteOn( float frequency, float amplitude, int string ) {
	#if defined(flagDEBUG)

	if ( string >= strings_.GetCount() ) {
		LOG("Guitar::noteOn: string parameter is greater than number of strings!");
		HandleError( AudioError::WARNING );
		return;
	}

	if ( Audio::InRange( amplitude, 0.0f, 1.0f ) == false ) {
		LOG("Guitar::noteOn: amplitude parameter is outside range 0.0f - 1.0f!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	this->SetFrequency( frequency, string );
	stringState_[string] = 2;
	filePointer_[string] = 0;
	strings_[string].SetLoopGain( 0.995f );
	pluckGains_[string] = amplitude;
}

void Guitar::NoteOff( float amplitude, int string ) {
	#if defined(flagDEBUG)

	if ( string >= strings_.GetCount() ) {
		LOG("Guitar::noteOff: string parameter is greater than number of strings!");
		HandleError( AudioError::WARNING );
		return;
	}

	if ( Audio::InRange( amplitude, 0.0f, 1.0f ) == false ) {
		LOG("Guitar::noteOff: amplitude parameter is outside range 0.0f - 1.0f!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	strings_[string].SetLoopGain( (1.0f - amplitude) * 0.9 );
	stringState_[string] = 1;
}

void Guitar::ControlChange( int number, float value, int string ) {
	#if defined(flagDEBUG)

	if ( Audio::InRange( value, 0.0f, 128.0f ) == false ) {
		LOG("Guitar::controlChange: value (" << value << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	if ( string > 0 && string >= (int) strings_.GetCount() ) {
		LOG("Guitar::controlChange: string parameter is greater than number of strings!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	float normalizedValue = value * ONE_OVER_128;

	if ( number == 2 )
		couplingGain_ = 1.5f * BASE_COUPLING_GAIN * normalizedValue;
	else if ( number == __SK_PickPosition_ )
		this->SetPluckPosition( normalizedValue, string );
	else if ( number == __SK_StringDamping_ )
		this->SetLoopGain( 0.97f + (normalizedValue * 0.03f), string );
	else if ( number == __SK_ModWheel_ )
		couplingFilter_.SetPole( 0.98f * normalizedValue );
	else if (number == __SK_AfterTouch_Cont_)
		pick_filter_.SetPole( 0.95f * normalizedValue );

	#if defined(flagDEBUG)
	else {
		LOG("Guitar::controlChange: undefined Control number (" << number << ")!");
		HandleError( AudioError::WARNING );
	}

	#endif
}

float Guitar_NoteToFrequency(byte note) {
	return 440.0f * powf(2.0f, (note - 69.0f) / 12.0f);
}

int Guitar::GetString(float frequency) {
	static bool values;
	static float freqs[6];
	if (!values) {
		freqs[0] = Guitar_NoteToFrequency(40);
		freqs[1] = Guitar_NoteToFrequency(40+5);
		freqs[2] = Guitar_NoteToFrequency(40+5+5);
		freqs[3] = Guitar_NoteToFrequency(40+5+5+5);
		freqs[4] = Guitar_NoteToFrequency(40+5+5+5+4);
		freqs[5] = Guitar_NoteToFrequency(40+5+5+5+4+5);
		values = true;
	}
	
	for(int i = min(6, strings_.GetCount())-1; i >= 0; i--) {
		if (freqs[i] < frequency)
			return i;
	}
	return 0;
}

void Guitar::SetFrequency( float frequency ) {
	SetFrequency(frequency, 0);
}

void Guitar::NoteOn( float frequency, float amplitude ) {
	return NoteOn(frequency, amplitude, Guitar_NoteToFrequency(frequency));
}

void Guitar::NoteOff( float amplitude ) {
	return NoteOff(amplitude, 0);
}

void Guitar::ControlChange( int number, float value) {
	return ControlChange(number, value, -1);
}


NAMESPACE_AUDIO_END
