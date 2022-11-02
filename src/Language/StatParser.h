#ifndef _Language_StatParser_h_
#define _Language_StatParser_h_

#include <plugin/pcre/Pcre.h>

NAMESPACE_LANGUAGE_BEGIN

struct Backpointer : Moveable<Backpointer> {
	byte len = 0;
	WString X, Y, Z;
	int i, s, j;
	
	Backpointer() {}
	Backpointer(const Backpointer& bp) {*this = bp;}
	void operator=(const Backpointer& bp) {
		len = bp.len;
		X = bp.X;
		Y = bp.Y;
		Z = bp.Z;
		i = bp.i;
		s = bp.s;
		j = bp.j;
	}
	
	void Set(WString X, WString Y, int i, int j) {
		this->X = X;
		this->Y = Y;
		this->i = i;
		this->j = j;
		len = 4;
	}
};

struct NormWord : Moveable<NormWord> {
	WString word_;
	WString norm;
	
	void Serialize(Stream& s) {s % word_ % norm;}
	unsigned GetHashValue() const {return CombineHash().Do(word_).Do(norm);}
	bool operator==(const NormWord& b) const {return word_==b.word_ && norm==b.norm;}
};

struct XY2 : Moveable<XY2> {
	WString x, y1, y2;
	
	XY2() {}
	XY2(WString X, WString Y1, WString Y2) {x=X; y1=Y1; y2=Y2;}
	void Serialize(Stream& s) {s % x % y1 % y2;}
	unsigned GetHashValue() const {return CombineHash().Do(x).Do(y1).Do(y2);}
	bool operator==(const XY2& b) const {return x==b.x && y1==b.y1 && y2==b.y2;}
};

struct Y2 : Moveable<Y2> {
	WString y1, y2;
	
	unsigned GetHashValue() const {return CombineHash().Do(y1).Do(y2);}
	bool operator==(const Y2& b) const {return y1==b.y1 && y2==b.y2;}
};

class PennTreebankTokenizer : public Lexer {
	
	void Cat(int chr) {tokens.Top().str_value.Cat(chr);}
	Token& NewSingle(WString ws) {
		if (tokens.GetCount() && tokens.Top().str_value.IsEmpty()) {
			tokens.Top().str_value = ws; tokens.Add(); return tokens[tokens.GetCount()-2];
		} else {
			tokens.Add().str_value = ws; tokens.Add(); return tokens[tokens.GetCount()-2];
		}
	}
public:
	PennTreebankTokenizer();
	
	virtual bool Tokenize(WString txt);
	virtual String GetTypeString(int type) {return "text";}
};

class PCFG {
	
protected:
	friend Node* CKY(PCFG& pcfg, Vector<NormWord>& norm_words);
	
	static const int RARE_WORD_COUNT = 5;
	
	VectorMap<WString, VectorMap<WString, int> > word_type_count;
	VectorMap<WString, int> sym_count;
	VectorMap<WString, int> words_count;
	VectorMap<NormWord, int> unary_count;
	VectorMap<XY2, int> binary_count;
	
	Index<WString> N;
	
	VectorMap<WString, Vector<Y2> > binary_rules;
	
public:
	VectorMap<NormWord, double> q1;
	VectorMap<XY2, double> q2;
	Index<WString> well_known_words;
	
	PCFG();
	
	WString GetNormWord(WString word_);
	void BuildCaches();
	void LearnFromTreebanks(Vector<String>& treebanks);
	void Count(Node& tree);
	void SaveModel(String path);
	void LoadModel(String path);
	
	bool IsEmpty();
	
	WString WordClass(WString word_);
	
};


bool IsEnding(const char* end, int end_len, const WString& w);

Node* GetBacktrace(Backpointer& back, DictMap<int, int, WString, Backpointer>& bp);

Node* CKY(PCFG& pcfg, Vector<NormWord>& norm_words);

class StatParser {
	PCFG pcfg;
	PennTreebankTokenizer tokenizer;
	
	
public:
	StatParser();
	
	void LoadModel();
	void NormParse(WString sentence);
	bool Parse(WString sentence);
	
	void Dump();
	
	One<Node> root;
};

void BuildModel(PCFG& pcfg);

void GetWords(Node& n, Vector<String>& words);
WString GetSentence(Node& n, int& words);
inline WString GetSentence(Node& n) {int words = 0; return GetSentence(n, words);}

void ChomskyNormalForm(Node& n);
void UnChomskyNormalForm(Node& n);
bool IsNullElementsFilter(Node& n);

struct UncertainParsing {};

void PruneNullElements(Node& tree, VectorMap<Node*, Node*>& parents);
void GenerateNormal(String path, const Vector<String>& input_treebanks);

struct Tags {
	VectorMap<WString, WString> tags;
	
	Tags();
};

inline Tags& GetTags() {return Single<Tags>();}

WString NormalizeTag(WString tag);
WString NormalizeWord(WString word_);

void ParseNode(const WString& input, int& cursor, Node& node, WString& text);
void ParseTreebank(String file_path, Node& tb);
void NormalizeQuestionbank(String in_path, String out_path);

bool IsCapWord(const WString& word_);
bool IsNumberStr(const WString& word_);
bool HasNoneTag(Node& n);



void StatParseEnglish(String text, Node& n);


NAMESPACE_LANGUAGE_END
        
#endif
