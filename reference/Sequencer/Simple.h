#ifndef _Sequencer_Simple_h_
#define _Sequencer_Simple_h_

NAMESPACE_TOPSIDE_BEGIN

class SimpleOscillator : public Core {
	
	struct Note {
		double frequency = 1;
		double amplitude = 1.0;
		double phase = 0.0;
		
		double Tick();
	};
	
	SimpleStereoMixer mix;
	ArrayMap<double, Note> notes;
	SpinLock lock;
	
public:
	virtual void Tick(AudioFrames& frames);
	virtual void NoteOn(double frequency, double amplitude = 1.0);
	virtual void NoteOff(double frequency);
	virtual void Configure(const CoreParams& params);
};
	
class SimpleReverb : public Core {
	
	struct Channel {
		DelayLine l[4];
		double prev_value = 0;
	};
	
	double prev_gain = 0.6;
	double comb_gain = 0.2;
	double mix = 0.7;
	
	Channel ch[CH_COUNT];
	
public:
	SimpleReverb();
	virtual void Tick(AudioFrames& prev, AudioFrames& frames);
	virtual void NoteOn(double frequency, double amplitude = 1.0);
	virtual void NoteOff(double frequency);
	virtual void Configure(const CoreParams& params);
};


NAMESPACE_TOPSIDE_END

#endif
