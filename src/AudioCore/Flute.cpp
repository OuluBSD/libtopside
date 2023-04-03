#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

Flute::Flute( float lowest_freq ) {
	if ( lowest_freq <= 0.0f ) {
		LOG("Flute::Flute: argument is less than or equal to zero!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	int delay_counts = (int) ( Audio::GetSampleRate() / lowest_freq );
	bore_delay_.SetMaximumDelay( delay_counts + 1 );
	jet_delay_.SetMaximumDelay( delay_counts + 1 );
	jet_delay_.SetDelay( 49.0f );
	vibrato_.SetFrequency( 5.925f );
	filter_.SetPole( 0.7f - ( 0.1f * 22050.0f / Audio::GetSampleRate() ) );
	dc_block_.SetBlockZero();
	adsr_.SetAllTimes( 0.005f, 0.01f, 0.8f, 0.010f );
	end_reflection = 0.5f;
	jetReflection_ = 0.5f;
	noise_gain_     = 0.15f;
	vibrato_gain_   = 0.05f;
	jetRatio_      = 0.32f;
	max_pressure_ = 0.0f;
	this->Clear();
	this->SetFrequency( 220.0f );
}

Flute::~Flute() {
}

void Flute::Clear() {
	jet_delay_.Clear();
	bore_delay_.Clear();
	filter_.Clear();
	dc_block_.Clear();
}

void Flute::SetFrequency( float frequency ) {
	#if defined(flagDEBUG)

	if ( frequency <= 0.0f ) {
		LOG("Flute::SetFrequency: argument is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	last_frequency_ = frequency * 0.66666f;
	float delay = Audio::GetSampleRate() / last_frequency_ - filter_.GetPhaseDelay( last_frequency_ ) - 1.0f;
	bore_delay_.SetDelay( delay );
	jet_delay_.SetDelay( delay * jetRatio_ );
}

void Flute::SetJetDelay( float aRatio ) {
	jetRatio_ = aRatio;
	jet_delay_.SetDelay( bore_delay_.GetDelay() * aRatio );
}

void Flute::StartBlowing( float amplitude, float rate ) {
	if ( amplitude <= 0.0f || rate <= 0.0f ) {
		LOG("Flute::StartBlowing: one or more arguments is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	adsr_.SetAttackRate( rate );
	max_pressure_ = amplitude / (float) 0.8f;
	adsr_.KeyOn();
}

void Flute::StopBlowing( float rate ) {
	if ( rate <= 0.0f ) {
		LOG("Flute::StopBlowing: argument is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	adsr_.SetReleaseRate( rate );
	adsr_.KeyOff();
}

void Flute::NoteOn( float frequency, float amplitude ) {
	this->SetFrequency( frequency );
	this->StartBlowing( 1.1f + (amplitude * 0.20f), amplitude * 0.02f );
	output_gain_ = amplitude + 0.001f;
}

void Flute::NoteOff( float amplitude ) {
	this->StopBlowing( amplitude * 0.02f );
}


void Flute::ControlChange( int number, float value ) {
	#if defined(flagDEBUG)

	if ( Audio::InRange( value, 0.0f, 128.0f ) == false ) {
		LOG("Flute::controlChange: value (" << value << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	float normalizedValue = value * ONE_OVER_128;

	if (number == __SK_JetDelay_)
		this->SetJetDelay( (float) (0.08f + (0.48f * normalizedValue)) );
	else if (number == __SK_NoiseLevel_)
		noise_gain_ = ( normalizedValue * 0.4f);
	else if (number == __SK_ModFrequency_)
		vibrato_.SetFrequency( normalizedValue * 12.0f);
	else if (number == __SK_ModWheel_)
		vibrato_gain_ = ( normalizedValue * 0.4f );
	else if (number == __SK_AfterTouch_Cont_)
		adsr_.SetTarget( normalizedValue );

	#if defined(flagDEBUG)
	else {
		LOG("Flute::controlChange: undefined Control number (" << number << ")!");
		HandleError( AudioError::WARNING );
	}

	#endif
}

NAMESPACE_AUDIO_END
