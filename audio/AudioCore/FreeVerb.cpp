#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN


const double FreeVerb::fixedGain = 0.015;
const double FreeVerb::scaleWet = 3;
const double FreeVerb::scaleDry = 2;
const double FreeVerb::scaleDamp = 0.4;
const double FreeVerb::scaleRoom = 0.28;
const double FreeVerb::offsetRoom = 0.7;
int FreeVerb::cDelayLengths[] = {1617, 1557, 1491, 1422, 1356, 1277, 1188, 1116};
int FreeVerb::aDelayLengths[] = {225, 556, 441, 341};

FreeVerb::FreeVerb() {
	last_frame_.SetCount( 1, 2, 0.0 );
	Effect::SetEffectMix( 0.75 );
	roomSizeMem_ = (0.75 * scaleRoom) + offsetRoom;
	dampMem_ = 0.25 * scaleDamp;
	width_ = 1.0;
	frozenMode_ = false;
	Refresh();
	gain_ = fixedGain;
	g_ = 0.5;
	double fsScale = Audio::GetSampleRate() / 44100.0;

	if ( fsScale != 1.0 ) {
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

void FreeVerb::SetEffectMix( double mix ) {
	Effect::SetEffectMix( mix );
	Refresh();
}

void FreeVerb::SetRoomSize( double roomSize ) {
	roomSizeMem_ = (roomSize * scaleRoom) + offsetRoom;
	Refresh();
}

double FreeVerb::GetRoomSize() {
	return (roomSizeMem_ - offsetRoom) / scaleRoom;
}

void FreeVerb::SetDamping( double damping ) {
	dampMem_ = damping * scaleDamp;
	Refresh();
}

double FreeVerb::GetDamping() {
	return dampMem_ / scaleDamp;
}

void FreeVerb::SetWidth( double width ) {
	width_ = width;
	Refresh();
}

double FreeVerb::GetWidth() {
	return width_;
}

void FreeVerb::SetMode( bool isFrozen ) {
	frozenMode_ = isFrozen;
	Refresh();
}

double FreeVerb::GetMode() {
	return frozenMode_;
}

void FreeVerb::Refresh() {
	double wet = scaleWet * effect_mix_;
	dry_ = scaleDry * (1.0 - effect_mix_);
	wet /= (wet + dry_);
	dry_ /= (wet + dry_);
	wet1_ = wet * (width_ / 2.0 + 0.5);
	wet2_ = wet * (1.0 - width_) / 2.0;

	if ( frozenMode_ ) {
		roomSize_ = 1.0;
		damp_ = 0.0;
		gain_ = 0.0;
	}
	else {
		roomSize_ = roomSizeMem_;
		damp_ = dampMem_;
		gain_ = fixedGain;
	}

	for ( int i = 0; i < nCombs; i++ ) {
		combLPL_[i].SetCoefficients(1.0 - damp_, -damp_);
		combLPR_[i].SetCoefficients(1.0 - damp_, -damp_);
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

	last_frame_[0] = 0.0;
	last_frame_[1] = 0.0;
}

AudioFrames& FreeVerb::Tick( AudioFrames& frames, unsigned int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() - 1 ) {
		LOG("FreeVerb::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	double* samples = &frames[channel];
	unsigned int step = frames.GetChannelCount();

	for ( unsigned int i = 0; i < frames.GetFrameCount(); i++, samples += step ) {
		*samples = Tick( *samples, *(samples + 1) );
		*(samples + 1) = last_frame_[1];
	}

	return frames;
}

AudioFrames& FreeVerb::Tick( AudioFrames& in_frames, AudioFrames& out_frames, unsigned int in_channel, unsigned int out_channel ) {
	#if defined(flagDEBUG)

	if ( in_channel >= in_frames.GetChannelCount() || out_channel >= out_frames.GetChannelCount() - 1 ) {
		LOG("FreeVerb::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	double* in_samples = &in_frames[in_channel];
	double* out_samples = &out_frames[out_channel];
	unsigned int in_step = in_frames.GetChannelCount();
	unsigned int out_step = out_frames.GetChannelCount();
	bool stereoInput = ( in_frames.GetChannelCount() > in_channel + 1 ) ? true : false;

	for ( unsigned int i = 0; i < in_frames.GetFrameCount(); i++, in_samples += in_step, out_samples += out_step) {
		if ( stereoInput )
			*out_samples = Tick( *in_samples, *(in_samples + 1) );
		else
			*out_samples = Tick( *in_samples );

		*(out_samples + 1) = last_frame_[1];
	}

	return out_frames;
}


NAMESPACE_AUDIO_END
