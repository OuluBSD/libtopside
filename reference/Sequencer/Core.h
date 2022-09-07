#ifndef _Sequencer_Core_h_
#define _Sequencer_Core_h_

#define CH_COUNT 2
#define SRATE 44100


NAMESPACE_TOPSIDE_BEGIN


struct AudioFrames {
	Vector<double> output;
	int fpb = 0;
	int ch_count = 0;

	
	void SetCount(int i, int ch) {fpb = i; ch_count = ch; output.SetCount(i * ch, 0);}
	void Zero() {for(int i = 0; i < output.GetCount(); i++) output[i] = 0;}
	
	int GetCount() const {return output.GetCount();}
	int GetFrameCount() const {return fpb;}
	
	double& operator [](int i) {return output[i];}
	
};

struct CoreParams : Moveable<CoreParams> {
	VectorMap<String, Value> values;
	int factory = 0;
	
	CoreParams& Set(int factory) {this->factory = factory; return *this;}
	CoreParams& Arg(String key, Value value) {values.GetAdd(key) = value; return *this;}
	
	void Serialize(Stream& s) {s % values % factory;}
	
	template <class T>
	void Get(String key, T& o) const {
		int i = values.Find(key);
		if (i != -1)
			o = values[i];
	}
};

class Core {
	
protected:
	friend class System;
	
	int factory = -1;
	
	
public:
	Core() {}
	virtual ~Core() {}
	
	virtual void Tick(AudioFrames& frames) {}
	virtual void Tick(AudioFrames& prev, AudioFrames& frames) {}
	virtual void NoteOn(double frequency, double amplitude = 1.0) = 0;
	virtual void NoteOff(double frequency) = 0;
	virtual void Configure(const CoreParams& params) = 0;
	
};


/*template <class T>
class MultiNoteStereo : public Core {
	
public:
	MultiNoteStereo() {
		for(int i = 0; i < CH_COUNT; i++) {
			ch[i] = new T();
		}
	}
	~MultiNoteStereo() {
		for(int i = 0; i < CH_COUNT; i++) {
			if (ch[i]) {
				delete ch[i];
				ch[i] = NULL;
			}
		}
	}
	
	Instrument* ch[CH_COUNT];
	
	virtual void Tick(AudioFrames& frames) {
		for(int i = 0; i < CH_COUNT; i++)
			ch[i]->Tick(frames, i);
	}
	
	virtual void NoteOn(double frequency, double amplitude = 1.0) {
		for(int i = 0; i < CH_COUNT; i++)
			ch[i]->NoteOn(frequency, amplitude);
	}
	
	virtual void NoteOff(double frequency) {
		for(int i = 0; i < CH_COUNT; i++)
			ch[i]->NoteOff(amplitude);
	}
	
};*/


NAMESPACE_TOPSIDE_END

#endif
