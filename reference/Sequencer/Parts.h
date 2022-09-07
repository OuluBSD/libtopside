#ifndef _Sequencer_Parts_h_
#define _Sequencer_Parts_h_

NAMESPACE_TOPSIDE_BEGIN

class SimpleStereoMixer {
	double value[CH_COUNT];
	
public:
	
	double Tick(int ch) {
		double d = value[ch];
		value[ch] = 0;
		if (d > 1.0) d = 1.0;
		else if (d < -1.0) d = -1.0;
		return d;
	}
	
	void Add(double d, double balance) {
		double left = max(0.0, min(1.0, 1.0 - balance));
		double right = max(0.0, min(1.0, -1.0 + balance));
		value[0] += left * d;
		value[1] += right * d;
	}
};


class DelayLine {
	Vector<double> buf;
	int cursor = 0;
public:
	
	void SetTime(int ms) {
		int count = SRATE * ms / 1000;
		buf.SetCount(count, 0);
	}
	double Tick(double d) {
		int next = (cursor + 1) % buf.GetCount();
		double out = buf[next];
		buf[cursor] = d;
		cursor = next;
		return out;
	}
};

NAMESPACE_TOPSIDE_END

#endif
