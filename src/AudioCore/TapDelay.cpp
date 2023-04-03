#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

TapDelay::TapDelay( const Vector<int>& taps, int max_delay ) {
	if ( max_delay < 1 ) {
		LOG("TapDelay::TapDelay: max_delay must be > 0!\n");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	for ( int i = 0; i < taps.GetCount(); i++ ) {
		if ( taps[i] > max_delay ) {
			LOG("TapDelay::TapDelay: max_delay must be > than all tap delay values!\n");
			HandleError( AudioError::FUNCTION_ARGUMENT );
		}
	}

	if ( ( max_delay + 1 ) > inputs_.GetCount() )
		inputs_.SetCount( max_delay + 1, 1, 0.0f );

	in_point_ = 0;
	this->SetTapDelays( taps );
}

TapDelay::~TapDelay() {
}

void TapDelay::SetMaximumDelay( int delay ) {
	if ( delay < inputs_.GetCount() ) return;

	for ( int i = 0; i < delays_.GetCount(); i++ ) {
		if ( delay < delays_[i] ) {
			LOG("TapDelay::SetMaximumDelay: argument (" << delay << ") less than a current tap delay Setting (" << delays_[i] << ")!\n");
			HandleError( AudioError::WARNING );
			return;
		}
	}

	inputs_.SetCount( delay + 1 );
}

void TapDelay::SetTapDelays( const Vector<int>& taps ) {
	for ( int i = 0; i < taps.GetCount(); i++ ) {
		if ( taps[i] > inputs_.GetCount() - 1 ) {
			LOG("TapDelay::SetTapDelay: argument (" << taps[i] << ") greater than maximum!\n");
			HandleError( AudioError::WARNING );
			return;
		}
	}

	if ( taps.GetCount() != out_point_.GetCount() ) {
		out_point_.SetCount( taps.GetCount() );
		delays_.SetCount( taps.GetCount() );
		last_frame_.SetCount( 1, (int)taps.GetCount(), 0.0f );
	}

	for ( int i = 0; i < taps.GetCount(); i++ ) {
		if ( in_point_ >= taps[i] ) out_point_[i] = in_point_ - taps[i];
		else out_point_[i] = inputs_.GetCount() + in_point_ - taps[i];

		delays_[i] = taps[i];
	}
}

NAMESPACE_AUDIO_END

