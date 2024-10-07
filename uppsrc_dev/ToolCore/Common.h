#ifndef _TopTool_Common_h_
#define _TopTool_Common_h_


BEGIN_TEXTLIB_NAMESPACE


#define TODO Panic("TODO");
#define MOVED Panic("MOVED");



enum {
	SCORE_IDEA,
	SCORE_EMOTION,
	SCORE_HOOK,
	SCORE_SHARE,
	SCORE_VALUE,
	SCORE_COMEDY,
	SCORE_SEX,
	SCORE_POLITICS,
	SCORE_LOVE,
	SCORE_SOCIAL,
	
	SCORE_COUNT
};


extern const char* ScoreTitles[SCORE_COUNT];
extern const char* ScoreDescriptions[SCORE_COUNT];
String GetScoreKey(int score);
String GetScoreTitle(int score);
String GetScoreDescription(int score);

enum {
	RHYME_A_A,
	RHYME_AB_AB,
	RHYME_AAC_BBC,
	//RHYME_A_AB,
	
	RHYME_A_A_A,
	RHYME_AB_AB_AB_,
	RHYME_AAD_BBC_CCD,
	
	RHYME_A_A_A_A,
	RHYME_A_B_A_B,
	RHYME_A_C_B_C,
	RHYME_AA_C_BB_C,
	
	RHYME_COUNT
};

extern const char* RhymeSchemes[RHYME_COUNT][3];
extern const int RhymeSchemeLineCount[RHYME_COUNT];

int FindRhymeType(const char* name);

void PutKeyColor(const char* key, int ir, int ig, int ib, double& r, double& g, double& b, double& sr, double& sg, double& sb);






// These are sorted using AI (14.10.2023). The first one is the popular option

