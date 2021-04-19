#ifndef _Sequencer_Midi_h_
#define _Sequencer_Midi_h_


NAMESPACE_OULU_BEGIN


class Midi {
	
protected:
	friend void process_midi(PtTimestamp timestamp, void *userData);
	
	static const int IN_QUEUE_SIZE = 1024;
	
	const PmDeviceInfo *info;
	PmQueue *in_queue;
	int id = 0;
	PmStream *midi_in;
	
	
public:
	typedef Midi CLASSNAME;
	Midi();
	~Midi();
	
	Callback2<int, int> WhenNote;
	
};

inline Midi& GetMidi() {return Single<Midi>();}


NAMESPACE_OULU_END

#endif
