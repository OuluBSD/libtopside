#ifndef _Sequencer_Session_h_
#define _Sequencer_Session_h_

/*

1/64	1
1/32	2
1/16	4
1/8		8
1/4		16
1/2		32
bar		64


*/

#define BARSIZE 64


NAMESPACE_TOPSIDE_BEGIN


enum {
	OP_NULL,
	OP_ADDTRACK,
	OP_REMOVETRACK,
	OP_ADDBLOCK,
	OP_MOVEBLOCK,
	OP_MOVEBLOCKTRACK,
	OP_MOVENOTE,
	OP_ADDNOTE,
	OP_REMNOTE
};

class Op : Moveable<Op> {
	static const int MAXARGS = 10;
	
	Vector<Op> ops;
	int data[MAXARGS];
	String serialized;
	
public:
	Op() {data[0] = 0;}
	Op(const Op& src) {*this = src;}
	
	void operator = (const Op& src) {
		ops <<= src.ops;
		for(int i = 0; i < MAXARGS; i++)
			data[i] = src.data[i];
		serialized = src.serialized;
	}
	
	int GetInt(int pos) const {ASSERT(pos >= 0 && pos < MAXARGS); return data[pos];}
	void SetInt(int pos, int i) {ASSERT(pos >= 0 && pos < MAXARGS); data[pos] = i;}
	void Clear() {data[0] = OP_NULL; ops.Clear();}
	void AddOp(const Op& op) {ops.Add(op);}
	const Op& GetOp(int i) const {return ops[i];}
	int GetOpCount() const {return ops.GetCount();}
	
	template <class T>
	void Load(T& t) const {
		MemStream m((void*)serialized.Begin(), serialized.GetCount());
		m.SetLoading();
		m % t;
	}
	
	template <class T>
	void Store(T& t) {
		StringStream ss;
		ss.SetStoring();
		ss % t;
		serialized = ss;
	}
	
};


class Note : Moveable<Note> {
	int pitch = 0, shift = 0, len = 1;
	byte vel = 255;
	
	
public:
	Note();
	
	void Serialize(Stream& s) {s % pitch % shift % len % vel;}
	
	int GetShift() const {return shift;}
	int GetLength() const {return len;}
	int GetPitch() const {return pitch;}
	int GetVelocity() const {return vel;}
	double GetFrequency() const {return pow(2, (pitch - (4*12+9)) / 12.0) * 440;}
	static double GetFrequencyPitch(int pitch) {return pow(2, (pitch - (4*12+9)) / 12.0) * 440;}
	
	Note& SetShift(int i) {shift = i; return *this;}
	Note& SetLength(int i) {len = i; return *this;}
	Note& SetPitch(int i) {pitch = i; return *this;}
	Note& SetVelocity(int i) {vel = i; return *this;}
	
	
};

class Block : Moveable<Block> {
	Vector<Note> notes;
	int shift = 0;
	int size = BARSIZE;
	
public:
	Block();
	Block(const Block& b) {*this = b;}
	void operator=(const Block& b) {
		notes <<= b.notes;
		shift = b.shift;
		size = b.size;
	}
	void Serialize(Stream& s) {s % notes % shift % size;}
	
	
	Note& AddNote() {return notes.Add();}
	int GetShift() const {return shift;}
	int GetSize() const {return size;}
	int GetNoteCount() const {return notes.GetCount();}
	Note& GetNote(int i) {return notes[i];}
	const Note& GetNote(int i) const {return notes[i];}
	void RemoveNote(int i) {notes.Remove(i);}
	void PopNote() {notes.Pop();}
	Note& InsertNote(int i) {return notes.Insert(i);}
	
	Block& SetShift(int i) {shift = i; return *this;}
	Block& SetSize(int i) {size = i; return *this;}
	
	
	
	
};

class Track {
	Vector<Block> blocks;
	String title;
	CoreParams input;
	VectorMap<int, CoreParams> fx;
	
public:
	Track();
	
	
	String GetTitle() const {return title;}
	int GetBlockCount() const {return blocks.GetCount();}
	Block& GetBlock(int i);
	const Block& GetBlock(int i) const {return blocks[i];}
	const CoreParams& GetInput() const {return input;}
	const CoreParams& GetFx(int i) const {return fx[i];}
	int GetFxKey(int i) const {return fx.GetKey(i);}
	int GetFxCount() const {return fx.GetCount();}
	
	Block& AddBlock() {return blocks.Add();}
	void PopBlock() {blocks.Pop();}
	void SetTitle(String s) {title = s;}
	CoreParams& SetInput() {return input;}
	CoreParams& SetEffect(int i) {return fx.GetAdd(i);}
	void PickBlock(Track& t, int block) {blocks.Add(t.GetBlock(block)); t.RemoveBlock(block);}
	void RemoveBlock(int block) {blocks.Remove(block);}
	
	void Serialize(Stream& s) {s % blocks % title % input;}
	
};

enum {NOTE_ON, NOTE_OFF};

struct PlayEvent : Moveable<PlayEvent> {
	int time, type, track;
	double freq, ampl;
	
	bool operator()(const PlayEvent& a, const PlayEvent& b) const {
		if (a.time < b.time)	return true;
		if (a.time > b.time)	return false;
		if (a.type > b.type)	return true;
		if (a.type < b.type)	return false;
		return a.track < b.track;
	}
};

class Session {
	
	typedef Tuple<int, double> CloseNote;
	
	
	Array<Track> tracks;
	int tempo = 120;
	
	Vector<CloseNote> close_notes;
	Vector<Op> undo_history, redo_history;
	System sys;
	Op group_op;
	int time_cursor = 0, play_cursor = 0;
	bool is_group_op = false;
	bool playing = false, stopped = true;
	
	void Undo(const Op& op);
	void Redo(const Op& op);
	void Play();
	
public:
	typedef Session CLASSNAME;
	Session();
	~Session() {Stop();}
	
	void Do(const Op& op);
	void DoBegin();
	void DoEnd();
	void Undo();
	void Redo();
	void Data();
	void Start() {Stop(); playing = true; stopped = false; Thread::Start(THISBACK(Play));}
	void Stop() {playing = false; while (!stopped) Sleep(100); CloseNotes();}
	void Seek(int time) {time_cursor = time; play_cursor = 0; WhenTimeChanges();}
	void CloseNotes();
	void MidiIn(int note, int vel);
	
	bool IsPlaying() {return playing;}
	
	
	Track& AddTrack() {return tracks.Add();}
	Track& GetTrack(int i);
	int GetTrackCount() const {return tracks.GetCount();}
	const Vector<Op>& GetUndoHistory() const {return undo_history;}
	const Vector<Op>& GetRedoHistory() const {return redo_history;}
	int GetTimeCursor() const {return time_cursor;}
	int GetTempo() const {return tempo;}
	System& GetSystem() {return sys;}
	int GetTimeFromShift(int shift) const;
	
	void GetEvents(Vector<PlayEvent>& events) const;
	
	Callback WhenAction, WhenTimeChanges;
};


NAMESPACE_TOPSIDE_END

#endif
