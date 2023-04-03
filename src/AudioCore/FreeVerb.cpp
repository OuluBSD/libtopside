#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN


const float FreeVerb::fixedGain = 0.015;
const float FreeVerb::scaleWet = 3;
const float FreeVerb::scaleDry = 2;
const float FreeVerb::scaleDamp = 0.4;
const float FreeVerb::scaleRoom = 0.28;
const float FreeVerb::offsetRoom = 0.7;
int FreeVerb::cDelayLengths[] = {1617, 1557, 1491, 1422, 1356, 1277, 1188, 1116};
int FreeVerb::aDelayLengths[] = {225, 556, 441, 341};

FreeVerb::FreeVerb() {
	last_frame_.SetCount( 1, 2, 0.0f );
	Effect::SetEffectMix( 0.75 );
	roomSizeMem_ = (0.75 * scaleRoom) + offsetRoom;
	dampMem_ = 0.25 * scaleDamp;
	width_ = 1.0f;
	frozenMode_ = false;
	Refresh();
	gain_ = fixedGain;
	g_ = 0.5;
	float fsScale = Audio::GetSampleRate() / 44100.0f;

	if ( fsScale != 1.0f ) {
		for ( int i = 0; i < nCombs; i++ )
			cDelayLengths[i] = (int) floor(fsScale * cDelayLengths[i]);

		for ( int i = 0; i < nAllpasses; i++ )
			aDelayLengths[i] = (int) floor(fsScale * aDelayLengths[i]);
	}

	for ( int i = 0; i < nCombs; i++ ) {
		combDelayL_[i].SetMaximumDelay( cDelayLengths[i] );
		combDelayL_[i].SetDelay( cDelayLengths[i] );
		combDelayR_[i].SetMaximumDelay( cDelayLengths[i] + stereoSpread );
		combDelayR_[i].SetDelay( cDelayLengths[i] + stereoSpread );
	}

	for (int i = 0; i < nAllpasses; i++) {
		allPassDelayL_[i].SetMaximumDelay( aDelayLengths[i] );
		allPassDelayL_[i].SetDelay( aDelayLengths[i] );
		allPassDelayR_[i].SetMaximumDelay( aDelayLengths[i] + stereoSpread );
		allPassDelayR_[i].SetDelay( aDelayLengths[i] + stereoSpread );
	}
}

FreeVerb::~FreeVerb() {
}

void FreeVerb::LoadState(const ArrayMap<String, Object>& state) {
	int i;
	
	i = state.Find(".mix");
	if (i >= 0)
		SetEffectMix(state[i].ToDouble());
	
	i = state.Find(".roomsize");
	if (i >= 0)
		SetRoomSize(state[i].ToDouble());
	
}

void FreeVerb::SetEffectMix( float mix ) {
	Effect::SetEffectMix( mix );
	Refresh();
}

void FreeVerb::SetRoomSize( float roomSize ) {
	roomSizeMem_ = (roomSize * scaleRoom) + offsetRoom;
	Refresh();
}

float FreeVerb::GetRoomSize() {
	return (roomSizeMem_ - offsetRoom) / scaleRoom;
}

void FreeVerb::SetDamping( float damping ) {
	dampMem_ = damping * scaleDamp;
	Refresh();
}

float FreeVerb::GetDamping() {
	return dampMem_ / scaleDamp;
}

void FreeVerb::SetWidth( float width ) {
	width_ = width;
	Refresh();
}

float FreeVerb::GetWidth() {
	return width_;
}

void FreeVerb::SetMode( bool isFrozen ) {
	frozenMode_ = isFrozen;
	Refresh();
}

float FreeVerb::GetMode() {
	return frozenMode_;
}

void FreeVerb::Refresh() {
	float wet = scaleWet * effect_mix_;
	dry_ = scaleDry * (1.0f - effect_mix_);
	wet /= (wet + dry_);
	dry_ /= (wet + dry_);
	wet1_ = wet * (width_ / 2.0 + 0.5);
	wet2_ = wet * (1.0f - width_) / 2.0f;

	if ( frozenMode_ ) {
		roomSize_ = 1.0f;
		damp_ = 0.0f;
		gain_ = 0.0f;
	}
	else {
		roomSize_ = roomSizeMem_;
		damp_ = dampMem_;
		gain_ = fixedGain;
	}

	for ( int i = 0; i < nCombs; i++ ) {
		combLPL_[i].SetCoefficients(1.0f - damp_, -damp_);
		combLPR_[i].SetCoefficients(1.0f - damp_, -damp_);
	}
}

void FreeVerb::Clear() {
	for ( int i = 0; i < nCombs; i++ ) {
		combDelayL_[i].Clear();
		combDelayR_[i].Clear();
	}

	for ( int i = 0; i < nAllpasses; i++ ) {
		allPassDelayL_[i].Clear();
		allPassDelayR_[i].Clear();
	}

	last_frame_[0] = 0.0f;
	last_frame_[1] = 0.0f;
}

AudioFrames& FreeVerb::Tick( AudioFrames& frames, int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() - 1 ) {
		LOG("FreeVerb::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	float* samples = &frames[channel];
	int step = frames.GetChannelCount();

	for ( int i = 0; i < frames.GetFrameCount(); i++, samples += step ) {
		*samples = Tick( *samples, *(samples + 1) );
		*(samples + 1) = last_frame_[1];
	}

	return frames;
}

AudioFrames& FreeVerb::Tick( AudioFrames& in_frames, AudioFrames& out_frames, int in_channel, int out_channel ) {
	#if defined(flagDEBUG)

	if ( in_channel >= in_frames.GetChannelCount() || out_channel >= out_frames.GetChannelCount() - 1 ) {
		LOG("FreeVerb::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	float* in_samples = &in_frames[in_channel];
	float* out_samples = &out_frames[out_channel];
	int in_step = in_frames.GetChannelCount();
	int out_step = out_frames.GetChannelCount();
	bool stereoInput = ( in_frames.GetChannelCount() > in_channel + 1 ) ? true : false;

	for ( int i = 0; i < in_frames.GetFrameCount(); i++, in_samples += in_step, out_samples += out_step) {
		if ( stereoInput )
			*out_samples = Tick( *in_samples, *(in_samples + 1) );
		else
			*out_samples = Tick( *in_samples );

		*(out_samples + 1) = last_frame_[1];
	}

	return out_frames;
}


NAMESPACE_AUDIO_END
