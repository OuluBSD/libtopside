#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

Mandolin::Mandolin( double lowest_freq ) {
	if ( lowest_freq <= 0.0 ) {
		LOG("Mandolin::Mandolin: argument is less than or equal to zero!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	soundfile_[0].OpenFile( (Audio::GetRawWavePath() + "mand1.raw").Begin(), true );
	soundfile_[1].OpenFile( (Audio::GetRawWavePath() + "mand2.raw").Begin(), true );
	soundfile_[2].OpenFile( (Audio::GetRawWavePath() + "mand3.raw").Begin(), true );
	soundfile_[3].OpenFile( (Audio::GetRawWavePath() + "mand4.raw").Begin(), true );
	soundfile_[4].OpenFile( (Audio::GetRawWavePath() + "mand5.raw").Begin(), true );
	soundfile_[5].OpenFile( (Audio::GetRawWavePath() + "mand6.raw").Begin(), true );
	soundfile_[6].OpenFile( (Audio::GetRawWavePath() + "mand7.raw").Begin(), true );
	soundfile_[7].OpenFile( (Audio::GetRawWavePath() + "mand8.raw").Begin(), true );
	soundfile_[8].OpenFile( (Audio::GetRawWavePath() + "mand9.raw").Begin(), true );
	soundfile_[9].OpenFile( (Audio::GetRawWavePath() + "mand10.raw").Begin(), true );
	soundfile_[10].OpenFile( (Audio::GetRawWavePath() + "mand11.raw").Begin(), true );
	soundfile_[11].OpenFile( (Audio::GetRawWavePath() + "mand12.raw").Begin(), true );
	mic_ = 0;
	detuning_ = 0.995;
	pluck_amplitude_ = 0.5;
	strings_[0].SetLowestFrequency( lowest_freq );
	strings_[1].SetLowestFrequency( lowest_freq );
	this->SetFrequency( 220.0 );
	this->SetPluckPosition( 0.4 );
}

Mandolin::~Mandolin() {
}

void Mandolin::Clear() {
	strings_[0].Clear();
	strings_[1].Clear();
}

void Mandolin::SetPluckPosition( double position ) {
	if ( position < 0.0 || position > 1.0 ) {
		LOG("WARNING: Mandolin::SetPluckPosition: position parameter out of range!");
		return;
	}

	strings_[0].SetPluckPosition( position );
	strings_[1].SetPluckPosition( position );
}

void Mandolin::SetDetune( double detune ) {
	if ( detune <= 0.0 ) {
		LOG("WARNING: Mandolin::SetDeturn: parameter is less than or equal to zero!");
		return;
	}

	detuning_ = detune;
	strings_[1].SetFrequency( frequency_ * detuning_ );
}

void Mandolin::SetBodySize( double size ) {
	double rate = size * 22050.0 / Audio::GetSampleRate();

	for ( int i = 0; i < 12; i++ )
		soundfile_[i].SetRate( rate );
}

void Mandolin::SetFrequency( double frequency ) {
	#if defined(flagDEBUG)

	if ( frequency <= 0.0 ) {
		LOG("Mandolin::SetFrequency: argument is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	frequency_ = frequency;
	strings_[0].SetFrequency( frequency_ );
	strings_[1].SetFrequency( frequency_ * detuning_ );
}

void Mandolin::Pluck( double amplitude ) {
	if ( amplitude < 0.0 || amplitude > 1.0 ) {
		LOG("Mandolin::pluck: amplitude parameter out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	soundfile_[mic_].Reset();
	pluck_amplitude_ = amplitude;
}

void Mandolin::Pluck( double amplitude, double position ) {
	this->SetPluckPosition( position );
	this->Pluck( amplitude );
}

void Mandolin::NoteOn( double frequency, double amplitude ) {
	this->SetFrequency( frequency );
	this->Pluck( amplitude );
}

void Mandolin::NoteOff( double amplitude ) {
	if ( amplitude < 0.0 || amplitude > 1.0 ) {
		LOG("Mandolin::noteOff: amplitude is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}
}

void Mandolin::ControlChange( int number, double value ) {
	#if defined(flagDEBUG)

	if ( Audio::InRange( value, 0.0, 128.0 ) == false ) {
		LOG("Mandolin::controlChange: value (" << value << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	double normalizedValue = value * ONE_OVER_128;

	if ( number == __SK_BodySize_ )
		this->SetBodySize( normalizedValue * 2.0 );
	else if ( number == __SK_PickPosition_ )
		this->SetPluckPosition( normalizedValue );
	else if ( number == __SK_StringDamping_ ) {
		strings_[0].SetLoopGain( 0.97 + (normalizedValue * 0.03) );
		strings_[1].SetLoopGain( 0.97 + (normalizedValue * 0.03) );
	}
	else if ( number == __SK_StringDetune_ )
		this->SetDetune( 1.0 - (normalizedValue * 0.1) );
	else if ( number == __SK_AfterTouch_Cont_ )
		mic_ = (int) (normalizedValue * 11.0);

	#if defined(flagDEBUG)
	else {
		LOG("Mandolin::controlChange: undefined Control number (" << number << ")!");
		HandleError( AudioError::WARNING );
	}

	#endif
}

NAMESPACE_AUDIO_END