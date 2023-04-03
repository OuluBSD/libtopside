#ifndef _AudioCore_PITSHIFT_H
#define _AudioCore_PITSHIFT_H


NAMESPACE_AUDIO_BEGIN


const int max_delay = 5024;

class PitchShift : public Effect {
public:

	PitchShift();
	void Clear() override;
	void SetShift( float shift );

	float GetLastOut() const {
		return last_frame_[0];
	};

	float Tick( float input, int channel=0 ) override;
	AudioFrames& Tick( AudioFrames& frames, int channel = 0 );
	AudioFrames& Tick( AudioFrames& in_frames, AudioFrames& out_frames, int in_channel = 0, int out_channel = 0 );

protected:

	DelayL delay_line_[2];
	float delay_[2];
	float env_[2];
	float rate_;
	int delay_length_;
	int half_length_;

};

inline float PitchShift::Tick( float input, int channel ) {
	delay_[0] += rate_;

	while ( delay_[0] > max_delay - 12 ) delay_[0] -= delay_length_;

	while ( delay_[0] < 12 ) delay_[0] += delay_length_;

	delay_[1] = delay_[0] + half_length_;

	while ( delay_[1] > max_delay - 12 ) delay_[1] -= delay_length_;

	while ( delay_[1] < 12 ) delay_[1] += delay_length_;

	delay_line_[0].SetDelay( delay_[0] );
	delay_line_[1].SetDelay( delay_[1] );
	env_[1] = fabs( ( delay_[0] - half_length_ + 12 ) * ( 1.0f / (half_length_ + 12 ) ) );
	env_[0] = 1.0f - env_[1];
	last_frame_[0] =  env_[0] * delay_line_[0].Tick( input );
	last_frame_[0] += env_[1] * delay_line_[1].Tick( input );
	last_frame_[0] *= effect_mix_;
	last_frame_[0] += ( 1.0f - effect_mix_ ) * input;
	return last_frame_[0];
}

NAMESPACE_AUDIO_END

#endif

