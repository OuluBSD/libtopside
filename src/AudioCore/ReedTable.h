#ifndef _AudioCore_REEDTABLE_H
#define _AudioCore_REEDTABLE_H


NAMESPACE_AUDIO_BEGIN

class ReedTable : public Function {
public:

	ReedTable() : offset_(0.6f), slope_(-0.8f) {};

	void SetOffset( float offset ) {
		offset_ = offset;
	};

	void SetSlope( float slope ) {
		slope_ = slope;
	};

	float Tick( float input );
	AudioFrames& Tick( AudioFrames& frames, int channel = 0 );
	AudioFrames& Tick( AudioFrames& in_frames, AudioFrames& out_frames, int in_channel = 0, int out_channel = 0 );

protected:

	float offset_;
	float slope_;

};

inline float ReedTable::Tick( float input ) {
	last_frame_[0] = offset_ + (slope_ * input);

	if ( last_frame_[0] > 1.0f) last_frame_[0] = (float) 1.0f;

	if ( last_frame_[0] < -1.0f) last_frame_[0] = (float) - 1.0f;

	return last_frame_[0];
}

inline AudioFrames& ReedTable::Tick( AudioFrames& frames, int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() ) {
		LOG("ReedTable::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	float* samples = &frames[channel];
	int step = frames.GetChannelCount();

	for ( int i = 0; i < frames.GetFrameCount(); i++, samples += step ) {
		*samples = offset_ + (slope_ * *samples);

		if ( *samples > 1.0f) *samples = 1.0f;

		if ( *samples < -1.0f) *samples = -1.0f;
	}

	last_frame_[0] = *(samples - step);
	return frames;
}

inline AudioFrames& ReedTable::Tick( AudioFrames& in_frames, AudioFrames& out_frames, int in_channel, int out_channel ) {
	#if defined(flagDEBUG)

	if ( in_channel >= in_frames.GetChannelCount() || out_channel >= out_frames.GetChannelCount() ) {
		LOG("ReedTable::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	float* in_samples = &in_frames[in_channel];
	float* out_samples = &out_frames[out_channel];
	int in_step = in_frames.GetChannelCount(), out_step = out_frames.GetChannelCount();

	for ( int i = 0; i < in_frames.GetFrameCount(); i++, in_samples += in_step, out_samples += out_step ) {
		*out_samples = offset_ + (slope_ * *in_samples);

		if ( *out_samples > 1.0f) *out_samples = 1.0f;

		if ( *out_samples < -1.0f) *out_samples = -1.0f;
	}

	last_frame_[0] = *(out_samples - out_step);
	return in_frames;
}

NAMESPACE_AUDIO_END

#endif