#define ATTR_LIST \
	ATTR_ITEM(FAITH_AND_REASON_SEEKER, "faith and reason seekers", "divine worshipers", "rational thinker") \
	ATTR_ITEM(GROUP_FAITH, "group faith", "individual spirituality", "organized religion") \
	ATTR_ITEM(BELIF_SPECTRUM, "belief spectrum", "believer", "non-believer") \
	ATTR_ITEM(OLD_AND_NEW_BELIEVER, "old and new believers", "new age spirituality", "traditional religion") \
	ATTR_ITEM(BELIF_COMMUNITY, "belief communities", "secular society", "religious community") \
	ATTR_ITEM(THEOLOGICAL_OPPOSITE, "theological opposites", "theistic", "atheistic") \
	ATTR_ITEM(SEEKER_OF_TRUTH, "seekers of truth", "spiritual seeker", "skeptic") \
	ATTR_ITEM(INTUITIVE_THINKER, "intuitive thinkers", "rationalist", "mystic practitioner") \
	ATTR_ITEM(RATIONAL_BELIEF, "rational believers", "religious", "scientific") \
	ATTR_ITEM(PHYSICAL_PREFERENCE, "physical preference", "body enhancing beauty", "natural beauty") \
	ATTR_ITEM(SEXUAL_ORIENTATION, "sexual orientation", "heterosexual", "homosexual") \
	ATTR_ITEM(SEXUAL_PREFERENCE, "sexual preference", "normal", "kinky") \
	ATTR_ITEM(FAITH_EXTREME, "faith extremes", "agnostic", "religious fundamentalist") \
	\
	ATTR_ITEM(AVERAGE_EXPECTATIONS, "average expectations", "expectation-conformed", "expectation-opposed") \
	ATTR_ITEM(IMAGERY, "imagery", "trope-reinforcing", "unique") \
	ATTR_ITEM(EXPRESSION, "expression", "explicit", "allegorical") \
	ATTR_ITEM(RELATIONSHIP, "relationship", "romantic couple", "without romantic partner" ) \
	ATTR_ITEM(RELATIONSHIP_FOCUS, "relationship focus", "partner-focused", "individual-focused") \
	ATTR_ITEM(HUMAN_STRENGTH, "human strength", "strong", "weak") \
	ATTR_ITEM(GENDER, "gender", "female", "male") \
	ATTR_ITEM(RATIONALITY, "rationality", "unreasonable", "reasonable") \
	ATTR_ITEM(INTEGRITY, "integrity", "twisted", "honest") \
	ATTR_ITEM(SEXUALIZATION, "sexualization", "sexual", "non-sexual") \
	ATTR_ITEM(EXPECTATIONS, "expectations", "perfection", "acceptance") \
	ATTR_ITEM(PROBLEM_SOLVING, "problem solving strategy", "shortcut taking", "cunning") \
	ATTR_ITEM(RESPONSIBILITY, "responsibility", "irresponsible", "accountable") \
	ATTR_ITEM(SOCIAL, "social", "authoritarian", "libertarian") \
	ATTR_ITEM(ECONOMIC, "economic", "liberal", "conservative") \
	ATTR_ITEM(CULTURE, "culture", "individualistic", "collective") \
	ATTR_ITEM(GROUP_EXPERIENCE, "group experience", "group-oriented", "individual-oriented") \
	ATTR_ITEM(MOTIVATION, "motivation", "rewarding", "punishing") \
	ATTR_ITEM(LOVE_STATUS, "love status", "loving now", "heartbreak") \
	ATTR_ITEM(SITUATION_RELATION, "situation relation", "prescriptive", "descriptive") \
	ATTR_ITEM(COMPETITIVENESS, "competitiveness", "competition", "collaboration") \
	ATTR_ITEM(OTHER_RELATION, "relation to others", "comparison", "self-acceptance") \
	ATTR_ITEM(INTELLIGENCE, "intelligence", "emotional", "intellectual") \
	ATTR_ITEM(SOPHISTICATION, "sophistication", "sophisticated", "simple") \
	ATTR_ITEM(TRANSPARENCY, "transparency", "transparent", "mysterious") \
	\
	ATTR_ITEM(STORYMODE, "storymode", "storytelling", "simple themes") \
	ATTR_ITEM(TRUTHFULNESS, "truthfulness", "personal experience", "fictional") \
	ATTR_ITEM(MINDFULNESS, "mindfulness", "mindless", "mindful") \
	ATTR_ITEM(PEACEFULNESS, "peacefulness", "peacemaker", "troublemaker") \
	ATTR_ITEM(NARRATIVE, "narrative", "protagonist storytelling", "narrative detachment") \
	ATTR_ITEM(LYRICAL_EMPHASIS, "lyrical emphasis", "witty wordplay", "straightforward scripts") \
	ATTR_ITEM(EMOTIONALITY, "lyrical emphasis", "emotionally charged", "emotionally restrained") \
	ATTR_ITEM(CONCEPTS, "concepts", "grounded", "psychedelic") \
	ATTR_ITEM(STORY_MOTIVATION, "story-motivation",  "narrative-driven", "mood-driven") \
	ATTR_ITEM(REALITY, "reality", "escapism", "realism") \
	ATTR_ITEM(PROVOCATIVITY, "provocativity", "edgy", "innocent") \
	ATTR_ITEM(INSPIRATION_SOURCE, "source of inspiration", "nostalgic", "relevant to current times") \
	ATTR_ITEM(PRODUCTION_STYLE, "production style", "acoustic", "electronic") \
	ATTR_ITEM(LIFE_AND_LOVE, "life and love", "aspirational", "relatable") \
	ATTR_ITEM(AUDIENCE, "audience", "mainstream", "alternative") \
	ATTR_ITEM(AUTHENCITY, "authencity", "social media-driven", "authentic") \
	ATTR_ITEM(PATIENCE, "patience", "instant gratification", "longevity") \
	ATTR_ITEM(LOVE_TARGET, "target of love", "romantic love", "self-love") \
	ATTR_ITEM(AGE_TARGET, "age target", "youth-oriented", "age-inclusive") \
	ATTR_ITEM(INDEPENDENCE, "independence", "independence", "dependence") \
	ATTR_ITEM(COMMERCIAL_APPEAL, "commercial appeal", "mainstream success", "artistic integrity") \
	ATTR_ITEM(CULTURAL_ELEMENTS, "cultural elements", "globalization", "cultural preservation") \
	ATTR_ITEM(CORPORATION_RELATIONS, "corporation relations", "consumerism", "anti-capitalism") \
	ATTR_ITEM(CELEBRITY_PERSONA, "celebrity Persona", "celebrity worship", "body positivity") \
	ATTR_ITEM(EMOTIONAL_REALISM, "emotional realism",  "happiness", "realistic emotions") \
	ATTR_ITEM(PARTY_RELATION, "party relation", "party anthems", "introspective ballads") \
	ATTR_ITEM(ATTITUDE_ATTITUDE_OPEN_CLOSED, "attitude 1", "open", "closed") \
	ATTR_ITEM(ATTITUDE_HOPEFUL_DESPAIR, "attitude 2", "hopeful", "despair") \
	ATTR_ITEM(ATTITUDE_OPTIMISTIC_PESSIMISTIC, "attitude 3", "optimistic", "pessimistic") \
	ATTR_ITEM(SEXUALITY, "sexuality", "adventurous", "limited") \
	ATTR_ITEM(SEXUAL_ACTING, "sexual acting", "confident", "sensitive") \
	ATTR_ITEM(SEXUAL_COMMITMENT, "sexual commitment", "monogamy", "polygamy") \
	ATTR_ITEM(MOOD_JOYFUL_MELANCHOLIC, "mood 1", "joyful", "melancholic") \
	ATTR_ITEM(MOOD_LIGHTHEARTED_SOMBER, "mood 2", "lighthearted", "somber") \
	ATTR_ITEM(MOOD_UPLIFTING_HEAVY, "mood 3", "uplifting", "heavy") \
	ATTR_ITEM(MOOD_HUMOROUS_DRAMATIC, "mood 4", "humorous", "dramatic") \
	ATTR_ITEM(MOOD_PLAYFUL_SERIOUS, "mood 5", "playful", "serious") \
	

