#ifndef _AudioCore_FM_H
#define _AudioCore_FM_H


NAMESPACE_AUDIO_BEGIN


class FM : public Instrument {
public:

	FM( unsigned int operators = 4 );
	virtual ~FM();
	void LoadWaves( const char** filenames );
	virtual void SetFrequency( double frequency );
	void SetRatio( unsigned int waveIndex, double ratio );
	void SetGain( unsigned int waveIndex, double gain );

	void SetModulationSpeed( double mod_speed ) {
		vibrato_.SetFrequency( mod_speed );
	};

	void SetModulationDepth( double mod_depth ) {
		mod_depth_ = mod_depth;
	};

	void SetControl1( double cVal ) {
		control1_ = cVal * 2.0;
	};

	void SetControl2( double cVal ) {
		control2_ = cVal * 2.0;
	};

	void KeyOn();
	void KeyOff();
	void NoteOff( double amplitude );
	virtual void ControlChange( int number, double value );
	virtual double Tick( unsigned int ) = 0;
	virtual AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 ) = 0;

protected:

	Vector<ADSR*> adsr_;
	Vector<FileLoop*> waves_;
	SineWave vibrato_;
	TwoZero  twozero_;
	unsigned int nOperators_;
	double base_frequency_;
	Vector<double> ratios_;
	Vector<double> gains_;
	double mod_depth_;
	double control1_;
	double control2_;
	double fm_gains_[100];
	double fm_sus_levels_[16];
	double fm_attr_times_[32];

};

NAMESPACE_AUDIO_END

#endif
