#ifndef _AudioCore_DRUMMER_H
#define _AudioCore_DRUMMER_H


NAMESPACE_AUDIO_BEGIN


const int DRUM_NUMWAVES = 11;
const int DRUM_POLYPHONY = 4;

class Drummer : public Instrument {
public:

	Drummer();
	~Drummer();
	void NoteOn( double instrument, double amplitude );
	void NoteOff( double amplitude );
	double Tick( unsigned int channel = 0 );
	AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 );

protected:

	FileWaveIn waves_[DRUM_POLYPHONY];
	OnePole  filters_[DRUM_POLYPHONY];
	Vector<int> sound_order_;
	Vector<int> sound_number_;
	int sounding_count;
};


NAMESPACE_AUDIO_END

#endif
