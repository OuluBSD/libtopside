#ifndef _AudioCore_Midi_h_
#define _AudioCore_Midi_h_

NAMESPACE_TOPSIDE_BEGIN


class MidiFrame {
	
public:
	Vector<const MidiIO::Event*> midi;
	
	void Reset() {midi.SetCount(0);}
};


NAMESPACE_TOPSIDE_END

#endif
