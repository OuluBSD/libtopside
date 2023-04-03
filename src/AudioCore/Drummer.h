#ifndef _AudioCore_DRUMMER_H
#define _AudioCore_DRUMMER_H


NAMESPACE_AUDIO_BEGIN


const int DRUM_NUMWAVES = 11;
const int DRUM_POLYPHONY = 64;

class Drummer : public Instrument {
public:

	Drummer();
	~Drummer();
	void SetPreset(String preset);
	void NoteOn( float instrument, float amplitude );
	void NoteOff( float amplitude );
	float Tick( int channel = 0 );
	AudioFrames& Tick( AudioFrames& frames, int channel = 0 );
	
protected:

	FileWaveIn waves_[DRUM_POLYPHONY];
	OnePole  filters_[DRUM_POLYPHONY];
	Vector<int> sound_order_;
	Vector<int> sound_number_;
	int sounding_count;
	VectorMap<int, String> preset;
	bool skip_note_off = true;
	
};


NAMESPACE_AUDIO_END

#endif
