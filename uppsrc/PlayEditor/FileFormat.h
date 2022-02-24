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
	
};

struct PlaySentence : ScriptObject {
	Vector<Token> tokens;
	WString voice_id;
	
	String ToString(int indent=-1) const;
	
};

struct MetaText : ScriptObject {
	Array<PlaySentence> sents;
	
	
	String ToString(String title="", int indent=0) const;
	
};

struct PlayLine : ScriptObject {
	PlayIdentifier id;
	bool is_comment = false;
	bool is_narration = false;
	Array<PlaySentence> sents;
	
	
	String ToString(int indent=0) const;
	
};

struct PlayDialogue : ScriptObject {
	Array<PlayLine> lines;
	
	
	String ToString(String title="", int indent=0) const;
	
};

struct PlaySection : ScriptObject {
	int idx = -1;
	PlaySentence title;
	PlayDialogue dialog;
	
	String ToString(int indent=0) const;
	
};

struct PlayPart : ScriptObject {
	int idx = -1;
	PlaySentence title;
	Array<PlaySection> sections;
	
	
	String ToString(int indent=0) const;
	
};

struct PlayScript : ScriptObject {
	MetaText title;
	MetaText description;
	MetaText author;
	MetaText disclaimer;
	PlayDialogue actors;
	Array<PlayPart> parts;
	
	
	String ToString(int indent=0) const;
	void Dump() const {LOG(ToString());}
	
	
	
};
	
class PlayParser : public ErrorSource {
	const Vector<Token>* tokens = 0;
	int cursor = 0;
	
	PlayScript script;
	
	bool IsPartToken(const Token& t);
	bool IsSectionToken(const Token& t);
	bool CheckEof();
	bool CheckColon();
	
	bool ParseScript(PlayScript& s);
	bool ParseParts(PlayScript& s);
	bool ParseMetaText(MetaText& t);
	bool ParseSentence(PlaySentence& p, bool opt_voice_id);
	bool ParseSentenceEol(PlaySentence& p, bool opt_voice_id);
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
	
	PlayParser();
	
	bool Process(const Vector<Token>& tokens);
	
	const PlayScript& GetResult() const {return script;}
	
};


NAMESPACE_TOPSIDE_END

#endif