namespace Attr {

enum {
#define ATTR_ITEM(e, g, i0, i1) e,
ATTR_LIST
#undef ATTR_ITEM
ATTR_COUNT
};

extern const char* AttrKeys[ATTR_COUNT+1][4];

int FindAttrGroup(const char* group);
int FindAttrGroupByValue(const char* value);
bool FindAttrValue(int group_i, const char* value);

}

String GetAttrNotString(String positive_attr);


struct Pipe;


struct DataFile {
	String file_title;
	
	bool operator()(const DataFile& a, const DataFile& b) const {
		return a.file_title < b.file_title;
	}
};


struct TaskMgr;


struct Owner;
struct Profile;
struct Entity;
struct Snapshot;
struct Component;
struct Script;
class ToolEditor;
class LeadsCtrl;




	

struct EditorPtrs {
	TextLib::Entity*		entity = 0;
	TextLib::Snapshot*		release = 0;
	TextLib::Component*		component = 0;
	TextLib::Script*		script = 0;
	TextLib::ToolEditor*	editor = 0;
	int pkg_cursor= 0;
	int node_cursor= 0;
	
	void Zero() {memset(this, 0, sizeof(EditorPtrs));}
	
	bool HasComponent() const {return component;}
	
	int GetActiveScriptIndex() const;
	
	int GetActiveEntityIndex() const;
	int GetActiveSnapshotIndex() const;
	int GetActiveComponentIndex() const;
	
	TextDatabase& GetDatabase() const;
	
};





struct MetaPtrs {
	EditorPtrs db;
	Owner*					owner = 0;
	Profile*				profile = 0;
	LeadsCtrl*				leads = 0;
	
	MetaPtrs();
	static MetaPtrs& Single() {static MetaPtrs e; return e;}
	
	int GetOwnerIndex() const;
	int GetProfileIndex() const;
	
};


Color GetPartColor(const String& name, Color def=Color(56,170,255));
int CountWords(const String& s);

String FixInvalidChars(const String& s);
void RemoveLineNumber(String& s);
void RemoveLineChar(String& s);
void RemoveEmptyLines(String& s);
void RemoveEmptyLines2(String& s);
void RemoveEmptyLines3(String& s);
void RemoveColonTrail(String& s);
void RemoveCommentTrail(String& s);

template <class T>
void CalculateWeightedGenderDifference(Vector<double>& values, const Vector<T>& score, const Vector<T>& other_score);




#define IMMEDIATE_TYPES_EQUAL(T) bool operator==(const T& t) const {return MemoryCompare(this, &t, sizeof(T)) == 0;}

struct FileLocation : Moveable<FileLocation> {
	String file;
	int cursor = -1;
	int line = -1;
	int col = -1;
	
	bool operator==(const FileLocation& t) const {
		return	file == t.file &&
				cursor == t.cursor &&
				line == t.line &&
				col == t.col;
	}
	void Clear() {file.Clear(); cursor = -1; line = -1; col = -1;}
	void SetFileLocation(const FileLocation& loc) {*this = loc;}
	void operator=(const FileLocation& loc) {
		file = loc.file;
		cursor = loc.cursor;
		line = loc.line;
		col = loc.col;
	}
	void Serialize(Stream& s) {s % file % cursor % line % col;}
	bool operator<(const FileLocation& l) const {
		if (file != l.file) return file < l.file;
		if (line != l.line) return line < l.line;
		return col < l.col;
	}
	bool operator>(const FileLocation& l) const {
		if (file != l.file) return file > l.file;
		if (line != l.line) return line > l.line;
		return col > l.col;
	}
	bool operator()(const FileLocation& a, const FileLocation& b) const {
		if (a.line != b.line) return a.line < b.line;
		return a.col < b.col;
	}
	String ToString() const {return file + ":" + IntStr(line) + ":" + IntStr(col);}
	
};


