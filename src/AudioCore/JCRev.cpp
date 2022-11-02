#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

JCRev::JCRev( double T60 ) {
	if ( T60 <= 0.0 ) {
		LOG("JCRev::JCRev: argument (" << T60 << ") must be positive!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	last_frame_.SetCount( 1, 2, 0.0 );
	int GetCounts[9] = {1116, 1356, 1422, 1617, 225, 341, 441, 211, 179};
	double scaler = Audio::GetSampleRate() / 44100.0;
	int delay, i;

	if ( scaler != 1.0 ) {
		for ( i = 0; i < 9; i++ ) {
			delay = (int) floor( scaler * GetCounts[i] );

			if ( (delay & 1) == 0) delay++;

			while ( !this->IsPrime(delay) ) delay += 2;

			GetCounts[i] = delay;
		}
	}

	for ( i = 0; i < 3; i++ ) {
		allpass_delays_[i].SetMaximumDelay( GetCounts[i + 4] );
		allpass_delays_[i].SetDelay( GetCounts[i + 4] );
	}

	for ( i = 0; i < 4; i++ ) {
		comb_delays_[i].SetMaximumDelay( GetCounts[i] );
		comb_delays_[i].SetDelay( GetCounts[i] );
		combFilters_[i].SetPole( 0.2 );
	}

	this->SetT60( T60 );
	outLeftDelay_.SetMaximumDelay( GetCounts[7] );
	outLeftDelay_.SetDelay( GetCounts[7] );
	outRightDelay_.SetMaximumDelay( GetCounts[8] );
	outRightDelay_.SetDelay( GetCounts[8] );
	allpass_coeff_ = 0.7;
	effect_mix_ = 0.3;
	this->Clear();
}

void JCRev::Clear() {
	allpass_delays_[0].Clear();
	allpass_delays_[1].Clear();
	allpass_delays_[2].Clear();
	comb_delays_[0].Clear();
	comb_delays_[1].Clear();
	comb_delays_[2].Clear();
	comb_delays_[3].Clear();
	outRightDelay_.Clear();
	outLeftDelay_.Clear();
	last_frame_[0] = 0.0;
	last_frame_[1] = 0.0;
}

void JCRev::SetT60( double T60 ) {
	if ( T60 <= 0.0 ) {
		LOG("JCRev::SetT60: argument (" << T60 << ") must be positive!");
		HandleError( AudioError::WARNING );
		return;
	}

	for ( int i = 0; i < 4; i++ )
		comb_coeff_[i] = pow(10.0, (-3.0 * comb_delays_[i].GetDelay() / (T60 * Audio::GetSampleRate())));
}

AudioFrames& JCRev::Tick( AudioFrames& frames, unsigned int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() - 1 ) {
		LOG("JCRev::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	double* samples = &frames[channel];
	unsigned int step = frames.GetChannelCount();

	for ( unsigned int i = 0; i < frames.GetFrameCount(); i++, samples += step ) {
		*samples = Tick( *samples );
		*(samples + 1) = last_frame_[1];
	}

	return frames;
}

AudioFrames& JCRev::Tick( AudioFrames& in_frames, AudioFrames& out_frames, unsigned int in_channel, unsigned int out_channel ) {
	#if defined(flagDEBUG)

	if ( in_channel >= in_frames.GetChannelCount() || out_channel >= out_frames.GetChannelCount() - 1 ) {
		LOG("JCRev::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	double* in_samples = &in_frames[in_channel];
	double* out_samples = &out_frames[out_channel];
	unsigned int in_step = in_frames.GetChannelCount(), out_step = out_frames.GetChannelCount();

	for ( unsigned int i = 0; i < in_frames.GetFrameCount(); i++, in_samples += in_step, out_samples += out_step ) {
		*out_samples = Tick( *in_samples );
		*(out_samples + 1) = last_frame_[1];
	}

	return in_frames;
}

NAMESPACE_AUDIO_END
