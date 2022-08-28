#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

LentPitchShift::LentPitchShift( double periodRatio, int tMax )
	: inputFrames(0., tMax, 1), outputFrames(0., tMax, 1), ptrFrames(0), inputPtr(0), outputPtr(0.), tMax_(tMax), periodRatio_(periodRatio), zeroFrame(0., tMax, 1) {
	window = new double[2 * tMax_];
	threshold_ = 0.1;
	dt = new double[tMax + 1];
	cumDt = new double[tMax + 1];
	cumDt[0] = 0.;
	dpt = new double[tMax + 1];
	dpt[0]   = 1.;
	input_line_.SetMaximumDelay( 3 * tMax_ );
	outputLine_.SetMaximumDelay( 3 * tMax_ );
	outputLine_.SetDelay( 3 * tMax_ );
}

void LentPitchShift::Clear() {
	input_line_.Clear();
	outputLine_.Clear();
}

void LentPitchShift::SetShift( double shift ) {
	if ( shift <= 0.0 ) periodRatio_ = 1.0;

	periodRatio_ = 1.0 / shift;
}

NAMESPACE_AUDIO_END