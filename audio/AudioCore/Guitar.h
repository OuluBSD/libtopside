#ifndef _AudioCore_GUITAR_H
#define _AudioCore_GUITAR_H


NAMESPACE_AUDIO_BEGIN


class Guitar : public Audio {
public:

	Guitar( unsigned int nStrings = 6, String bodyfile = "" );
	void Clear();
	void SetBodyFile( String bodyfile = "" );
	void SetPluckPosition( double position, int string = -1 );
	void SetLoopGain( double gain, int string = -1 );
	void SetFrequency( double frequency, unsigned int string = 0 );
	void NoteOn( double frequency, double amplitude, unsigned int string = 0 );
	void NoteOff( double amplitude, unsigned int string = 0 );
	void ControlChange( int number, double value, int string = -1 );
	
	double GetLastOut() {
		return last_frame_[0];
	};

	double Tick( double input = 0.0 );
	AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 );
	AudioFrames& Tick( AudioFrames& in_frames, AudioFrames& out_frames, unsigned int in_channel = 0, unsigned int out_channel = 0 );

protected:

	Vector< Twang > strings_;
	Vector< int > stringState_;
	Vector< unsigned int > decayCounter_;
	Vector< unsigned int > filePointer_;
	Vector< double > pluckGains_;

	OnePole   pick_filter_;
	OnePole   couplingFilter_;
	double  couplingGain_;
	AudioFrames excitation_;
	AudioFrames last_frame_;
};

inline double Guitar::Tick( double input ) {
	double temp, output = 0.0;
	last_frame_[0] /= strings_.GetCount();

	for ( unsigned int i = 0; i < strings_.GetCount(); i++ ) {
		if ( stringState_[i] ) {
			temp = input;

			if ( filePointer_[i] < excitation_.GetFrameCount() && pluckGains_[i] > 0.2 )
				temp += pluckGains_[i] * excitation_[filePointer_[i]++];

			temp += couplingGain_ * couplingFilter_.Tick( last_frame_[0] );
			output += strings_[i].Tick( temp );

			if ( stringState_[i] == 1 ) {
				if ( fabs( strings_[i].GetLastOut() ) < 0.001 ) decayCounter_[i]++;
				else decayCounter_[i] = 0;

				if ( decayCounter_[i] > (unsigned int) floor( 0.1 * Audio::GetSampleRate() ) ) {
					stringState_[i] = 0;
					decayCounter_[i] = 0;
				}
			}
		}
	}

	return last_frame_[0] = output;
}

inline AudioFrames& Guitar::Tick( AudioFrames& frames, unsigned int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() ) {
		LOG("Guitar::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	double* samples = &frames[channel];
	unsigned int step = frames.GetChannelCount();

	for ( unsigned int i = 0; i < frames.GetFrameCount(); i++, samples += step )
		* samples = Tick( *samples );

	return frames;
}

inline AudioFrames& Guitar::Tick( AudioFrames& in_frames, AudioFrames& out_frames, unsigned int in_channel, unsigned int out_channel ) {
	#if defined(flagDEBUG)

	if ( in_channel >= in_frames.GetChannelCount() || out_channel >= out_frames.GetChannelCount() ) {
		LOG("Guitar::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	double* in_samples = &in_frames[in_channel];
	double* out_samples = &out_frames[out_channel];
	unsigned int in_step = in_frames.GetChannelCount(), out_step = out_frames.GetChannelCount();

	for ( unsigned int i = 0; i < in_frames.GetFrameCount(); i++, in_samples += in_step, out_samples += out_step )
		* out_samples = Tick( *in_samples );

	return in_frames;
}

NAMESPACE_AUDIO_END

#endif
