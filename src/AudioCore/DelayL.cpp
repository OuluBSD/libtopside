#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

DelayL::DelayL( double delay, unsigned long max_delay ) {
	if ( delay < 0.0 ) {
		LOG("DelayL::DelayL: delay must be >= 0.0!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	if ( delay > (double) max_delay ) {
		LOG("DelayL::DelayL: max_delay must be > than delay argument!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	if ( max_delay + 1 > inputs_.GetCount() )
		inputs_.SetCount( max_delay + 1, 1, 0.0 );

	in_point_ = 0;
	this->SetDelay( delay );
	do_next_out_ = true;
}

DelayL::~DelayL() {
}

void DelayL::SetMaximumDelay( unsigned long delay ) {
	if ( delay < inputs_.GetCount() ) return;

	inputs_.SetCount(delay + 1, 1, 0.0);
}

double DelayL::GetTapOut( unsigned long tap_delay ) {
	long tap = in_point_ - tap_delay - 1;

	while ( tap < 0 )
		tap += inputs_.GetCount();

	return inputs_[tap];
}

void DelayL::TapIn( double value, unsigned long tap_delay ) {
	long tap = in_point_ - tap_delay - 1;

	while ( tap < 0 )
		tap += inputs_.GetCount();

	inputs_[tap] = value;
}

NAMESPACE_AUDIO_END
