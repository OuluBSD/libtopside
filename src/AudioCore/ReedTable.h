#ifndef _AudioCore_REEDTABLE_H
#define _AudioCore_REEDTABLE_H


NAMESPACE_AUDIO_BEGIN

class ReedTable : public Function {
public:

	ReedTable() : offset_(0.6), slope_(-0.8) {};

	void SetOffset( double offset ) {
		offset_ = offset;
	};

	void SetSlope( double slope ) {
		slope_ = slope;
	};

	double Tick( double input );
	AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 );
	AudioFrames& Tick( AudioFrames& in_frames, AudioFrames& out_frames, unsigned int in_channel = 0, unsigned int out_channel = 0 );

protected:

	double offset_;
	double slope_;

};

inline double ReedTable::Tick( double input ) {
	last_frame_[0] = offset_ + (slope_ * input);

	if ( last_frame_[0] > 1.0) last_frame_[0] = (double) 1.0;

	if ( last_frame_[0] < -1.0) last_frame_[0] = (double) - 1.0;

	return last_frame_[0];
}

inline AudioFrames& ReedTable::Tick( AudioFrames& frames, unsigned int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() ) {
		LOG("ReedTable::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	double* samples = &frames[channel];
	unsigned int step = frames.GetChannelCount();

	for ( unsigned int i = 0; i < frames.GetFrameCount(); i++, samples += step ) {
		*samples = offset_ + (slope_ * *samples);

		if ( *samples > 1.0) *samples = 1.0;

		if ( *samples < -1.0) *samples = -1.0;
	}

	last_frame_[0] = *(samples - step);
	return frames;
}

inline AudioFrames& ReedTable::Tick( AudioFrames& in_frames, AudioFrames& out_frames, unsigned int in_channel, unsigned int out_channel ) {
	#if defined(flagDEBUG)

	if ( in_channel >= in_frames.GetChannelCount() || out_channel >= out_frames.GetChannelCount() ) {
		LOG("ReedTable::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	double* in_samples = &in_frames[in_channel];
	double* out_samples = &out_frames[out_channel];
	unsigned int in_step = in_frames.GetChannelCount(), out_step = out_frames.GetChannelCount();

	for ( unsigned int i = 0; i < in_frames.GetFrameCount(); i++, in_samples += in_step, out_samples += out_step ) {
		*out_samples = offset_ + (slope_ * *in_samples);

		if ( *out_samples > 1.0) *out_samples = 1.0;

		if ( *out_samples < -1.0) *out_samples = -1.0;
	}

	last_frame_[0] = *(out_samples - out_step);
	return in_frames;
}

NAMESPACE_AUDIO_END

#endif