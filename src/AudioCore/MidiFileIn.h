#ifndef _AudioCore_MIDIFILEIN_H
#define _AudioCore_MIDIFILEIN_H


NAMESPACE_AUDIO_BEGIN


class MidiFileIn : public Audio {
public:

	MidiFileIn( String file_name );
	~MidiFileIn();

	int GetFileFormat() const {
		return format_;
	};

	int GetNumberOfTracks() const {
		return nTracks_;
	};

	int GetDivision() const {
		return division_;
	};

	void RewindTrack( int track = 0 );
	float GetTickSeconds( int track = 0 );
	int GetNextEvent( Vector<unsigned char>* event, int track = 0 );
	int GetNextMidiEvent( Vector<unsigned char>* midiEvent, int track = 0 );

protected:

	bool GetVariableLength( int* value );

	FileIn file_;
	int nTracks_;
	int format_;
	int division_;
	bool usingTimeCode_;
	Vector<float> tickSeconds_;
	Vector<long> trackPointers_;
	Vector<long> trackOffsets_;
	Vector<long> trackLengths_;
	Vector<char> trackStatus_;

	struct TempoChange : Moveable<TempoChange> {
		int count;
		float tickSeconds;
	};
	
	Vector<TempoChange> tempoEvents_;
	Vector<int> trackCounters_;
	Vector<int> trackTempoIndex_;
};

NAMESPACE_AUDIO_END

#endif