enum { PROCMSG_UNKNOWN, PROCMSG_SKIP, PROCMSG_INFO, PROCMSG_WARNING, PROCMSG_ERROR };

struct ProcMsg : Moveable<ProcMsg>, public FileLocation {
	int severity = 0;
	String src;
	String msg;
	String parts[3];

	ProcMsg() {}
	ProcMsg(const ProcMsg& e) { *this = e; }
	ProcMsg(String source, FileLocation loc, int severity, String msg) {
		this->src = source;
		SetFileLocation(loc);
		this->severity = severity;
		this->msg = msg;
	}
	
	bool operator==(const ProcMsg& t) const {
		return	severity == t.severity &&
				src == t.src &&
				msg == t.msg &&
				parts[0] == t.parts[0] &&
				parts[1] == t.parts[1] &&
				parts[2] == t.parts[2] &&
				FileLocation::operator==(t);
	}
	
	void operator=(const ProcMsg& e) {
		FileLocation::operator=(e);
		severity = e.severity;
		src = e.src;
		msg = e.msg;
		parts[0] = e.parts[0];
		parts[1] = e.parts[1];
		parts[2] = e.parts[2];
	}
	
	void Serialize(Stream& s) {FileLocation::Serialize(s); s % severity % src % msg;}
	
	ProcMsg& Set(FileLocation loc, int severity, String src, String msg) {
		SetFileLocation(loc);
		this->severity = severity;
		this->src = src;
		this->msg = msg;
		return *this;
	}
	
	String ToString() const {
		String s;
		if (src.GetCount())
			s << ToUpper(src) << ": ";
		s	<< GetFileName(file)
			<< ":" << line
			<< ":" << col
			<< ": " << GetSeverityString()
			<< ": " << msg;
		return s;
	}
	
	String GetSeverityString() const {
		switch (severity) {
			case PROCMSG_UNKNOWN:	return "unknown";
			case PROCMSG_SKIP:		return "skip";
			case PROCMSG_INFO:		return "info";
			case PROCMSG_WARNING:	return "warning";
			case PROCMSG_ERROR:		return "error";
			default:				return "<invalid severity>";
		}
	}
};





class TextMatchFinder {
	struct Line : Moveable<Line> {
		int no;
		WString orig_txt;
		WString spaceless_txt;
		Vector<int> spaceless_orig_cursor;
	};
	Vector<Line> lines;
	
public:
	TextMatchFinder(String txt) {Parse(txt);}
	
	void Parse(String txt);
	bool Find(String line, Point& pt);
	
};



struct CoverSuggestionData {
	String artist;
	String album;
	int year;
	String genre;
	String singer_description;
	int count_of_components;
	
	struct Component {
		String name, scripts;
	};
	Array<Component> components;
};



const Vector<String>& CommonEntitys();

void TrimBothAllLines(String& s);
void RealizeDoubleNewlinesOnNumbered(String& s);
void RealizeDoubleNewlinesBeforeTitles(String& s);
Vector<String> GetStructureParts(String s);

String ToMinSec(double sec);
String GetComponentPartFromAbbr(const String& abbr);
String GetAbbrPartFromComponent(const String& abbr);
Color GetComponentPartPaperColor(const String& abbr);
String GetProgramPartFromAbbr(const String& abbr);
Color GetProgramPartPaperColor(const String& abbr);
int GetComponentPartPriority(const String& abbr);

template <class T> void CheckSerialisationData(const String& json) {}
template <> void CheckSerialisationData<TextLib::Component>(const String& json);

template <class T>
void LoadFromJsonFileStandard(T& o, const String& path) {
	String s = UPP::LoadFile(path);
	s = ToCharset(CHARSET_DEFAULT, s, CHARSET_UTF8);
	CheckSerialisationData<T>(s); // Has been a real issue
	LoadFromJson(o, s);
}

