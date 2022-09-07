#include "Sequencer.h"

NAMESPACE_TOPSIDE_BEGIN

double SimpleOscillator::Note::Tick() {
	double d = sin(phase * 2 * M_PI) * amplitude;
	double phase_diff = frequency / SRATE;
	phase += phase_diff;
	return d;
}

void SimpleOscillator::Tick(AudioFrames& frames) {
	lock.Enter();
	
	int step = CH_COUNT;
	
	double* samples = frames.output.Begin();
	
	for (int i = 0; i < frames.GetFrameCount(); i++) {
		
		for(int k = 0; k < notes.GetCount(); k++) {
			mix.Add(notes[k].Tick() / 5, 0.0);
		}
		
		for(int i = 0; i < CH_COUNT; i++) {
			double& sample = *samples;
			sample = mix.Tick(i);
			samples++;
		}
		
	}
	
	
	lock.Leave();
}

void SimpleOscillator::NoteOn( double frequency, double amplitude) {
	lock.Enter();
	
	Note& n = notes.GetAdd(frequency);
	n.frequency = frequency;
	n.amplitude = amplitude;
	
	lock.Leave();
}

void SimpleOscillator::NoteOff(double frequency) {
	lock.Enter();
	
	int i = notes.Find(frequency);
	if (i != -1)
		notes.Remove(i);
	
	lock.Leave();
}

void SimpleOscillator::Configure(const CoreParams& params) {
	
}







SimpleReverb::SimpleReverb() {
	
	for(int i = 0; i < CH_COUNT; i++) {
		Channel& c = ch[i];
		if (i % 2 == 0) {
			c.l[0].SetTime(297);
			c.l[1].SetTime(371);
			c.l[2].SetTime(411);
			c.l[3].SetTime(137);
		} else {
			c.l[0].SetTime(277);
			c.l[1].SetTime(393);
			c.l[2].SetTime(409);
			c.l[3].SetTime(155);
		}
	}
}

void SimpleReverb::Tick(AudioFrames& prev, AudioFrames& frames) {
	double* src = prev.output.Begin();
	double* dst = frames.output.Begin();
	
	for (int i = 0; i < frames.GetFrameCount(); i++) {
		
		for(int i = 0; i < CH_COUNT; i++) {
			double in = *src;
			double& out = *dst;
			
			Channel& c = ch[i];
			
			double in2 = in + c.prev_value * prev_gain;
			
			double l0 = c.l[0].Tick(in2);
			double l1 = c.l[1].Tick(in2);
			double l2 = c.l[2].Tick(in2);
			double l3 = c.l[3].Tick(in2);
			
			double sum = in2 + (l0 * 0.65 + l1 * 0.51 + l2 * 0.5 + l3 * 0.73) * comb_gain;
			
			c.prev_value = sum;
			
			out = mix * sum + (1.0 - mix) * in;
			
			dst++;
			src++;
		}
		
	}
}

void SimpleReverb::NoteOn(double frequency, double amplitude) {
	
}

void SimpleReverb::NoteOff(double frequency) {
	
}

void SimpleReverb::Configure(const CoreParams& params) {
	params.Get("prev_gain", prev_gain);
	params.Get("comb_gain", comb_gain);
	params.Get("mix", mix);
}


NAMESPACE_TOPSIDE_END
