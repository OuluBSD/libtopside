#ifndef _AudioCore_BOWTABL_H
#define _AudioCore_BOWTABL_H


NAMESPACE_AUDIO_BEGIN


class BowTable : public Function {
public:

	BowTable() : offset_(0.0f), slope_(0.1f), min_output_(0.01f), max_output_(0.98f) {};
	
	void SetOffset( float offset ) {
		offset_ = offset;
	};

	void SetSlope( float slope ) {
		slope_ = slope;
	};

	void SetMinOutput( float minimum ) {
		min_output_ = minimum;
	};

	void SetMaxOutput( float maximum ) {
		max_output_ = maximum;
	};

	float Tick( float input );
	AudioFrames& Tick( AudioFrames& frames, int channel = 0 );
	AudioFrames& Tick( AudioFrames& in_frames, AudioFrames& out_frames, int in_channel = 0, int out_channel = 0 );

protected:

	float offset_;
	float slope_;
	float min_output_;
	float max_output_;

};

inline float BowTable::Tick( float input ) {
	float sample  = input + offset_;
	sample *= slope_;
	last_frame_[0] = (float) fabs( (float) sample ) + (float) 0.75;
	last_frame_[0] = (float) powf( last_frame_[0], (float) - 4.0 );

	if ( last_frame_[0] < min_output_ ) last_frame_[0] = min_output_;

	if ( last_frame_[0] > max_output_ ) last_frame_[0] = max_output_;

	return last_frame_[0];
}

inline AudioFrames& BowTable::Tick( AudioFrames& frames, int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() ) {
		LOG("BowTable::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	float* samples = &frames[channel];
	int step = frames.GetChannelCount();

	for ( int i = 0; i < frames.GetFrameCount(); i++, samples += step ) {
		*samples = *samples + offset_;
		*samples *= slope_;
		*samples = (float) fabs( (float) * samples ) + 0.75f;
		*samples = (float) powf( *samples, (float) - 4.0f );

		if ( *samples > 1.0f) *samples = 1.0f;
	}

	last_frame_[0] = *(samples - step);
	return frames;
}

inline AudioFrames& BowTable::Tick( AudioFrames& in_frames, AudioFrames& out_frames, int in_channel, int out_channel ) {
	#if defined(flagDEBUG)

	if ( in_channel >= in_frames.GetChannelCount() || out_channel >= out_frames.GetChannelCount() ) {
		LOG("BowTable::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	float* in_samples = &in_frames[in_channel];
	float* out_samples = &out_frames[out_channel];
	int in_step = in_frames.GetChannelCount(), out_step = out_frames.GetChannelCount();

	for ( int i = 0; i < in_frames.GetFrameCount(); i++, in_samples += in_step, out_samples += out_step ) {
		*out_samples = *in_samples + offset_;
		*out_samples *= slope_;
		*out_samples = (float) fabs( (float) * out_samples ) + 0.75f;
		*out_samples = (float) powf( *out_samples, (float) - 4.0f );

		if ( *out_samples > 1.0f) *out_samples = 1.0f;
	}

	last_frame_[0] = *(out_samples - out_step);
	return in_frames;
}

NAMESPACE_AUDIO_END

#endif
