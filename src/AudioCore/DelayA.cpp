#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

DelayA::DelayA( float delay, int max_delay ) {
	if ( delay < 0.5f ) {
		LOG("DelayA::DelayA: delay must be >= 0.5!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	if ( delay > (float) max_delay ) {
		LOG("DelayA::DelayA: max_delay must be > than delay argument!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	if ( max_delay + 1 > inputs_.GetCount() )
		inputs_.SetCount( max_delay + 1, 1, 0.0f );

	in_point_ = 0;
	this->SetDelay( delay );
	ap_input_ = 0.0f;
	do_next_out_ = true;
}

DelayA::~DelayA() {
}

void DelayA::Clear() {
	for ( int i = 0; i < inputs_.GetCount(); i++ )
		inputs_[i] = 0.0f;

	last_frame_[0] = 0.0f;
	ap_input_ = 0.0f;
}

void DelayA::SetMaximumDelay( int delay ) {
	if ( delay < inputs_.GetCount() ) return;

	inputs_.SetCount(delay + 1, 1, 0.0f);
}

void DelayA::SetDelay( float delay ) {
	int GetCount = inputs_.GetCount();

	if ( delay + 1 > GetCount ) {
		LOG("DelayA::SetDelay: argument (" << delay << ") greater than maximum!");
		HandleError( AudioError::WARNING );
		return;
	}

	if ( delay < 0.5f ) {
		LOG("DelayA::SetDelay: argument (" << delay << ") less than 0.5f not possible!");
		HandleError( AudioError::WARNING );
	}

	float out_pointer = in_point_ - delay + 1.0f;
	delay_ = delay;

	while ( out_pointer < 0 )
		out_pointer += GetCount;

	out_point_ = (long) out_pointer;

	if ( out_point_ == GetCount ) out_point_ = 0;

	alpha_ = 1.0f + out_point_ - out_pointer;

	if ( alpha_ < 0.5f ) {
		out_point_ += 1;

		if ( out_point_ >= GetCount ) out_point_ -= GetCount;

		alpha_ += (float) 1.0f;
	}

	coeff_ = (1.0f - alpha_) / (1.0f + alpha_);
}

float DelayA::GetTapOut( int tap_delay ) {
	long tap = in_point_ - tap_delay - 1;

	while ( tap < 0 )
		tap += inputs_.GetCount();

	return inputs_[tap];
}

void DelayA::TapIn( float value, int tap_delay ) {
	long tap = in_point_ - tap_delay - 1;

	while ( tap < 0 )
		tap += inputs_.GetCount();

	inputs_[tap] = value;
}

NAMESPACE_AUDIO_END
