#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

PRCRev::PRCRev( float T60 ) {
	if ( T60 <= 0.0f ) {
		LOG("PRCRev::PRCRev: argument (" << T60 << ") must be positive!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	last_frame_.SetCount( 1, 2, 0.0f );
	int GetCounts[4] = {341, 613, 1557, 2137};
	float scaler = Audio::GetSampleRate() / 44100.0f;
	int delay, i;

	if ( scaler != 1.0f ) {
		for (i = 0; i < 4; i++)	{
			delay = (int) floor(scaler * GetCounts[i]);

			if ( (delay & 1) == 0) delay++;

			while ( !this->IsPrime(delay) ) delay += 2;

			GetCounts[i] = delay;
		}
	}

	for ( i = 0; i < 2; i++ )	{
		allpass_delays_[i].SetMaximumDelay( GetCounts[i] );
		allpass_delays_[i].SetDelay( GetCounts[i] );
		comb_delays_[i].SetMaximumDelay( GetCounts[i + 2] );
		comb_delays_[i].SetDelay( GetCounts[i + 2] );
	}

	this->SetT60( T60 );
	allpass_coeff_ = 0.7;
	effect_mix_ = 0.5;
	this->Clear();
}

void PRCRev::Clear() {
	allpass_delays_[0].Clear();
	allpass_delays_[1].Clear();
	comb_delays_[0].Clear();
	comb_delays_[1].Clear();
	last_frame_[0] = 0.0f;
	last_frame_[1] = 0.0f;
}

void PRCRev::SetT60( float T60 ) {
	if ( T60 <= 0.0f ) {
		LOG("PRCRev::SetT60: argument (" << T60 << ") must be positive!");
		HandleError( AudioError::WARNING );
		return;
	}

	comb_coeff_[0] = powf(10.0f, (-3.0 * comb_delays_[0].GetDelay() / (T60 * Audio::GetSampleRate())));
	comb_coeff_[1] = powf(10.0f, (-3.0 * comb_delays_[1].GetDelay() / (T60 * Audio::GetSampleRate())));
}

AudioFrames& PRCRev::Tick( AudioFrames& frames, int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() - 1 ) {
		LOG("PRCRev::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	float* samples = &frames[channel];
	int step = frames.GetChannelCount();

	for ( int i = 0; i < frames.GetFrameCount(); i++, samples += step ) {
		*samples = Tick( *samples );
		*(samples + 1) = last_frame_[1];
	}

	return frames;
}

AudioFrames& PRCRev::Tick( AudioFrames& in_frames, AudioFrames& out_frames, int in_channel, int out_channel ) {
	#if defined(flagDEBUG)

	if ( in_channel >= in_frames.GetChannelCount() || out_channel >= out_frames.GetChannelCount() - 1 ) {
		LOG("PRCRev::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	float* in_samples = &in_frames[in_channel];
	float* out_samples = &out_frames[out_channel];
	int in_step = in_frames.GetChannelCount(), out_step = out_frames.GetChannelCount();

	for ( int i = 0; i < in_frames.GetFrameCount(); i++, in_samples += in_step, out_samples += out_step ) {
		*out_samples = Tick( *in_samples );
		*(out_samples + 1) = last_frame_[1];
	}

	return in_frames;
}

NAMESPACE_AUDIO_END
