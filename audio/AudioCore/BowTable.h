#ifndef _AudioCore_BOWTABL_H
#define _AudioCore_BOWTABL_H


NAMESPACE_AUDIO_BEGIN


class BowTable : public Function {
public:

	BowTable() : offset_(0.0), slope_(0.1), min_output_(0.01), max_output_(0.98) {};
	
	void SetOffset( double offset ) {
		offset_ = offset;
	};

	void SetSlope( double slope ) {
		slope_ = slope;
	};

	void SetMinOutput( double minimum ) {
		min_output_ = minimum;
	};

	void SetMaxOutput( double maximum ) {
		max_output_ = maximum;
	};

	double Tick( double input );
	AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 );
	AudioFrames& Tick( AudioFrames& in_frames, AudioFrames& out_frames, unsigned int in_channel = 0, unsigned int out_channel = 0 );

protected:

	double offset_;
	double slope_;
	double min_output_;
	double max_output_;

};

inline double BowTable::Tick( double input ) {
	double sample  = input + offset_;
	sample *= slope_;
	last_frame_[0] = (double) fabs( (double) sample ) + (double) 0.75;
	last_frame_[0] = (double) pow( last_frame_[0], (double) - 4.0 );

	if ( last_frame_[0] < min_output_ ) last_frame_[0] = min_output_;

	if ( last_frame_[0] > max_output_ ) last_frame_[0] = max_output_;

	return last_frame_[0];
}

inline AudioFrames& BowTable::Tick( AudioFrames& frames, unsigned int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() ) {
		LOG("BowTable::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	double* samples = &frames[channel];
	unsigned int step = frames.GetChannelCount();

	for ( unsigned int i = 0; i < frames.GetFrameCount(); i++, samples += step ) {
		*samples = *samples + offset_;
		*samples *= slope_;
		*samples = (double) fabs( (double) * samples ) + 0.75;
		*samples = (double) pow( *samples, (double) - 4.0 );

		if ( *samples > 1.0) *samples = 1.0;
	}

	last_frame_[0] = *(samples - step);
	return frames;
}

inline AudioFrames& BowTable::Tick( AudioFrames& in_frames, AudioFrames& out_frames, unsigned int in_channel, unsigned int out_channel ) {
	#if defined(flagDEBUG)

	if ( in_channel >= in_frames.GetChannelCount() || out_channel >= out_frames.GetChannelCount() ) {
		LOG("BowTable::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	double* in_samples = &in_frames[in_channel];
	double* out_samples = &out_frames[out_channel];
	unsigned int in_step = in_frames.GetChannelCount(), out_step = out_frames.GetChannelCount();

	for ( unsigned int i = 0; i < in_frames.GetFrameCount(); i++, in_samples += in_step, out_samples += out_step ) {
		*out_samples = *in_samples + offset_;
		*out_samples *= slope_;
		*out_samples = (double) fabs( (double) * out_samples ) + 0.75;
		*out_samples = (double) pow( *out_samples, (double) - 4.0 );

		if ( *out_samples > 1.0) *out_samples = 1.0;
	}

	last_frame_[0] = *(out_samples - out_step);
	return in_frames;
}

NAMESPACE_AUDIO_END

#endif