template <class T>
void StoreAsJsonFileStandard(T& o, const String& path, bool pretty=false) {
	String s = StoreAsJson(o, pretty);
	s = ToCharset(CHARSET_UTF8, s, CHARSET_DEFAULT);
	s.Replace("\\r\\n", "\\n");
	s.Replace("\r\n", "\n");
	RealizeDirectory(GetFileDirectory(path));
	FileOut fout(path);
	fout << s;
	fout.Close();
}

enum {
	BIAS_DEMOCRAT,
	BIAS_REPUBLICAN,
	BIAS_NONPARTISAN,
	BIAS_BEAUTIFULMUSIC,
};

String GetDemocratBiasHeader();
String GetRepublicanBiasHeader();
String GetNonPartisanBiasHeader();
String GetBiasHeader(int mode);


enum {
	#undef LNG_ENGLISH
	LNG_NATIVE,
	LNG_ENGLISH,
	LNG_FINNISH,
	LNG_SPANISH,
	LNG_PORTUGUESE,
	LNG_KOREAN,
	LNG_JAPANESE,
	LNG_RUSSIAN,
	LNG_CHINESE,
	
	LNG_COUNT
};

inline int GetLanguageCount() {return LNG_COUNT;}
inline const char* GetLanguageKey(int i) {
	switch (i) {
		case LNG_NATIVE: return "dataset native";
		case LNG_ENGLISH: return "english";
		case LNG_FINNISH: return "finnish";
		case LNG_SPANISH: return "spanish";
		case LNG_PORTUGUESE: return "portuguese";
		case LNG_KOREAN: return "korean";
		case LNG_JAPANESE: return "japanese";
		case LNG_RUSSIAN: return "russian";
		case LNG_CHINESE: return "chinese";
		default: return "";
	}
}

inline const char* GetLanguageCode(int i) {
	switch (i) {
		case LNG_NATIVE: return "";
		case LNG_ENGLISH: return "EN-US";
		case LNG_FINNISH: return "FI-FI";
		case LNG_SPANISH: return "ES-ES";
		case LNG_PORTUGUESE: return "PT-PT";
		case LNG_KOREAN: return "KO-KO";
		case LNG_JAPANESE: return "JA-JA";
		case LNG_RUSSIAN: return "RU-RU";
		case LNG_CHINESE: return "ZH-SG";
		default: return "";
	}
}

namespace Attr {

struct Group;

}

struct PartAbbrSorter {
	bool operator()(const String& a, const String& b) const;
};

int HexInt(String s);

AttrText GreenRedAttr(AttrText a, int red);





void TrimBothAll(Vector<String>& v);
int VectorFind(const Vector<String>& v, const String& s);
void RemoveQuotes(String& s);
void RemoveQuotes2(String& s);
void RemoveParenthesis(String& s);



enum {
	STORY_PHYSICAL_ACTIVITIES,
	STORY_PERSONS_OF_INTEREST,
	STORY_FEELINGS_OF_PERSONS,
	STORY_MOTIVATIONS_OF_PERSONS,
	STORY_PHYSICAL_ENVIRONMENT,
	STORY_SOCIAL_ENVIRONMENT,
	STORY_EMOTIONAL_ACTIVITIES,
	STORY_MENTAL_ACTIVITIES,
	STORY_VERBAL_ACTIVITIES,
	STORY_CULTURAL_OBJECTS,
	STORY_AESTHETIC_QUALITIES,
	STORY_TIME_AND_TEMPORALITY,
	STORY_VOCALIST_SEES,
	
	STORY_COUNT
};

extern const char* StoryContextString[STORY_COUNT][2];




enum {
	DIALOGUESTYLE_SURREAL,
	DIALOGUESTYLE_DREAMY,
	DIALOGUESTYLE_ETHEREAL,
	DIALOGUESTYLE_ROMANTIC,
	
	DIALOGUESTYLE_PASSIONATE,
	DIALOGUESTYLE_INTENSE,
	DIALOGUESTYLE_WHIMSICAL,
	DIALOGUESTYLE_IMAGINATIVE,
	
	DIALOGUESTYLE_MYSTICAL,
	DIALOGUESTYLE_OTHERWORLDLY,
	DIALOGUESTYLE_MAGICAL,
	
	
	DIALOGUESTYLE_AGGRESSIVE,
	DIALOGUESTYLE_ANXIOUS,
	DIALOGUESTYLE_CHAOTIC,
	DIALOGUESTYLE_CONFLICTED,
	
	DIALOGUESTYLE_UNSETTLING,
	DIALOGUESTYLE_DISSONANT,
	DIALOGUESTYLE_DISORIENTING,
	DIALOGUESTYLE_NASTY,
	
