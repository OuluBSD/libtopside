#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

Chorus::Chorus( double baseDelay ) {
	last_frame_.SetCount( 1, 2, 0.0 );
	delay_line_[0].SetMaximumDelay( (unsigned long) (baseDelay * 1.414) + 2);
	delay_line_[0].SetDelay( baseDelay );
	delay_line_[1].SetMaximumDelay( (unsigned long) (baseDelay * 1.414) + 2);
	delay_line_[1].SetDelay( baseDelay );
	baseLength_ = baseDelay;
	mods_[0].SetFrequency( 0.2 );
	mods_[1].SetFrequency( 0.222222 );
	mod_depth_ = 0.05;
	effect_mix_ = 0.5;
	this->Clear();
}

void Chorus::Clear() {
	delay_line_[0].Clear();
	delay_line_[1].Clear();
	last_frame_[0] = 0.0;
	last_frame_[1] = 0.0;
}

void Chorus::SetModDepth( double depth ) {
	if ( depth < 0.0 || depth > 1.0 ) {
		LOG("Chorus::SetModDepth(): depth argument must be between 0.0 - 1.0!");
		HandleError( AudioError::WARNING );
		return;
	}

	mod_depth_ = depth;
};

void Chorus::SetModFrequency( double frequency ) {
	mods_[0].SetFrequency( frequency );
	mods_[1].SetFrequency( frequency * 1.1111 );
}

NAMESPACE_AUDIO_END
