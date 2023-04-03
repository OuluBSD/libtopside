#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

Fir::Fir() {
	b_.Add( 1.0f );
	inputs_.SetCount( 1, 1, 0.0f );
}

Fir::Fir( Vector<float>& coefficients ) {
	if ( coefficients.GetCount() == 0 ) {
		LOG("Fir: coefficient vector must have size > 0!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	gain_ = 1.0f;
	b_ <<= coefficients;
	inputs_.SetCount( b_.GetCount(), 1, 0.0f );
	this->Clear();
}

Fir::~Fir() {
}

void Fir::SetCoefficients( Vector<float>& coefficients, bool ClearState ) {
	if ( coefficients.GetCount() == 0 ) {
		LOG("Fir::SetCoefficients: coefficient vector must have size > 0!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	if ( b_.GetCount() != coefficients.GetCount() ) {
		b_ <<= coefficients;
		inputs_.SetCount( b_.GetCount(), 1, 0.0f );
	}
	else {
		for ( int i = 0; i < b_.GetCount(); i++ ) b_[i] = coefficients[i];
	}

	if ( ClearState ) this->Clear();
}

NAMESPACE_AUDIO_END
