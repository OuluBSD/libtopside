#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

Iir::Iir() {
	b_.Add( 1.0 );
	a_.Add( 1.0 );
	inputs_.SetCount( 1, 1, 0.0 );
	outputs_.SetCount( 1, 1, 0.0 );
}

Iir::Iir( Vector<double>& bCoefficients, Vector<double>& aCoefficients ) {
	if ( bCoefficients.GetCount() == 0 || aCoefficients.GetCount() == 0 ) {
		LOG("Iir: a and b coefficient vectors must both have size > 0!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	if ( aCoefficients[0] == 0.0 ) {
		LOG("Iir: a[0] coefficient cannot == 0!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	gain_ = 1.0;
	b_ <<= bCoefficients;
	a_ <<= aCoefficients;
	inputs_.SetCount( b_.GetCount(), 1, 0.0 );
	outputs_.SetCount( a_.GetCount(), 1, 0.0 );
	this->Clear();
}

Iir::~Iir() {
}

void Iir::SetCoefficients( Vector<double>& bCoefficients, Vector<double>& aCoefficients, bool ClearState ) {
	this->SetNumerator( bCoefficients, false );
	this->SetDenominator( aCoefficients, false );

	if ( ClearState ) this->Clear();
}

void Iir::SetNumerator( Vector<double>& bCoefficients, bool ClearState ) {
	if ( bCoefficients.GetCount() == 0 ) {
		LOG("Iir::SetNumerator: coefficient vector must have size > 0!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	if ( b_.GetCount() != bCoefficients.GetCount() ) {
		b_ <<= bCoefficients;
		inputs_.SetCount( b_.GetCount(), 1, 0.0 );
	}
	else {
		for ( unsigned int i = 0; i < b_.GetCount(); i++ ) b_[i] = bCoefficients[i];
	}

	if ( ClearState ) this->Clear();
}

void Iir::SetDenominator( Vector<double>& aCoefficients, bool ClearState ) {
	if ( aCoefficients.GetCount() == 0 ) {
		LOG("Iir::SetDenominator: coefficient vector must have size > 0!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	if ( aCoefficients[0] == 0.0 ) {
		LOG("Iir::SetDenominator: a[0] coefficient cannot == 0!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	if ( a_.GetCount() != aCoefficients.GetCount() ) {
		a_ <<= aCoefficients;
		outputs_.SetCount( a_.GetCount(), 1, 0.0 );
	}
	else {
		for ( unsigned int i = 0; i < a_.GetCount(); i++ ) a_[i] = aCoefficients[i];
	}

	if ( ClearState ) this->Clear();

	if ( a_[0] != 1.0 ) {
		unsigned int i;

		for ( i = 0; i < b_.GetCount(); i++ ) b_[i] /= a_[0];

		for ( i = 1; i < a_.GetCount(); i++ )  a_[i] /= a_[0];
	}
}

NAMESPACE_AUDIO_END
