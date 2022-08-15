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

	unsigned int GetNumberOfTracks() const {
		return nTracks_;
	};

	int GetDivision() const {
		return division_;
	};

	void RewindTrack( unsigned int track = 0 );
	double GetTickSeconds( unsigned int track = 0 );
	unsigned long GetNextEvent( Vector<unsigned char>* event, unsigned int track = 0 );
	unsigned long GetNextMidiEvent( Vector<unsigned char>* midiEvent, unsigned int track = 0 );

protected:

	bool GetVariableLength( unsigned long* value );

	FileIn file_;
	unsigned int nTracks_;
	int format_;
	int division_;
	bool usingTimeCode_;
	Vector<double> tickSeconds_;
	Vector<long> trackPointers_;
	Vector<long> trackOffsets_;
	Vector<long> trackLengths_;
	Vector<char> trackStatus_;

	struct TempoChange : Moveable<TempoChange> {
		unsigned long count;
		double tickSeconds;
	};
	
	Vector<TempoChange> tempoEvents_;
	Vector<unsigned long> trackCounters_;
	Vector<unsigned int> trackTempoIndex_;
};

NAMESPACE_AUDIO_END

#endif
