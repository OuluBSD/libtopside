#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

BlowHole::BlowHole( float lowest_freq ) {
	if ( lowest_freq <= 0.0f ) {
		LOG("BlowHole::BlowHole: argument is less than or equal to zero!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	int delay_counts = (int) ( 0.5f * Audio::GetSampleRate() / lowest_freq );
	delays_[0].SetDelay( 5.0f * Audio::GetSampleRate() / 22050.0f );
	delays_[1].SetMaximumDelay( delay_counts + 1 );
	delays_[2].SetDelay( 4.0f * Audio::GetSampleRate() / 22050.0f );
	reed_table_.SetOffset( 0.7f );
	reed_table_.SetSlope( -0.3f );
	float rb = 0.0075f;
	float rth = 0.003f;
	scatter_ = -powf(rth, 2) / ( powf(rth, 2) + 2 * powf(rb, 2) );
	float te = 1.4f * rth;
	th_coeff_ = (te * 2 * Audio::GetSampleRate() - 347.23f) / (te * 2 * Audio::GetSampleRate() + 347.23f);
	tonehole_.SetA1( -th_coeff_ );
	tonehole_.SetB0( th_coeff_ );
	tonehole_.SetB1( -1.0f );
	float r_rh = 0.0015f;
	te = 1.4f * r_rh;
	float xi = 0.0f;
	float zeta = 347.23f + 2 * PI * powf(rb, 2) * xi / 1.1769f;
	float psi = 2 * PI * powf(rb, 2) * te / (PI * powf(r_rh, 2));
	float rh_coeff = (zeta - 2 * Audio::GetSampleRate() * psi) / (zeta + 2 * Audio::GetSampleRate() * psi);
	rh_gain_ = -347.23f / (zeta + 2 * Audio::GetSampleRate() * psi);
	vent_.SetA1( rh_coeff );
	vent_.SetB0( 1.0f );
	vent_.SetB1( 1.0f );
	vent_.SetGain( 0.0f );
	vibrato_.SetFrequency((float) 5.735f);
	output_gain_ = 1.0f;
	noise_gain_ = 0.2f;
	vibrato_gain_ = 0.01f;
	this->SetFrequency( 220.0f );
	this->Clear();
}

BlowHole::~BlowHole() {
}

void BlowHole::Clear() {
	delays_[0].Clear();
	delays_[1].Clear();
	delays_[2].Clear();
	filter_.Tick( 0.0f );
	tonehole_.Tick( 0.0f );
	vent_.Tick( 0.0f );
}

void BlowHole::SetFrequency( float frequency ) {
	#if defined(flagDEBUG)

	if ( frequency <= 0.0f ) {
		LOG("BlowHole::SetFrequency: argument is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	float delay = ( Audio::GetSampleRate() / frequency ) * 0.5f - 3.5f;
	delay -= delays_[0].GetDelay() + delays_[2].GetDelay();
	delays_[1].SetDelay( delay );
}

void BlowHole::SetVent( float newValue ) {
	float gain;

	if ( newValue <= 0.0f )
		gain = 0.0f;
	else if ( newValue >= 1.0f )
		gain = rh_gain_;
	else
		gain = newValue * rh_gain_;

	vent_.SetGain( gain );
}

void BlowHole::SetTonehole( float newValue ) {
	float new_coeff;

	if ( newValue <= 0.0f )
		new_coeff = 0.9995f;
	else if ( newValue >= 1.0f )
		new_coeff = th_coeff_;
	else
		new_coeff = ( newValue * (th_coeff_ - 0.9995f) ) + 0.9995f;

	tonehole_.SetA1( -new_coeff );
	tonehole_.SetB0( new_coeff );
}

void BlowHole::StartBlowing( float amplitude, float rate ) {
	if ( amplitude <= 0.0f || rate <= 0.0f ) {
		LOG("BlowHole::StartBlowing: one or more arguments is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	envelope_.SetRate( rate );
	envelope_.SetTarget( amplitude );
}

void BlowHole::StopBlowing( float rate ) {
	if ( rate <= 0.0f ) {
		LOG("BlowHole::StopBlowing: argument is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	envelope_.SetRate( rate );
	envelope_.SetTarget( 0.0f );
}

void BlowHole::NoteOn( float frequency, float amplitude ) {
	this->SetFrequency( frequency );
	this->StartBlowing( 0.55f + (amplitude * 0.30f), amplitude * 0.005f );
	output_gain_ = amplitude + 0.001f;
}

void BlowHole::NoteOff( float amplitude ) {
	this->StopBlowing( amplitude * 0.01f );
}

void BlowHole::ControlChange( int number, float value ) {
	#if defined(flagDEBUG)

	if ( Audio::InRange( value, 0.0f, 128.0f ) == false ) {
		LOG("BlowHole::controlChange: value (" << value << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	float normalizedValue = value * ONE_OVER_128;

	if (number == __SK_ReedStiffness_)
		reed_table_.SetSlope( -0.44f + (0.26f * normalizedValue) );
	else if (number == __SK_NoiseLevel_)
		noise_gain_ = ( normalizedValue * 0.4f);
	else if (number == __SK_ModFrequency_)
		this->SetTonehole( normalizedValue );
	else if (number == __SK_ModWheel_)
		this->SetVent( normalizedValue );
	else if (number == __SK_AfterTouch_Cont_)
		envelope_.SetValue( normalizedValue );

	#if defined(flagDEBUG)
	else {
		LOG("BlowHole::controlChange: undefined Control number (" << number << ")!");
		HandleError( AudioError::WARNING );
	}

	#endif
}

NAMESPACE_AUDIO_END
