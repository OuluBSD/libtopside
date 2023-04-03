#ifndef _MIDIFILE_H_INCLUDED
#define _MIDIFILE_H_INCLUDED


NAMESPACE_MIDI_BEGIN


#define TIME_STATE_DELTA       0
#define TIME_STATE_ABSOLUTE    1

#define TRACK_STATE_SPLIT      0
#define TRACK_STATE_JOINED     1

class TickTime : Moveable<TickTime> {

public:
	int    tick;
	float seconds;
};


class File {
	String last_error;
	
public:
	File();
	File(String file);
	File(Stream& input);
	File(const File& other);
	File(File && other);
	~File();
	
	bool      Open(String file);
	String    GetLastError() const {return last_error;}
	
	// reading/writing functions:
	int       Read(String file);
	int       Read(Stream& istream);
	int       Write(String file);
	int       Write(Stream& out);
	int       WriteHex(String file, int width = 25);
	int       WriteHex(Stream& out,        int width = 25);
	int       WriteBinasc(String file);
	int       WriteBinasc(Stream& out);
	int       WriteBinascWithComments(String file);
	int       WriteBinascWithComments(Stream& out);
	int       GetStatus();
	
	// track-related functions:
	EventList& operator[](int track);
	const EventList& operator[](int track) const;
	int       GetTrackCount() const;
	
	// join/split track functionality:
	void      MarkSequence();
	void      ClearSequence();
	void      JoinTracks();
	void      SplitTracks();
	void      SplitTracksByChannel();
	int       GetTrackState();
	int       HasJoinedTracks();
	int       HasSplitTracks();
	int       GetSplitTrack(int track, int index);
	int       GetSplitTrack(int index);
	
	void      SortTrack(EventList& track_data);
	void      SortTracks();
	
	int       AddTrack();
	int       AddTrack(int count);
	int       AddTracks(int count) {return AddTrack(count);}
	
	void      DeleteTrack(int track);
	void      MergeTracks(int track1, int track2);
	int       GetTrackCountAsType1();
	
	int       GetEventCount(int track);
	void      AllocateEvents(int track, int size);
	
	// tick-related functions:
	void      DeltaTicks();
	void      AbsoluteTicks();
	int       GetTickState();
	int       IsDeltaTicks();
	int       IsAbsoluteTicks();
	
	// ticks-per-quarter related functions:
	void      SetMillisecondTicks();
	int       GetTicksPerQuarterNote();
	int       GetTPQ();
	void      SetTicksPerQuarterNote(int ticks);
	void      SetTPQ(int ticks);
	
	// physical-time analysis functions:
	void      DoTimeAnalysis();
	float    GetTimeInSeconds(int track, int index);
	float    GetTimeInSeconds(int tickvalue);
	int       GetAbsoluteTickTime(float starttime);
	
	float    GetTotalTimeInSeconds();
	int       GetTotalTimeInTicks();
	float    GetTotalTimeInQuarters();
	
	// note-analysis functions:
	int       LinkNotePairs();
	int       LinkEventPairs();
	void      ClearLinks();
	
	// filename functions:
	void      SetFilename(String aname);
	String GetFilename();
	
	int       AddEvent(int track, int tick, Vector<uint8>& midiData);
	int       AddEvent(Event& mfevent);
	
	// MIDI message adding convenience functions:
	int       AddNoteOn(int track, int tick, int channel, int key, int vel);
	int       AddNoteOff(int track, int tick, int channel, int key, int vel);
	int       AddNoteOff(int track, int tick, int channel, int key);
	int       AddController(int track, int tick, int channel, int num, int value);
	int       AddPatchChange(int track, int tick, int channel, int patchnum);
	int       AddTimbre(int track, int tick, int channel, int patchnum);
	int       AddPitchBend(int track, int tick, int channel, float amount);
	        
	// Meta-event adding convenience functions:
	int       AddMetaEvent(int track, int tick, int type, Vector<uint8>& meta_data);
	int       AddMetaEvent(int track, int tick, int type, String meta_data);
	int       AddCopyright(int track, int tick, String text);
	int       AddTrackName(int track, int tick, String name);
	int       AddInstrumentName(int track, int tick, String name);
	int       AddLyric(int track, int tick, String text);
	int       AddMarker(int track, int tick, String text);
	int       AddCue(int track, int tick, String text);
	int       AddTempo(int track, int tick, float aTempo);
	int       AddTimeSignature(int track, int tick, int top, int bottom, int clocks_per_click = 24, int num32dsPerQuarter = 8);
	int       AddCompoundTimeSignature(int track, int tick, int top, int bottom, int clocks_per_click = 36, int num32dsPerQuarter = 8);
	        
	void      Clear();
	void      ClearNoDeallocate();
	Event&  GetEvent(int track, int index);
	
	File& operator=(const File& other);
	
