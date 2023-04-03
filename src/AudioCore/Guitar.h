#ifndef _AudioCore_GUITAR_H
#define _AudioCore_GUITAR_H


NAMESPACE_AUDIO_BEGIN


class Guitar : public Instrument {
public:

	Guitar( int nStrings = 6, String bodyfile = "" );
	void Clear() override;
	void SetBodyFile( String bodyfile = "" );
	void SetPluckPosition( float position, int string = -1 );
	void SetLoopGain( float gain, int string = -1 );
	void SetFrequency( float frequency, int string );
	void SetFrequency( float frequency ) override;
	void NoteOn( float frequency, float amplitude, int string );
	void NoteOff( float amplitude, int string );
	void ControlChange( int number, float value, int string );
	void NoteOn( float frequency, float amplitude ) override;
	void NoteOff( float amplitude ) override;
	void ControlChange( int number, float value) override;
	
	int GetString(float frequency);
	
	float GetLastOut() {
		return last_frame_[0];
	};

	float Tick( float input = 0.0f );
	AudioFrames& Tick( AudioFrames& frames, int channel = 0 ) override;
	AudioFrames& Tick( AudioFrames& in_frames, AudioFrames& out_frames, int in_channel = 0, int out_channel = 0 );
	float Tick( int channel = 0 ) override;
	
protected:

	Vector< Twang > strings_;
	Vector< int > stringState_;
	Vector< int > decayCounter_;
	Vector< int > filePointer_;
	Vector< float > pluckGains_;

	OnePole   pick_filter_;
	OnePole   couplingFilter_;
	float  couplingGain_;
	AudioFrames excitation_;
	AudioFrames last_frame_;
};

inline float Guitar::Tick( int channel ) {
	return Tick(0.0f);
}

inline float Guitar::Tick( float input ) {
	float temp, output = 0.0f;
	last_frame_[0] /= strings_.GetCount();

	for ( int i = 0; i < strings_.GetCount(); i++ ) {
		if ( stringState_[i] ) {
			temp = input;

			if ( filePointer_[i] < excitation_.GetFrameCount() && pluckGains_[i] > 0.2f )
				temp += pluckGains_[i] * excitation_[filePointer_[i]++];

			temp += couplingGain_ * couplingFilter_.Tick( last_frame_[0] );
			output += strings_[i].Tick( temp );

			if ( stringState_[i] == 1 ) {
				if ( fabs( strings_[i].GetLastOut() ) < 0.001 ) decayCounter_[i]++;
				else decayCounter_[i] = 0;

				if ( decayCounter_[i] > (int) floor( 0.1 * Audio::GetSampleRate() ) ) {
					stringState_[i] = 0;
					decayCounter_[i] = 0;
				}
			}
		}
	}

	return last_frame_[0] = output;
}

inline AudioFrames& Guitar::Tick( AudioFrames& frames, int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() ) {
		LOG("Guitar::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	float* samples = &frames[channel];
	int step = frames.GetChannelCount();

	for ( int i = 0; i < frames.GetFrameCount(); i++, samples += step )
		* samples = Tick( *samples );

	return frames;
}

inline AudioFrames& Guitar::Tick( AudioFrames& in_frames, AudioFrames& out_frames, int in_channel, int out_channel ) {
	#if defined(flagDEBUG)

	if ( in_channel >= in_frames.GetChannelCount() || out_channel >= out_frames.GetChannelCount() ) {
		LOG("Guitar::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	float* in_samples = &in_frames[in_channel];
	float* out_samples = &out_frames[out_channel];
	int in_step = in_frames.GetChannelCount(), out_step = out_frames.GetChannelCount();

	for ( int i = 0; i < in_frames.GetFrameCount(); i++, in_samples += in_step, out_samples += out_step )
		* out_samples = Tick( *in_samples );

	return in_frames;
}

NAMESPACE_AUDIO_END

#endif