	DIALOGUESTYLE_HEAVY,
	DIALOGUESTYLE_OPPRESSIVE,
	DIALOGUESTYLE_EERIE,
	
	DIALOGUESTYLE_COUNT
};

extern const char* DialogueStyleString[DIALOGUESTYLE_COUNT];
extern Color DialogueStyleColors[DIALOGUESTYLE_COUNT];

int FindDialogueStyle(String value);
int GetColorDistance(const Color& a, const Color& b);

struct ColorDistanceSorter {
	Color cmp;
	bool operator()(const Color& a, const Color& b) const {
		int dist0 = GetColorDistance(a, cmp);
		int dist1 = GetColorDistance(b, cmp);
		return dist0 < dist1;
	}
};

struct TextColorDistanceSorter {
	Color cmp;
	Vector<String>* str = 0;
	Vector<Color>* clr = 0;
	bool operator()(const int& ai, const int& bi) const;
	void Sort();
};

const Vector<String>& InlineRapperList();
const Vector<String>& OtherRapperList();



enum {
	LISTENERTYPE_MAN,
	LISTENERTYPE_WOMAN,
	
	LISTENERTYPE_COUNT,
};

extern const char* ListenerTypeString[LISTENERTYPE_COUNT];

struct ColoredText {
	const char* txt;
	byte r, g, b;
	
	Color GetColor() const {ASSERT(txt); return Color(r,g,b);}
	String GetText() const {ASSERT(txt); return txt;}
};

enum {
	VOCABULARYTYPE_IMPORTANT_WORD,
	VOCABULARYTYPE_POSITIVE_WORD,
	VOCABULARYTYPE_NEGATIVE_WORD,
	
	VOCABULARYTYPE_IMPORTANT_PHRASE,
	VOCABULARYTYPE_POSITIVE_PHRASE,
	VOCABULARYTYPE_NEGATIVE_PHRASE,
	
	VOCABULARYTYPE_COUNT,
	
	VOCABULARYTYPE_WORDCOUNT = VOCABULARYTYPE_IMPORTANT_PHRASE
};

extern const char* VocabularyTypeString[VOCABULARYTYPE_COUNT];

#define SIGNIFICANT_PHRASE_COUNT 100
extern ColoredText SignificantPhrases[VOCABULARYTYPE_COUNT][SIGNIFICANT_PHRASE_COUNT];


enum {
	COLORTYPE_MAIN,
	COLORTYPE_ATTACK,
	COLORTYPE_SUSTAIN,
	COLORTYPE_RELEASE,
	
	COLORTYPE_COUNT
};

extern const char* ColorTypeString[COLORTYPE_COUNT];


enum {
	ROLE_PROTAGONIST,
	ROLE_ANTAGONIST,
	ROLE_SIDEKICK,
	ROLE_LOVER,
	ROLE_FOLLOWER,
	ROLE_CHILD,
	ROLE_PARENT,
	ROLE_EXTENDED_FAMILY,
	ROLE_PEER,
	ROLE_CITIZEN,
	
	ROLE_CITIZEN_WORRYING,
	ROLE_CITIZEN_HAPPY,
	ROLE_CITIZEN_ANGRY,
	ROLE_CITIZEN_COMPETITIVE,
	ROLE_CITIZEN_PEACEFUL,
	ROLE_CITIZEN_AUTHORITARIAN,
	ROLE_CITIZEN_LIBERAL,
	ROLE_CITIZEN_POOR,
	ROLE_CITIZEN_RICH,
	ROLE_CITIZEN_SUBURBIAN,
	ROLE_CITIZEN_URBAN,
	ROLE_CITIZEN_BACKCOUNTRY,
	
	ROLE_SOLDIER,
	ROLE_STUDENT,
	ROLE_MODEL,
	ROLE_MERCHANT,
	ROLE_CLIENT,
	ROLE_SERVER,
	ROLE_NEWSREADER,
	ROLE_FORECASTER,
	ROLE_INCLUSIVITY_GENETIC,
	ROLE_INCLUSIVITY_GENETIC_HEALTH,
	ROLE_INCLUSIVITY_HEALTH,
	ROLE_INCLUSIVITY_AGE,
	ROLE_INCLUSIVITY_WEALTH,
	ROLE_INCLUSIVITY_SOCIAL,
	ROLE_INCLUSIVITY_RANDOM,
	ROLE_WISE_OLD_MAN,
	ROLE_WISE_OLD_WOMAN,
	ROLE_NIGHTCLUB_DANCER,
	ROLE_CAR_DRIVER,
	ROLE_STREET_WALKER,
	ROLE_HOPEFUL_DREAMER,
	
