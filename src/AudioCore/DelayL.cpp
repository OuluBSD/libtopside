#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

DelayL::DelayL( float delay, int max_delay ) {
	if ( delay < 0.0f ) {
		LOG("DelayL::DelayL: delay must be >= 0.0f!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	if ( delay > (float) max_delay ) {
		LOG("DelayL::DelayL: max_delay must be > than delay argument!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	if ( max_delay + 1 > inputs_.GetCount() )
		inputs_.SetCount( max_delay + 1, 1, 0.0f );

	in_point_ = 0;
	this->SetDelay( delay );
	do_next_out_ = true;
}

DelayL::~DelayL() {
}

void DelayL::SetMaximumDelay( int delay ) {
	if ( delay < inputs_.GetCount() ) return;

	inputs_.SetCount(delay + 1, 1, 0.0f);
}

float DelayL::GetTapOut( int tap_delay ) {
	long tap = in_point_ - tap_delay - 1;

	while ( tap < 0 )
		tap += inputs_.GetCount();

	return inputs_[tap];
}

void DelayL::TapIn( float value, int tap_delay ) {
	long tap = in_point_ - tap_delay - 1;

	while ( tap < 0 )
		tap += inputs_.GetCount();

	inputs_[tap] = value;
}

NAMESPACE_AUDIO_END
