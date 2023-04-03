#ifndef _AudioCore_SAMPLER_H
#define _AudioCore_SAMPLER_H


NAMESPACE_AUDIO_BEGIN


class Sampler : public Instrument {
public:

	Sampler();
	virtual ~Sampler();
	virtual void SetFrequency( float frequency ) = 0;
	void KeyOn();
	void KeyOff();
	virtual void NoteOff( float amplitude );
	virtual void ControlChange( int number, float value ) = 0;
	virtual float Tick( int channel = 0 ) = 0;
	virtual AudioFrames& Tick( AudioFrames& frames, int channel = 0 ) = 0;

protected:

	ADSR adsr_;
	Vector<FileWaveIn*> attacks_;
	Vector<FileLoop*> loops_;
	OnePole filter_;
	float base_frequency_;
	Vector<float> attack_ratios_;
	Vector<float> loop_ratios_;
	float attackGain_;
	float loop_gain_;

};

NAMESPACE_AUDIO_END

#endif
