#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

BlowHole::BlowHole( double lowest_freq ) {
	if ( lowest_freq <= 0.0 ) {
		LOG("BlowHole::BlowHole: argument is less than or equal to zero!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	unsigned long delay_counts = (unsigned long) ( 0.5 * Audio::GetSampleRate() / lowest_freq );
	delays_[0].SetDelay( 5.0 * Audio::GetSampleRate() / 22050.0 );
	delays_[1].SetMaximumDelay( delay_counts + 1 );
	delays_[2].SetDelay( 4.0 * Audio::GetSampleRate() / 22050.0 );
	reed_table_.SetOffset( 0.7 );
	reed_table_.SetSlope( -0.3 );
	double rb = 0.0075;
	double rth = 0.003;
	scatter_ = -pow(rth, 2) / ( pow(rth, 2) + 2 * pow(rb, 2) );
	double te = 1.4 * rth;
	th_coeff_ = (te * 2 * Audio::GetSampleRate() - 347.23) / (te * 2 * Audio::GetSampleRate() + 347.23);
	tonehole_.SetA1( -th_coeff_ );
	tonehole_.SetB0( th_coeff_ );
	tonehole_.SetB1( -1.0 );
	double r_rh = 0.0015;
	te = 1.4 * r_rh;
	double xi = 0.0;
	double zeta = 347.23 + 2 * PI * pow(rb, 2) * xi / 1.1769;
	double psi = 2 * PI * pow(rb, 2) * te / (PI * pow(r_rh, 2));
	double rh_coeff = (zeta - 2 * Audio::GetSampleRate() * psi) / (zeta + 2 * Audio::GetSampleRate() * psi);
	rh_gain_ = -347.23 / (zeta + 2 * Audio::GetSampleRate() * psi);
	vent_.SetA1( rh_coeff );
	vent_.SetB0( 1.0 );
	vent_.SetB1( 1.0 );
	vent_.SetGain( 0.0 );
	vibrato_.SetFrequency((double) 5.735);
	output_gain_ = 1.0;
	noise_gain_ = 0.2;
	vibrato_gain_ = 0.01;
	this->SetFrequency( 220.0 );
	this->Clear();
}

BlowHole::~BlowHole() {
}

void BlowHole::Clear() {
	delays_[0].Clear();
	delays_[1].Clear();
	delays_[2].Clear();
	filter_.Tick( 0.0 );
	tonehole_.Tick( 0.0 );
	vent_.Tick( 0.0 );
}

void BlowHole::SetFrequency( double frequency ) {
	#if defined(flagDEBUG)

	if ( frequency <= 0.0 ) {
		LOG("BlowHole::SetFrequency: argument is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	double delay = ( Audio::GetSampleRate() / frequency ) * 0.5 - 3.5;
	delay -= delays_[0].GetDelay() + delays_[2].GetDelay();
	delays_[1].SetDelay( delay );
}

void BlowHole::SetVent( double newValue ) {
	double gain;

	if ( newValue <= 0.0 )
		gain = 0.0;
	else if ( newValue >= 1.0 )
		gain = rh_gain_;
	else
		gain = newValue * rh_gain_;

	vent_.SetGain( gain );
}

void BlowHole::SetTonehole( double newValue ) {
	double new_coeff;

	if ( newValue <= 0.0 )
		new_coeff = 0.9995;
	else if ( newValue >= 1.0 )
		new_coeff = th_coeff_;
	else
		new_coeff = ( newValue * (th_coeff_ - 0.9995) ) + 0.9995;

	tonehole_.SetA1( -new_coeff );
	tonehole_.SetB0( new_coeff );
}

void BlowHole::StartBlowing( double amplitude, double rate ) {
	if ( amplitude <= 0.0 || rate <= 0.0 ) {
		LOG("BlowHole::StartBlowing: one or more arguments is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	envelope_.SetRate( rate );
	envelope_.SetTarget( amplitude );
}

void BlowHole::StopBlowing( double rate ) {
	if ( rate <= 0.0 ) {
		LOG("BlowHole::StopBlowing: argument is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	envelope_.SetRate( rate );
	envelope_.SetTarget( 0.0 );
}

void BlowHole::NoteOn( double frequency, double amplitude ) {
	this->SetFrequency( frequency );
	this->StartBlowing( 0.55 + (amplitude * 0.30), amplitude * 0.005 );
	output_gain_ = amplitude + 0.001;
}

void BlowHole::NoteOff( double amplitude ) {
	this->StopBlowing( amplitude * 0.01 );
}

void BlowHole::ControlChange( int number, double value ) {
	#if defined(flagDEBUG)

	if ( Audio::inRange( value, 0.0, 128.0 ) == false ) {
		LOG("BlowHole::controlChange: value (" << value << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	double normalizedValue = value * ONE_OVER_128;

	if (number == __SK_ReedStiffness_)
		reed_table_.SetSlope( -0.44 + (0.26 * normalizedValue) );
	else if (number == __SK_NoiseLevel_)
		noise_gain_ = ( normalizedValue * 0.4);
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
