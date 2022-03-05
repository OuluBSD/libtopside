#ifndef _PlayEditor_FileFormat_h_
#define _PlayEditor_FileFormat_h_

NAMESPACE_TOPSIDE_BEGIN


class PlayTokenizer : public ErrorSource {
	WString input;
	FileLocation loc;
	int tab_size = 4;
	
	enum {
		ANY,
		WORD,
		STRING
	};
	int state = ANY;
	
protected:
	
	Vector<Token> tokens;
	
	void Next() {loc.col++; loc.cursor++;}
	Token& Add(int token_id);
	
	
public:
	typedef PlayTokenizer CLASSNAME;
	
	PlayTokenizer();
	
	bool Process(String content, String path);
	
	void Dump() const;
	
	const Vector<Token>& GetTokens() const {return tokens;}
	FileLocation GetLocation() const {return loc;}
	
};


struct ScriptObject {
	
	
	
};

struct PlayIdentifier : ScriptObject {
	WString name;
	
	
	String ToString() const;
	String ToScript() const;
	
};

struct PlaySentence : ScriptObject {
	Vector<Token> tokens;
	WString voice_id;
	
	int tmp_time = -1;
	int tmp_duration = 0;
	
	PlaySentence() {}
	PlaySentence(const PlaySentence& ps) {tokens <<= ps.tokens; voice_id = ps.voice_id;}
	
	PlaySentence& Set(String txt);
	String ToString(int indent=-1) const;
	String ToScript() const;
	Value GetData() const;
	
};

struct MetaText : ScriptObject {
	Array<PlaySentence> sents;
	
	
	void Clear() {sents.Clear();}
	String ToString(String title="", int indent=0) const;
	String ToScript() const;
	Value GetData() const;
	
};

struct PlayLine : ScriptObject {
	PlayIdentifier id;
	bool is_comment = false;
	bool is_narration = false;
	bool is_meta = false;
	Array<PlaySentence> sents;
	
	
	String ToString(int indent=0) const;
	String ToScript() const;
	String GetId() const;
};

struct PlayDialogue : ScriptObject {
	Array<PlayLine> lines;
	
	
	String ToString(String title="", int indent=0) const;
	String ToScript() const;
	int GetFirstTime() const;
	int GetFirstActorTime() const;
	
};

struct PlaySection : ScriptObject {
	int idx = -1;
	int musical_idx = -1;
	int notes_min = -1;
	int notes_max = -1;
	int notes_idx_digits = -1;
	int musical_time = -1;
	double musical_fps = 0;
	String musical_dir;
	PlaySentence title;
	PlayDialogue dialog;
	
	String ToString(int indent=0) const;
	String ToScript() const;
	
};

struct PlayPart : ScriptObject {
	int idx = -1;
	PlaySentence title;
	Array<PlaySection> sections;
	
	
	String ToString(int indent=0) const;
	String ToScript() const;
	
};

struct PlayScript : ScriptObject {
	MetaText title;
	MetaText description;
	MetaText author;
	MetaText disclaimer;
	PlayDialogue actors;
	Array<PlayPart> parts;
	
	
	struct Subtitle {
		PlayLine* line = 0;
		PlaySentence* sent = 0;
		int part_i = -1;
		WString str;
		int time = -1;
		Color clr;
		
		String ToString() const;
	};
	
	struct Actor {
		PlayLine* line = 0;
		Color normal_paper;
		String name;
		int idx = -1;
		
	};
	
	struct NoteData : Moveable<NoteData> {
		int time = -1;
		double fps = 0;
		
		void Set(int t, double f) {time = t; fps = f;}
	};
	
	Array<Subtitle> subtitles;
	ArrayMap<String, Actor> tmp_actors;
	PlayLine beginning, ending;
	PlayLine intro_line;
	String filepath;
	Image logo, subscribe, author_img;
	
	
	VectorMap<unsigned, int> input_ext_time;
	VectorMap<int, VectorMap<int,NoteData>> input_ext_notes;
	Index<unsigned> used_hashes;
	
	String ToString(int indent=0) const;
	String ToScript() const;
	String GetSubtitleExtensionScript() const;
	String GetNotesExtensionScript() const;
	void Dump() const {LOG(ToString());}
	
	void LoadExtension(String s);
	void MakeSubtitles();
	void MakeActors();
	bool CheckReferences();
	void AddSubtitle(PlayLine& line, PlaySentence& sent);
	void MakeTempPlaySentenceTimes();
	void LoadImages();
	bool CheckMusical();
	
	const Actor& GetActor(const PlayLine& line) const;
	int FindSubtitle(int time) const;
	const Subtitle& Get(int i) const;
	int GetSubtitleCount() const {return subtitles.GetCount();}
	int GetLastSubtitleTiming() const;
	int GetTotalTime() const;
	const PlaySection* FindSection(int time, bool musical) const;
	
};
	
class PlayParser : public ErrorSource {
	const Vector<Token>* tokens = 0;
	int cursor = 0;
	PlayScript& script;
	
	
	bool IsPartToken(const Token& t);
	bool IsSectionToken(const Token& t);
	bool CheckEof();
	bool CheckEol();
	bool CheckColon();
	
	bool ParseScript(PlayScript& s);
	bool ParseParts(PlayScript& s);
	bool ParseMetaText(MetaText& t);
	bool ParseSentence(PlaySentence& p, bool opt_voice_id);
	bool ParseSentenceEol(PlaySentence& p, bool opt_voice_id);
	bool ParseTiming(PlayLine& p);
	bool ParsePlayDialogue(PlayDialogue& p);
	bool ParsePlayLine(PlayLine& l);
	bool ParsePart(PlayPart& p);
	bool ParseSection(PlaySection& s);
	void PassEmpty();
	
	const Token& Current() {return (*tokens)[cursor];}
	const Token* GetNext() {return cursor+1 < tokens->GetCount() ? &(*tokens)[cursor+1] : 0;}
	void Next() {cursor++;}
	bool IsEof() const {return !tokens || cursor >= tokens->GetCount() || (*tokens)[cursor].IsType(TK_EOF);}
	
public:
	typedef PlayParser CLASSNAME;
	
	PlayParser(PlayScript& script);
	
	bool Process(const Vector<Token>& tokens);
	
	const PlayScript& GetResult() const {return script;}
	
};


NAMESPACE_TOPSIDE_END

#endif
