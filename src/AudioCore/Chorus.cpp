#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

Chorus::Chorus( float baseDelay ) {
	last_frame_.SetCount( 1, 2, 0.0f );
	delay_line_[0].SetMaximumDelay( (int) (baseDelay * 1.414f) + 2);
	delay_line_[0].SetDelay( baseDelay );
	delay_line_[1].SetMaximumDelay( (int) (baseDelay * 1.414f) + 2);
	delay_line_[1].SetDelay( baseDelay );
	baseLength_ = baseDelay;
	mods_[0].SetFrequency( 0.2f );
	mods_[1].SetFrequency( 0.222222f );
	mod_depth_ = 0.05f;
	effect_mix_ = 0.5f;
	this->Clear();
}

void Chorus::Clear() {
	delay_line_[0].Clear();
	delay_line_[1].Clear();
	last_frame_[0] = 0.0f;
	last_frame_[1] = 0.0f;
}

void Chorus::SetModDepth( float depth ) {
	if ( depth < 0.0f || depth > 1.0f ) {
		LOG("Chorus::SetModDepth(): depth argument must be between 0.0f - 1.0f!");
		HandleError( AudioError::WARNING );
		return;
	}

	mod_depth_ = depth;
};

void Chorus::SetModFrequency( float frequency ) {
	mods_[0].SetFrequency( frequency );
	mods_[1].SetFrequency( frequency * 1.1111f );
}

NAMESPACE_AUDIO_END
