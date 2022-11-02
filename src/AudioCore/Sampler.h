#ifndef _AudioCore_SAMPLER_H
#define _AudioCore_SAMPLER_H


NAMESPACE_AUDIO_BEGIN


class Sampler : public Instrument {
public:

	Sampler();
	virtual ~Sampler();
	virtual void SetFrequency( double frequency ) = 0;
	void KeyOn();
	void KeyOff();
	virtual void NoteOff( double amplitude );
	virtual void ControlChange( int number, double value ) = 0;
	virtual double Tick( unsigned int channel = 0 ) = 0;
	virtual AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 ) = 0;

protected:

	ADSR adsr_;
	Vector<FileWaveIn*> attacks_;
	Vector<FileLoop*> loops_;
	OnePole filter_;
	double base_frequency_;
	Vector<double> attack_ratios_;
	Vector<double> loop_ratios_;
	double attackGain_;
	double loop_gain_;

};

NAMESPACE_AUDIO_END

#endif