	ROLE_COUNT
};
	
extern const char* RoleString[ROLE_COUNT];


enum {
	FOCUSMODE_1ST_PERSON,
	FOCUSMODE_3RD_PERSON,
	FOCUSMODE_DIRECT_REFERENCE,
	FOCUSMODE_INDIRECT_REFERENCE,
	FOCUSMODE_DEPENDENCY_REFERENCE,
	
	FOCUSMODE_COUNT
};

extern const char* FocusModeString[FOCUSMODE_COUNT];


enum {
	WORDGROUP_PRONOUN,
	WORDGROUP_NOUN,
	WORDGROUP_ADJECTIVE,
	WORDGROUP_PREPOSITIONS,
	WORDGROUP_CONJUNCTIONS,
	WORDGROUP_VERBS,
	
	WORDGROUP_COUNT
};

extern const char* WordGroupString[WORDGROUP_COUNT];


struct ProductionIdeaTopic : Moveable<ProductionIdeaTopic> {
	Vector<String> positive, negative;
	String title;
	
	void Add(const char* v) {positive.Add(TrimBoth(v));}
	void AddPos(const char* v) {positive.Add(TrimBoth(v));}
	void AddNeg(const char* v) {negative.Add(TrimBoth(v));}
	void Sort() {UPP::Sort(positive, StdLess<String>()); UPP::Sort(negative, StdLess<String>());}
	
};

const Vector<ProductionIdeaTopic>& ProductionIdeas();



void EscapeString(String& s);

void SplitParenthesisWords(const String& line, Vector<String>& words, Vector<bool>& parenthesis);
void GetWords(const String& line, Vector<String>& words);
const VectorMap<String,Color>& GetWordgroupColors();

Color GetSentenceColor(const Vector<String>& main_classes, const Vector<Color>& clrs);

void ReplaceWord(String& s, const String& orig_word, const String& replace_word);


int GetColorGroupCount();
const Color& GetGroupColor(int i);
int GetColorGroup(const Color& clr);


enum {
	STRESS_NONE,
	STRESS_PRIMARY,
	STRESS_SECONDARY,
};

void HotfixReplaceWord(WString& ws);
void HotfixReplaceWord(String& s);


template <class T>
int VectorFindAdd(Vector<T>& v, const T& o0) {
	int i = 0;
	for (const T& o1 : v) {
		if (o1 == o0)
			return i;
		i++;
	}
	i = v.GetCount();
	v.Add(o0);
	return i;
}

template <class T>
int VectorFind(Vector<T>& v, const T& o0) {
	int i = 0;
	for (const T& o1 : v) {
		if (o1 == o0)
			return i;
		i++;
	}
	return -1;
}

template <class T>
void VectorRemoveKey(Vector<T>& v, const T& o0) {
	for(int i = 0; i < v.GetCount(); i++) {
		const T& o1 = v[i];
		if (o1 == o0) {
			v.Remove(i--);
		}
	}
}

void SetColoredListValue(ArrayCtrl& list, int row, int col, const String& txt, Color clr, bool blend=true);






struct CallbackInhibitor {
	Event<> cb;
	Event<>& ref;
	
	CallbackInhibitor(Event<>& other) : cb(other), ref(other) {other.Clear();}
	~CallbackInhibitor() {ref = cb;}
};

#define INHIBIT_CURSOR(x) CallbackInhibitor __cur(x.WhenCursor)
#define INHIBIT_CURSOR_(x, id) CallbackInhibitor __##id(x.WhenCursor)
#define INHIBIT_ACTION(x) CallbackInhibitor __act(x.WhenAction)
#define INHIBIT_ACTION_(x, id) CallbackInhibitor __##id(x.WhenAction)




struct ActionHeader : Moveable<ActionHeader> {
	String action, arg;
	