	// static functions:
	static uint8   ReadByte(Stream& input);
	static uint16  ReadLittleEndian2Bytes(Stream& input);
	static uint32  ReadLittleEndian4Bytes(Stream& input);
	static Stream& WriteLittleEndianUShort(Stream& out, uint16 value);
	static Stream& WriteBigEndianUShort(Stream& out, uint16 value);
	static Stream& WriteLittleEndianShort(Stream& out, short  value);
	static Stream& WriteBigEndianShort(Stream& out, short  value);
	static Stream& WriteLittleEndianULong(Stream& out, uint32  value);
	static Stream& WriteBigEndianULong(Stream& out, uint32  value);
	static Stream& WriteLittleEndianLong(Stream& out, long   value);
	static Stream& WriteBigEndianLong(Stream& out, long   value);
	static Stream& WriteLittleEndianFloat(Stream& out, float  value);
	static Stream& WriteBigEndianFloat(Stream& out, float  value);
	static Stream& WriteLittleEndianDouble(Stream& out, float value);
	static Stream& WriteBigEndianDouble(Stream& out, float value);
	
protected:
	Array<EventList>      events;                     // MIDI file events
	int                   ticks_per_quarter_note;     // time base of file
	int                   track_count;                // # of tracks in file
	int                   the_track_state;            // joined or split
	int                   the_time_state;             // absolute or delta
	String                read_file_name;             // read file name
	int                   timemapvalid;
	Vector<TickTime>      timemap;
	int                   rwstatus;                   // read/write success flag
	
private:
	int        ExtractData(Stream& inputfile, Vector<uint8>& array, uint8& runningCommand);
	uint32     ReadVLValue(Stream& inputfile);
	uint32     UnpackVLV(uint8 a = 0, uint8 b = 0, uint8 c = 0, uint8 d = 0);
	void       WriteVLValue(long value, Vector<uint8>& data);
	int        MakeVLV(uint8 *buffer, int number);
	static int TickSearch(const void* A, const void* B);
	static int SecondSearch(const void* A, const void* B);
	void       BuildTimeMap();
	int        LinearTickInterpolationAtSecond(float seconds);
	float     LinearSecondInterpolationAtTick(int ticktime);
};



//////////////////////////////
//
// eventcompare -- Event comparison function for sorting tracks.
//
// Sorting rules:
//    (1) sort by (absolute) tick value; otherwise, if tick values are the same:
//    (2) end-of-track meta message is always last.
//    (3) other meta-messages come before regular MIDI messages.
//    (4) note-offs come after all other regular MIDI messages except note-ons.
//    (5) note-ons come after all other regular MIDI messages.
//

struct EventCompare {
	bool operator()(const Event& aevent, const Event& bevent) const {
		
		if (aevent.tick > bevent.tick) {
			// aevent occurs after bevent
			return false;
		}
		
		else if (aevent.tick < bevent.tick) {
			// aevent occurs before bevent
			return true;
		}
		
		else if (aevent.seq > bevent.seq) {
			// aevent sequencing state occurs after bevent
			// see File::MarkSequence()
			return false;
		}
		
		else if (aevent.seq < bevent.seq) {
			// aevent sequencing state occurs before bevent
			// see File::MarkSequence()
			return true;
		}
		
		else if (aevent[0] == 0xff && aevent[1] == 0x2f) {
			// end-of-track meta-message should always be last (but won't really
			// matter since the writing function ignores all end-of-track messages
			// and writes its own.
			return false;
		}
		
		else if (bevent[0] == 0xff && bevent[1] == 0x2f) {
			// end-of-track meta-message should always be last (but won't really
			// matter since the writing function ignores all end-of-track messages
			// and writes its own.
			return true;
		}
		
		else if (aevent[0] == 0xff && bevent[0] != 0xff) {
			// other meta-messages are placed before real MIDI messages
			return true;
		}
		
		else if (aevent[0] != 0xff && bevent[0] == 0xff) {
			// other meta-messages are placed before real MIDI messages
			return false;
		}
		
		else if (((aevent[0] & 0xf0) == 0x90) && (aevent[2] != 0)) {
			// note-ons come after all other types of MIDI messages
			return false;
		}
		
		else if (((bevent[0] & 0xf0) == 0x90) && (bevent[2] != 0)) {
			// note-ons come after all other types of MIDI messages
			return true;
		}
		
		else if (((aevent[0] & 0xf0) == 0x90) || ((aevent[0] & 0xf0) == 0x80)) {
			// note-offs come after all other MIDI messages (except note-ons)
			return false;
		}
		
		else if (((bevent[0] & 0xf0) == 0x90) || ((bevent[0] & 0xf0) == 0x80)) {
			// note-offs come after all other MIDI messages (except note-ons)
			return true;
		}
		
		else {
			return 0;
		}
	}
};

Stream& operator<<(Stream& out, File& aFile);

NAMESPACE_MIDI_END

#endif
