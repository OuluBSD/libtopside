#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

Fir::Fir() {
	b_.Add( 1.0 );
	inputs_.SetCount( 1, 1, 0.0 );
}

Fir::Fir( Vector<double>& coefficients ) {
	if ( coefficients.GetCount() == 0 ) {
		LOG("Fir: coefficient vector must have size > 0!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	gain_ = 1.0;
	b_ <<= coefficients;
	inputs_.SetCount( b_.GetCount(), 1, 0.0 );
	this->Clear();
}

Fir::~Fir() {
}

void Fir::SetCoefficients( Vector<double>& coefficients, bool ClearState ) {
	if ( coefficients.GetCount() == 0 ) {
		LOG("Fir::SetCoefficients: coefficient vector must have size > 0!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	if ( b_.GetCount() != coefficients.GetCount() ) {
		b_ <<= coefficients;
		inputs_.SetCount( b_.GetCount(), 1, 0.0 );
	}
	else {
		for ( unsigned int i = 0; i < b_.GetCount(); i++ ) b_[i] = coefficients[i];
	}

	if ( ClearState ) this->Clear();
}

NAMESPACE_AUDIO_END