	ActionHeader() {}
	ActionHeader(ActionHeader&& a) : action(std::move(a.action)), arg(std::move(a.arg)) {}
	ActionHeader(const ActionHeader& a) {action = a.action; arg = a.arg;}
	void operator=(const ActionHeader& a) {action = a.action; arg = a.arg;}
	bool operator==(const ActionHeader& a) const {return action == a.action && arg == a.arg;}
	hash_t GetHashValue() const {CombineHash c; c.Do(action); c.Put(1); c.Do(arg); return c;}
	bool operator()(const ActionHeader& a, const ActionHeader& b) const {
		if (a.action != b.action) return a.action < b.action;
		return a.arg < b.arg;
	}
	bool IsEmpty() const {return action.IsEmpty() || arg.IsEmpty();}
	void Jsonize(JsonIO& json) {
		json("action", action)("arg",arg);
	}
	void Serialize(Stream& s) {
		s % action % arg;
	}
	void Trim() {action = TrimBoth(action); arg = TrimBoth(arg);}
};

struct AttrHeader : Moveable<AttrHeader> {
	String group, value;
	
	AttrHeader() {}
	AttrHeader(String g, String v) : group(g), value(v) {}
	AttrHeader(AttrHeader&& a) : group(std::move(a.group)), value(std::move(a.value)) {}
	AttrHeader(const AttrHeader& a) {group = a.group; value = a.value;}
	void operator=(const AttrHeader& a) {group = a.group; value = a.value;}
	bool operator==(const AttrHeader& a) const {return group == a.group && value == a.value;}
	hash_t GetHashValue() const {CombineHash c; c.Do(group); c.Put(1); c.Do(value); return c;}
	bool operator()(const AttrHeader& a, const AttrHeader& b) const {
		if (a.group != b.group) return a.group < b.group;
		return a.value < b.value;
	}
	bool IsEmpty() const {return group.IsEmpty() || value.IsEmpty();}
	void Jsonize(JsonIO& json) {
		json("group", group)("value",value);
	}
	void Serialize(Stream& s) {
		s % group % value;
	}
	void Trim() {group = TrimBoth(group); value = TrimBoth(value);}
};

Color HSVToRGB(double H, double S, double V);

hash_t HexHash(const String& s);
String HashHex(hash_t h);

int FindNonEscaped(const String& s, const String& search);
int FindNonEscaped(const String& s, const String& search, int begin);
int FindNonEscaped(const WString& s, const WString& search, int begin);


template <class T>
int FixedIndexFindAdd(T* values, int max_value_count, int& value_count, const T& new_value) {
	ASSERT(value_count >= 0 && value_count <= max_value_count);
	T* it = values;
	T* end = it + value_count;
	int i = 0;
	while (it != end) {
		if (*it == new_value)
			return i;
		it++;
		i++;
	}
	ASSERT(value_count < max_value_count);
	*it = new_value;
	value_count++;
	return i;
}


template <class T>
void JsonCompressedStream(JsonIO& json, const String& key, T& o) {
	if (json.IsLoading()) {
		String s;
		json(key, s);
		if (s.GetCount())
			s = FastDecompress(s);
		StringStream ss(s);
		ss % o;
	}
	else {
		StringStream ss;
		ss % o;
		String s = ss.GetResult();
		if (s.GetCount())
			s = FastCompress(s);
		json(key, s);
	}
}






struct GenericType : Moveable<GenericType> {
	static const int PART_COUNT = 3;
	String key, parts[PART_COUNT];
	
	void Set(String k, String p0, String p1, String p2) {
		key = k;
		parts[0] = p0;
		parts[1] = p1;
		parts[2] = p2;
	}
};

int GetRoleCount();
int GetGenericCount();
const Vector<String>& GetGenericParts();


void SetIndexCursor(ArrayCtrl& arr, int cur);

void FixOffensiveWords(String& s);











enum {
	LEADSITE_TAXI,
	LEADSITE_MUSICXRAY,
	LEADSITE_SONICBIDS,
	
	LEADSITE_COUNT,
};

const char* GetLeadWebsiteKey(int leadsite_idx);



struct LeadCache {
	VectorMap<String, Time> last_update;
	
	
	LeadCache() {LoadFromFile(*this, ConfigFile("lead-cache.bin"));}
	~LeadCache() {StoreToFile(*this, ConfigFile("lead-cache.bin"));}
	void Serialize(Stream& s) {s % last_update;}
	
};




String DeHtml(String html, Vector<String>& links);

bool IsAllUpper(const String& s);



String GetDefaultScriptStructureString();


void SetGlobalProxy(String uri);
String GetGlobalProxy();

const Vector<String>& GetElements();


String AppendUnixFileName(String a, String b);

ValueMap& ValueToMap(Value& val);
ValueArray& ValueToArray(Value& val);



String KeyToName(String s);
String StringToName(String s);


END_TEXTLIB_NAMESPACE


#endif

