#ifndef _AudioCore_FM_H
#define _AudioCore_FM_H


NAMESPACE_AUDIO_BEGIN


class FM : public Instrument {
public:

	FM( int operators = 4 );
	virtual ~FM();
	void LoadWaves( const char** filenames );
	virtual void SetFrequency( float frequency );
	void SetRatio( int waveIndex, float ratio );
	void SetGain( int waveIndex, float gain );

	void SetModulationSpeed( float mod_speed ) {
		vibrato_.SetFrequency( mod_speed );
	};

	void SetModulationDepth( float mod_depth ) {
		mod_depth_ = mod_depth;
	};

	void SetControl1( float cVal ) {
		control1_ = cVal * 2.0f;
	};

	void SetControl2( float cVal ) {
		control2_ = cVal * 2.0f;
	};

	void KeyOn();
	void KeyOff();
	void NoteOff( float amplitude );
	virtual void ControlChange( int number, float value );
	virtual float Tick( int ) = 0;
	virtual AudioFrames& Tick( AudioFrames& frames, int channel = 0 ) = 0;

protected:

	Vector<ADSR*> adsr_;
	Vector<FileLoop*> waves_;
	SineWave vibrato_;
	TwoZero  twozero_;
	int nOperators_;
	float base_frequency_;
	Vector<float> ratios_;
	Vector<float> gains_;
	float mod_depth_;
	float control1_;
	float control2_;
	float fm_gains_[100];
	float fm_sus_levels_[16];
	float fm_attr_times_[32];

};

NAMESPACE_AUDIO_END

#endif
