#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

NRev::NRev( double T60 ) {
	if ( T60 <= 0.0 ) {
		LOG("NRev::NRev: argument (" << T60 << ") must be positive!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	last_frame_.SetCount( 1, 2, 0.0 );
	int GetCounts[15] = {1433, 1601, 1867, 2053, 2251, 2399, 347, 113, 37, 59, 53, 43, 37, 29, 19};
	double scaler = Audio::GetSampleRate() / 25641.0;
	int delay, i;

	for ( i = 0; i < 15; i++ ) {
		delay = (int) floor(scaler * GetCounts[i]);

		if ( (delay & 1) == 0) delay++;

		while ( !this->IsPrime(delay) ) delay += 2;

		GetCounts[i] = delay;
	}

	for ( i = 0; i < 6; i++ ) {
		comb_delays_[i].SetMaximumDelay( GetCounts[i] );
		comb_delays_[i].SetDelay( GetCounts[i] );
		comb_coeff_[i] = pow(10.0, (-3 * GetCounts[i] / (T60 * Audio::GetSampleRate())));
	}

	for ( i = 0; i < 8; i++ ) {
		allpass_delays_[i].SetMaximumDelay( GetCounts[i + 6] );
		allpass_delays_[i].SetDelay( GetCounts[i + 6] );
	}

	this->SetT60( T60 );
	allpass_coeff_ = 0.7;
	effect_mix_ = 0.3;
	this->Clear();
}

void NRev::Clear() {
	int i;

	for (i = 0; i < 6; i++) comb_delays_[i].Clear();

	for (i = 0; i < 8; i++) allpass_delays_[i].Clear();

	last_frame_[0] = 0.0;
	last_frame_[1] = 0.0;
	lowpass_state_ = 0.0;
}

void NRev::SetT60( double T60 ) {
	if ( T60 <= 0.0 ) {
		LOG("NRev::SetT60: argument (" << T60 << ") must be positive!");
		HandleError( AudioError::WARNING );
		return;
	}

	for ( int i = 0; i < 6; i++ )
		comb_coeff_[i] = pow(10.0, (-3.0 * comb_delays_[i].GetDelay() / (T60 * Audio::GetSampleRate())));
}

AudioFrames& NRev::Tick( AudioFrames& frames, unsigned int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() - 1 ) {
		LOG("NRev::Tick(): channel and AudioFrames arguments are incompatible!");
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

AudioFrames& NRev::Tick( AudioFrames& in_frames, AudioFrames& out_frames, unsigned int in_channel, unsigned int out_channel ) {
	#if defined(flagDEBUG)

	if ( in_channel >= in_frames.GetChannelCount() || out_channel >= out_frames.GetChannelCount() - 1 ) {
		LOG("NRev::Tick(): channel and AudioFrames arguments are incompatible!");
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
