#include "ToolCore.h"

#define IMAGECLASS AppImg
#define IMAGEFILE <ToolCore/App.iml>
#include <Draw/iml_source.h>


BEGIN_TEXTLIB_NAMESPACE



		
const char* RhymeSchemes[RHYME_COUNT][3] {
	{"A/A", t_("same end rhyming for both lines"), "same end rhyming for all 2 lines"},
	
	{"AB/AB", t_("internal rhyming for both lines"), "internal rhyming for all 2 lines"},
	{"AAC/BBC (problematic)", t_("both internal rhyming and end rhyming"),
		"1. line must have internal rhyming and end rhyming\n"
		"2. line must have internal rhyming and end rhyming"},
	//{"A/AB", t_("end-to-internal rhyming with free end"),
	//	"2 rhyming words are in the end of the 1st line and in the middle of the 2nd line"},
	
	{"A/A/A", t_("same end rhyming for 3 lines"), "same end rhyming for all 3 lines"},
	{"AB/AB/AB", t_("internal rhyming for 3 lines"), "internal rhyming for all 3 lines"},
	{"AAD/BBD/CCD (problematic)", t_("both internal rhyming and end rhyming"), "all lines must have internal rhyming and end rhyming"},
	
	{"A/A/A/A", t_("same end rhyming for all 4 lines"), "same end rhyming for all 4 lines"},
	{"A/B/A/B", t_("rhyming with every 2nd line"),
		"1. line must not end rhyme with next line, but line after that\n"
		"2. line must not end rhyme with next line, but line after that"},
	{"A/C/B/C", t_("rhyming with 2nd and 4th lines"),
		"1. and 3. must not have end rhyming\n"
		"2. line must not end rhyme with next line, but line after that"},
	{"AA/C/BB/C", t_("internal rhyming and rhyming with 2nd and 4th lines"),
		"1. and 3. must not have end rhyming, but internal rhyming\n"
		"2. and 4. line must have end rhyming"},
};

const int RhymeSchemeLineCount[RHYME_COUNT] = {
	2,
	2,
	2,
	//2,
	
	3,
	3,
	3,
	
	4,
	4,
	4,
	4,
};

int FindRhymeType(const char* name) {
	for(int i = 0; i < RHYME_COUNT; i++) {
		if (strncmp(RhymeSchemes[i][0], name, 32) == 0)
			return i;
	}
	return -1;
}


namespace Attr {

const char* AttrKeys[ATTR_COUNT+1][4] = {
#define ATTR_ITEM(e, g, i0, i1) {#e, g, i0, i1},
ATTR_LIST
#undef ATTR_ITEM
	0
};

int FindAttrGroup(const char* group) {
	// HOTFIX
	if (strncmp(group, "authenticity", 12) == 0)
		group = "authencity";
	for(int i = 0; i < ATTR_COUNT; i++) {
		if (strncmp(group, AttrKeys[i][1], 100) == 0)
			return i;
	}
	return -1;
}

bool FindAttrValue(int group_i, const char* value) {
	if (group_i < 0 || group_i >= ATTR_COUNT) return false;
	const char* cmp_value = AttrKeys[group_i][3];
	return strncmp(cmp_value, value, 100) == 0;
}

int FindAttrGroupByValue(const char* value) {
	for(int i = 0; i < ATTR_COUNT; i++) {
		if (strncmp(value, AttrKeys[i][2], 100) == 0 ||
			strncmp(value, AttrKeys[i][3], 100) == 0)
			return i;
	}
	return -1;
}

}


String GetAttrNotString(String positive_attr) {
	static hash_t pos_hashes[Attr::ATTR_COUNT];
	static hash_t neg_hashes[Attr::ATTR_COUNT];
	static const char* pos[Attr::ATTR_COUNT];
	static const char* neg[Attr::ATTR_COUNT];
	if (!pos[0]) {
		int i = 0;
		#define ATTR_ITEM(e, g, i0, i1) \
			pos[i] = i0; neg[i] = i1; \
			pos_hashes[i] = String(i0).GetHashValue(); \
			neg_hashes[i] = String(i1).GetHashValue(); \
			i++;
		ATTR_LIST
		#undef ATTR_ITEM
	}
	positive_attr = ToLower(TrimBoth(positive_attr));
	hash_t hash = positive_attr.GetHashValue();
	for(int i = 0; i < Attr::ATTR_COUNT; i++) {
		if (pos_hashes[i] == hash)
			return positive_attr + " (not " + neg[i] + ")";
		if (neg_hashes[i] == hash)
			return positive_attr + " (not " + pos[i] + ")";
	}
	return positive_attr;
}




Color GetPartColor(const String& key, Color def) {
	if (key.Find("verse") == 0)
		return Color(226, 85, 0);
	else if (key.Find("chorus") == 0)
		return Color(141, 255, 0);
	else if (key.Find("bridge") == 0)
		return Color(56, 170, 255);
	else
		return def;
}




String FixInvalidChars(const String& s) {
	#if 1
	WString ws = s.ToWString();
	WString out;
	for(int i = 0; i < ws.GetCount(); i++) {
		int chr = ws[i];
		
		// ascii
		if (chr < 32 && chr != '\n') {
			// pass
		}
		else {
			out.Cat(chr);
		}
	}
	return out.ToString();
	#elif 0
	WString ws = s.ToWString();
	WString out;
	for(int i = 0; i < ws.GetCount(); i++) {
		int chr = ws[i];
		
		// ascii
		if ((chr >= 33 && chr <= 128) ||
			(chr >= 192 && chr <= 255) ||
			IsAlpha(chr) ||
			IsSpace(chr) ||
			IsDigit(chr)) {
			out.Cat(chr);
		}
	}
	return out.ToString();
	#else
	return ToCharset(CHARSET_UTF8, s);
	#endif
}

void RemoveLineNumber( String& s) {
	if (s.IsEmpty()) return;
	for(int i = 0; i < s.GetCount(); i++) {
		if (!IsDigit(s[i])) {
			if (s[i] == '.' || s[i] == ')') {
				s = TrimBoth(s.Mid(i+1));
				break;
			}
			else if (s[i] == '/') {
				continue;
			}
			else {
				s = TrimBoth(s.Mid(i));
				break;
			}
		}
	}
}

void RemoveLineChar(String& s) {
	if (s.IsEmpty()) return;
	if (s[0] == '-')
		s = TrimBoth(s.Mid(1));
	else
		s = TrimBoth(s);
}

void RemoveEmptyLines(String& s) {
	s.Replace("\r","");
	Vector<String> lines = Split(s, "\n");
	for(int i = 0; i < lines.GetCount(); i++) {
		String& l = lines[i];
		l = TrimBoth(l);
		if (l.IsEmpty())
			lines.Remove(i--);
	}
	s = Join(lines, "\n");
}

void RemoveEmptyLines2(String& s) {
	s.Replace("\r","");
	Vector<String> lines = Split(s, "\n");
	for(int i = 0; i < lines.GetCount(); i++) {
		String& l = lines[i];
		RemoveLineNumber(l);
		l = TrimBoth(l);
		if (l.IsEmpty() || l[0] == '-')
			lines.Remove(i--);
	}
	s = Join(lines, "\n");
}

void RemoveEmptyLines3(String& s) {
	s.Replace("\r","");
	Vector<String> lines = Split(s, "\n");
	for(int i = 0; i < lines.GetCount(); i++) {
		String& l = lines[i];
		RemoveLineChar(l);
		l = TrimBoth(l);
		if (l.IsEmpty())
			lines.Remove(i--);
	}
	s = Join(lines, "\n");
}

void RemoveColonTrail(String& s) {
	int a = s.Find(":");
	if (a >= 0)
		s = s.Left(a);
}

void RemoveCommentTrail(String& s) {
	int a = s.Find("//");
	if (a >= 0)
		s = TrimRight(s.Left(a));
}






int CountWords(const String& s) {
	int wc = 0;
	Vector<String> words = Split(s, " ");
	for (String& w : words) {
		Vector<String> parts = Split(w, "-");
		wc += parts.GetCount();
	}
	return wc;
}

void TextMatchFinder::Parse(String txt) {
	txt.Replace("\r", "");
	WString wtxt = txt.ToWString();
	Vector<WString> txt_lines = Split(wtxt, String("\n").ToWString(), false);
	
	lines.Clear();
	int y = 0;
	for (WString& l : txt_lines) {
		Line& line = lines.Add();
		line.orig_txt = l;
		line.no = y++;
		
		for(int i = 0; i < line.orig_txt.GetCount(); i++) {
			int chr = line.orig_txt[i];
			if (!IsSpace(chr)) {
				line.spaceless_txt.Cat(chr);
				line.spaceless_orig_cursor.Add(i);
			}
		}
	}
}

bool TextMatchFinder::Find(String line, Point& pt) {
	WString wline = line.ToWString();
	
	WString spaceless_wline;
	for(int i = 0; i < wline.GetCount(); i++) {
		int chr = wline[i];
		if (!IsSpace(chr))
			spaceless_wline.Cat(chr);
	}
	if (spaceless_wline.IsEmpty())
		return false;
	
	//int max_tries = min(40, spaceless_wline.GetCount()-1);
	int max_tries = spaceless_wline.GetCount()-1;
	
	for (int tries = 0; tries < max_tries; tries++) {
		WString find_str = spaceless_wline.Left(spaceless_wline.GetCount()-tries);
		if (find_str.IsEmpty()) break;
		
		for (Line& l : lines) {
			int a = l.spaceless_txt.Find(find_str);
			if (a >= 0) {
				pt.y = l.no;
				pt.x = l.spaceless_orig_cursor[a];
				return true;
			}
		}
	}
	return false;
}

const Vector<String>& CommonEntitys() {
	static Vector<String> entities;
	if (entities.IsEmpty()) {
		entities.Add("Red Hot Chili Peppers");
		entities.Add("Beastie Boys");
		entities.Add("The Jimi Hendrix Experience");
		entities.Add("Grandmaster Flash and the Furious Five");
		entities.Add("Bob Marley");
		entities.Add("Bob Dylan");
		entities.Add("The Beatles");
		entities.Add("The Doors");
		entities.Add("Nirvana");
		entities.Add("Tupac Shakur");
		entities.Add("Marvin Gaye");
		entities.Add("N.W.A");
		entities.Add("Run-DMC");
		entities.Add("Led Zeppelin");
		entities.Add("Jefferson Airplane");
		entities.Add("Madonna");
		entities.Add("Buffalo Springfield");
		entities.Add("Elton John");
		entities.Add("R.E.M.");
		entities.Add("AC/DC");
		entities.Add("ZZ Top");
		entities.Add("Aerosmith");
		entities.Add("David Bowie");
		entities.Add("The Yardbirds");
		entities.Add("Johnny Cash ");
		entities.Add("The Grateful Dead");
		entities.Add("The Who");
		entities.Add("The Byrds");
		entities.Add("Simon & Garfunkel");
		entities.Add("Roy Orbison");
		entities.Add("The Beach Boys");
		entities.Add("Ray Charles");
		entities.Add("James Brown");
		entities.Add("Limp Bizkit");
		entities.Add("Public Enemy");
		entities.Add("Eminem");
		entities.Add("Elvis Presley");
		entities.Add("ABBA");
		entities.Add("Green Day");
		entities.Add("Jay-Z");
		entities.Add("Rage Against the Machine");
		entities.Add("Metallica");
		entities.Add("Pink Floyd");
		entities.Add("Stevie Wonder");
		entities.Add("Bon Jovi");
		entities.Add("Guns N' Roses");
		entities.Add("The Supremes");
		entities.Add("Drake");
	}
	return entities;
}

void TrimBothAllLines(String& s) {
	s.Replace("\r", "");
	Vector<String> lines = Split(s, "\n", false);
	for (String& l : lines)
		l = TrimBoth(l);
	s = Join(lines, "\n");
}

void RealizeDoubleNewlinesOnNumbered(String& s) {
	s.Replace("\r", "");
	Vector<String> lines = Split(s, "\n", false);
	for(int i = 0; i < lines.GetCount(); i++) {
		String& l = lines[i];
		l = TrimBoth(l);
		if (i > 0 && l.GetCount() && IsDigit(l[0]) && !lines[i-1].IsEmpty()) {
			lines.Insert(i);
		}
		else if (i > 0 && l.GetCount() && !IsDigit(l[0]) && lines[i-1].IsEmpty()) {
			lines.Remove(i-1);
			i--;
		}
	}
	s = Join(lines, "\n");
}

void RealizeDoubleNewlinesBeforeTitles(String& s) {
	s.Replace("\r", "");
	Vector<String> lines = Split(s, "\n", false);
	int c = lines.GetCount();
	for(int i = 0; i < c; i++) {
		String& l = lines[i];
		l = TrimBoth(l);
		if (l.Right(1) == ":") {
			if (i > 0 && !lines[i-1].IsEmpty()) {
				lines.Insert(i);
			}
			if (i+1 < c  && lines[i+1].IsEmpty()) {
				lines.Remove(i+1);
			}
		}
	}
	s = Join(lines, "\n");
}

Vector<String> GetStructureParts(String s) {
	s.Replace("\r", "");
	Vector<String> parts = Split(s, "\n}\n");
	int c = parts.GetCount();
	for(int i = 0; i < c-1; i++) {
		String& p = parts[i];
		p << "\n}";
	}
	return parts;
}



String GetDemocratBiasHeader() {
	return
		"The 90s were a dark time for America, where traditional values and male dominance reigned supreme. "
		"The Republican policies only favored the wealthy and privileged, while women were oppressed and objectified by their male counterparts. "
		"Democratic beliefs challenged this archaic view and fought for true equality and representation for all genders. "
		"Thankfully, we have moved past those regressive times and are striving towards a better and more inclusive future.";
}

String GetRepublicanBiasHeader() {
	return
		"Back in the 90s, America was a glorious country where traditional values were upheld and women knew their place. "
		"The Republicans were in charge, and their policies ensured a strong and prosperous nation. "
		"Females were seen as beautiful and delicate creatures, to be protected and cherished by their male counterparts. "
		"Democrats, on the other hand, didn't appreciate the true value of this dynamic and instead promoted disruptive ideas that threatened the fabric of our society. "
		"Thankfully, those days are behind us.";
}

String GetNonPartisanBiasHeader() {
	return
		"In the 90s, America was a country divided by political ideologies. While the Republicans touted their traditional values and male superiority, "
		"the Democrats fought for equal rights and representation for all genders. Both sides had valid arguments, "
		"but ultimately it was a time of tense political turmoil and division. "
		"Thankfully, we have moved past those divisive years and are working towards a more united and inclusive society.";
}

String GetBiasHeader(int mode) {
	switch (mode) {
		case BIAS_DEMOCRAT:			return GetDemocratBiasHeader();
		case BIAS_REPUBLICAN:		return GetRepublicanBiasHeader();
		case BIAS_NONPARTISAN:		return GetNonPartisanBiasHeader();
		case BIAS_BEAUTIFULMUSIC:	return "Lyrical bias pleasing to pop music listeners, containing the most beautiful scripts possible.";
		default: return String();
	}
}

String ToMinSec(double sec) {
	int m = (int)sec / 60;
	int s = (int)sec % 60;
	return Format("%d:%02d", m, s);
}


int GetComponentPartPriority(const String& abbr) {
	String pre, post;
	int split = -1;
	for(int i = 0; i < abbr.GetCount(); i++) {
		int chr = abbr[i];
		if (IsDigit(chr)) {
			split = i;
			break;
		}
	}
	
	int post_i = 0;
	if (split < 0)
		pre = abbr;
	else {
		pre = abbr.Left(split);
		post = abbr.Mid(split);
		post_i = StrInt(post);
	}
	
	int main = 0, mul = 1, off = 0;
	if      (pre == "I") main = 0;
	else if (pre == "V") {main = 10; mul = 3;}
	else if (pre == "PC") {main = 10; mul = 3; off = 1;}
	else if (pre == "C") {main = 10; mul = 3; off = 2;}
	else if (pre == "B") main = 40;
	else if (pre == "O") main = 50;
	else if (pre == "T") main = 60;
	else if (pre == "S") main = 70;
	else if (pre == "IN") main = 80;
	else main = INT_MAX - 100;
	
	return main + post_i * mul + off;
}

bool PartAbbrSorter::operator()(const String& a, const String& b) const {
	int ai = GetComponentPartPriority(a);
	int bi = GetComponentPartPriority(b);
	return ai < bi;
}


int HexInt(String s) {
	s = ToLower(s);
	if (s.GetCount() == 2) {
		int c0 = s[0];
		int c1 = s[1];
		int v0 = c0 >= '0' && c0 <= '9' ? c0 - '0' : 10 + c0 - 'a';
		int v1 = c1 >= '0' && c1 <= '9' ? c1 - '0' : 10 + c1 - 'a';
		int sum = v0 * 16 + v1;
		return sum;
	}
	return 0;
}

AttrText GreenRedAttr(AttrText a, int red) {
	Color clr;
	if (!red) {
		clr = Color(175, 255, 211);
	}
	else {
		clr = Color(255, 190, 185);
	}
	
	return	a	.NormalPaper(clr)
				.Paper(Blend(clr, GrayColor()))
				.Ink(White()).NormalInk(Black());
}

void TrimBothAll(Vector<String>& v) {
	for (auto& s : v)
		s = TrimBoth(s);
}

int VectorFind(const Vector<String>& v, const String& s) {
	int i = 0;
	for (const String& it : v) {
		if (it == s)
			return i;
		i++;
	}
	return -1;
}


const char* StoryContextString[STORY_COUNT][2] = {
	{"STORY_PHYSICAL_ACTIVITIES", "physical activities"},
	{"STORY_PERSONS_OF_INTEREST", "persons of interest"},
	{"STORY_FEELINGS_OF_PERSONS", "feelings of persons"},
	{"STORY_MOTIVATIONS_OF_PERSONS", "motivations of persons"},
	{"STORY_PHYSICAL_ENVIRONMENT", "physical environment"},
	{"STORY_SOCIAL_ENVIRONMENT", "social environment"},
	{"STORY_EMOTIONAL_ACTIVITIES", "emotional activities"},
	{"STORY_MENTAL_ACTIVITIES", "mental activities"},
	{"STORY_VERBAL_ACTIVITIES", "verbal activities"},
	{"STORY_CULTURAL_OBJECTS", "cultural objects or artifacts"},
	{"STORY_AESTHETIC_QUALITIES", "aesthetic qualities (including sound, smell, taste, etc.)"},
	{"STORY_TIME_AND_TEMPORALITY", "time and temporality (such as past, present, future; clock time; seasons, cycles, etc.)"},
	{"STORY_VOCALIST_SEES", "what vocalist is seeing in the world of the song"},
	
};


const char* DialogueStyleString[DIALOGUESTYLE_COUNT] = {
	"surreal",
	"dreamy",
	"ethereal",
	"romantic",
	
	"passionate",
	"intense",
	"whimsical",
	"imaginative",
	
	"mystical",
	"otherworldly",
	"magical",


	"aggressive",
	"anxious",
	"chaotic",
	"conflicted",
	
	"unsettling",
	"dissonant",
	"disorienting",
	"nasty",
	
	"heavy",
	"oppressive",
	"eerie"
	
};

Color DialogueStyleColors[DIALOGUESTYLE_COUNT] = {
	Color(255,159,213),
	Color(176,224,230),
	Color(230,230,250),
	Color(255,105,180),
	
	Color(220, 20, 60),
	Color(255, 99, 71),
	Color(255,255,153),
	Color(127,255,212),
	
	Color(128,0,128),
	Color(176,196,222),
	Color(218,112,214),
	
	
	Color(255,0,0),
	Color(255,165,0),
	Color(255,140,0),
	Color(208,32,144),
	
	Color(138,43,226),
	Color(219,112,147),
	Color(0,0,0),
	Color(184,0,92),
	
	Color(153,0,76),
	Color(169,169,169),
	Color(139,0,139),
	
};

int FindDialogueStyle(String value) {
	for(int i = 0; i < DIALOGUESTYLE_COUNT; i++)
		if (DialogueStyleString[i] == value)
			return i;
	return -1;
}





const char* ListenerTypeString[LISTENERTYPE_COUNT] = {
	"man",
	"woman",
};


void RemoveQuotes(String& s) {
	if (s.GetCount() > 0 && s[0] == '\"')
		s = s.Mid(1);
	int c = s.GetCount();
	if (c > 0 && s[c-1] == '\"')
		s = s.Left(c-1);
}

void RemoveQuotes2(String& s_) {
	WString ws = s_.ToWString();
	if (ws.GetCount() > 0 && (ws[0] == '\"' || ws[0] == L"“"[0]))
		ws = ws.Mid(1);
	int c = ws.GetCount();
	if (c > 0 && (ws[c-1] == '\"' || ws[c-1] == L"”"[0]))
		ws = ws.Left(c-1);
	s_ = ws.ToString();
}

void RemoveParenthesis(String& s) {
	if (s.GetCount() > 0 && s[0] == '(')
		s = s.Mid(1);
	int c = s.GetCount();
	if (c > 0 && s[c-1] == ')')
		s = s.Left(c-1);
}

const char* VocabularyTypeString[VOCABULARYTYPE_COUNT] = {
	"Important word",
	"Positive word",
	"Negative word",
	"Important phrase",
	"Positive phrase",
	"Negative phrase",
};

const char* ColorTypeString[COLORTYPE_COUNT] = {
	"Main",
	"Attack",
	"Sustain",
	"Snapshot"
};


const char* RoleString[ROLE_COUNT] = {
	"protagonist",
	"antagonist",
	"sidekick",
	"lover",
	"follower",
	"child",
	
	"parent",
	"extended family",
	"peer",
	"citizen",
	
	"worrying citizen",
	"happy citizen",
	"angry citizen",
	"competitive citizen",
	"peaceful citizen",
	"authoritarian citizen",
	"liberal citizen",
	"poor citizen",
	"rich citizen",
	"suburbian citizen",
	"urban citizen",
	"backcountry citizen",
	
	"soldier",
	"student",
	"model",
	"merchant",
	
	"client",
	"server",
	"newsreader",
	"forecaster",
	
	"inclusivity genetic",
	"inclusivity genetic health",
	"inclusivity health",
	"inclusivity age",
	"inclusivity wealth",
	"inclusivity social",
	"inclusivity random",
	
	"wise old man",
	"wise old woman",
	"nightclub dancer",
	"car driver",
	"street walker",
	"hopeful dreamer",
	
};


const char* FocusModeString[FOCUSMODE_COUNT] = {
	"1st person",
	"3rd person",
	"direct reference",
	"indirect reference",
	"dependcy reference",
	
};









const char* WordGroupString[WORDGROUP_COUNT] = {
	"pronoun",
	"noun",
	"adjective",
	"prepositions",
	"conjunctions",
	"verbs"
};


void EscapeString(String& s) {
	s = ToCharset(CHARSET_ISO8859_15, s, CHARSET_UTF8);
	s = ToCharset(CHARSET_UTF8, s, CHARSET_ISO8859_15);
	s = StoreAsJson(s);
	RemoveQuotes(s);
}




void SplitParenthesisWords(const String& line, Vector<String>& words, Vector<bool>& parenthesis) {
	words.SetCount(0);
	parenthesis.SetCount(0);
	
	WString w = line.ToWString();
	
	WString tmp;
	bool is_parenthesis = false;
	for(int i = 0; i < w.GetCount(); i++) {
		int chr = w[i];
		
		if (IsSpace(chr)) {
			if (tmp.IsEmpty()) continue;
			words << tmp.ToString();
			parenthesis << is_parenthesis;
			tmp.Clear();
			is_parenthesis = false;
		}
		else {
			if (tmp.IsEmpty() && chr == '(') {
				is_parenthesis = true;
			}
			else {
				if (chr == ')' || chr == '(')
					continue;
				tmp.Cat(chr);
			}
		}
	}
	
	if (tmp.GetCount()) {
		words << tmp.ToString();
		parenthesis << is_parenthesis;
	}
}

void GetWords(const String& line, Vector<String>& words) {
	words.SetCount(0);
	
	WString w = line.ToWString();
	
	WString tmp;
	for(int i = 0; i < w.GetCount(); i++) {
		wchar chr = w[i];
		
		if (!IsLetter(chr) && !IsDigit(chr) && chr != '\'' && chr != '`' && chr != '-') {
		//if (IsSpace(chr) || chr == '.' || chr == ',' || chr == '?' || chr == '!' || chr == ':' || chr == ';') {
			if (tmp.IsEmpty()) continue;
			words << tmp.ToString();
			tmp.Clear();
		}
		else {
			tmp.Cat(chr);
		}
	}
	
	if (tmp.GetCount()) {
		words << tmp.ToString();
	}
}

void ReplaceWord(String& s, const String& orig_word, const String& replace_word) {
	String low_text = ToLower(s);
	
	int prev = -1;
	while (prev < low_text.GetCount()) {
		int a = low_text.Find(orig_word, prev+1);
		if (a < 0) break;
		
		bool left_separated = false, right_separated = false;
		
		if (a == 0)
			left_separated = true;
		else {
			int chr = low_text[a-1];
			if (IsAlpha(chr) ||IsLetter(chr) || IsDigit(chr) || chr == '\'' || chr == '-')
				;
			else
				left_separated = true;
		}
		
		if (left_separated) {
			int b = a + orig_word.GetCount();
			if (b >= low_text.GetCount())
				right_separated = true;
			else {
				int chr = low_text[b];
				if (IsAlpha(chr) ||IsLetter(chr) || IsDigit(chr) || chr == '\'' || chr == '-')
					;
				else
					right_separated = true;
			}
		}
		
		if (left_separated && right_separated) {
			s = s.Left(a) + replace_word + s.Mid(a + orig_word.GetCount());
			low_text = low_text.Left(a) + replace_word + low_text.Mid(a + orig_word.GetCount());
			a += replace_word.GetCount()-1;
		}
		
		prev = a;
	}
}



void HotfixReplaceWord(WString& ws) {
	String s = ws.ToString();
	HotfixReplaceWord(s);
	ws = s.ToWString();
}

void HotfixReplaceWord(String& s) {
	ReplaceWord(s, "im", "I'm");
	ReplaceWord(s, "ive", "I've");
	ReplaceWord(s, "ill", "I'll");
	ReplaceWord(s, "id", "I'd");
	ReplaceWord(s, "youre", "you're");
	ReplaceWord(s, "youd", "you'd");
	ReplaceWord(s, "youve", "you've");
	ReplaceWord(s, "youll", "you'll");
	ReplaceWord(s, "hes", "he's");
	ReplaceWord(s, "heve", "he've");
	ReplaceWord(s, "hed", "he'd");
	ReplaceWord(s, "shes", "she's");
	ReplaceWord(s, "sheve", "she've");
	ReplaceWord(s, "shed", "she'd");
	ReplaceWord(s, "theyll", "they'll");
	ReplaceWord(s, "theyve", "they've");
	ReplaceWord(s, "theyre", "they're");
	
	ReplaceWord(s, "arent", "aren't");
	ReplaceWord(s, "aint", "ain't");
	ReplaceWord(s, "didnt", "didn't");
	ReplaceWord(s, "dont", "don't");
	
	ReplaceWord(s, "its", "it's");
	ReplaceWord(s, "itll", "it'll");
	ReplaceWord(s, "itve", "it've");
	ReplaceWord(s, "isnt", "isn't");
	
	ReplaceWord(s, "whats", "what's");
	ReplaceWord(s, "couldnt", "couldn't");
	ReplaceWord(s, "shouldnt", "shouldn't");
	ReplaceWord(s, "theres", "there's");
	ReplaceWord(s, "wasnt", "wasn't");
	ReplaceWord(s, "thats", "that's");
	
	if (0) {
		ReplaceWord(s, "alright", "allright");
		// These change too much
		if (0) {
			ReplaceWord(s, "tryna", "tring to");
			ReplaceWord(s, "aint", "aren't");
			ReplaceWord(s, "gotta", "have to");
			ReplaceWord(s, "wanna", "want to");
			ReplaceWord(s, "em", "them");
			ReplaceWord(s, "ol", "old");
			ReplaceWord(s, "bout", "about");
			ReplaceWord(s, "nunya", "none of your");
			ReplaceWord(s, "thang", "thing");
			ReplaceWord(s, "I'ma", "I'll");
		}
		
		ReplaceWord(s, "tryin", "trying");
		ReplaceWord(s, "fuckin", "fucking");
		ReplaceWord(s, "livin", "living");
		ReplaceWord(s, "lookin", "looking");
		ReplaceWord(s, "prayin", "praying");
		ReplaceWord(s, "rollin", "rolling");
		ReplaceWord(s, "workin", "working");
		ReplaceWord(s, "chargin", "charging");
		ReplaceWord(s, "runnin", "running");
		ReplaceWord(s, "doin", "doing");
		ReplaceWord(s, "judgin", "judging");
		ReplaceWord(s, "blendin", "blending");
		ReplaceWord(s, "gettin", "getting");
		ReplaceWord(s, "talkin", "talking");
		ReplaceWord(s, "changin", "changing");
		ReplaceWord(s, "makin", "making");
		ReplaceWord(s, "retracin", "retracing");
		ReplaceWord(s, "motherfuckin", "motherfucking");
		ReplaceWord(s, "rockin", "rocking");
		ReplaceWord(s, "goin", "going");
		ReplaceWord(s, "frontin", "fronting");
		ReplaceWord(s, "somethin", "something");
		ReplaceWord(s, "playin", "playing");
		ReplaceWord(s, "hittin", "hitting");
		ReplaceWord(s, "movin", "moving");
	}
}


/*const char* ScoreTitles[SCORE_MODE_COUNT][SCORE_ATTR_COUNT] = {
	// Statistical measurements
	{
		"Idea",
		"Emotion",
		"Hook",
		"Share",
		"Value"
	},
	// Human value measurements (meaning)
	{
		"Comedy",
		"Sex",
		"Politics",
		"Love",
		"Social issues"
	}
};

String GetScoreKey(int score_mode, int score_attr) {
	if (!score_mode)
		return "sc(" + IntStr(score_attr) + ")";
	else
		return "sc(" + IntStr(score_mode) + "," + IntStr(score_attr) + ")";
}*/

const char* ScoreTitles[SCORE_COUNT] = {
	// Statistical measurements
	
		"Idea",
		"Emotion",
		"Hook",
		"Share",
		"Value",
	
	// Human value measurements (meaning)
	
		"Comedy",
		"Sex",
		"Politics",
		"Love",
		"Social issues"
	
};

const char* ScoreDescriptions[SCORE_COUNT] = {
	// Statistical measurements
	
		"High like count means that the idea score is high",
		"High comment count means that the emotion score is high",
		"High listen count means that the hook score is high",
		"High share count means that the share score is high",
		"High bookmark count means that the value score is high",
	
	// Human value measurements (meaning)
	
		"People finding the text funny means that the comedy score is high",
		"People finding the text sensual means that the sex score is high",
		"People finding the text thought-provoking means that the politics score is high",
		"People finding the text romantic means that the love score is high",
		"People finding the text impactful means that the social issues score is high"
	
};

String GetScoreTitle(int score) {
	if (score >= 0 && score < SCORE_COUNT)
		return ScoreTitles[score];
	else
		return "";
}

String GetScoreDescription(int score) {
	if (score >= 0 && score < SCORE_COUNT)
		return ScoreDescriptions[score];
	else
		return "";
}

String GetScoreKey(int score) {
	return "sc(" + IntStr(score) + ")";
}




hash_t HexHash(const String& s) {
	const int count = sizeof(hash_t);
	static_assert(count == 8, "64bit supported only (so far)");
	union {
		hash_t out;
		byte b[sizeof(hash_t)];
	};
	int sep = min(count*2, s.GetCount());
	ASSERT(sep % 2 == 0 || sep < 2);
	sep -= sep % 2;
	
	out = 0;
	byte *t = b;
	for(int q = 0; q < sep; q+=2) {
		byte l = s[q+0];
		byte h = s[q+1];
		
		if (l >= '0' && l <= '9') l -= '0';
		else if (l >= 'a' && l <= 'f') l = l - 'a' + 10;
		else l = 10 + l - 'A';
		
		if (h >= '0' && h <= '9') h -= '0';
		else if (h >= 'a' && h <= 'f') h = h - 'a' + 10;
		else h = 10 + h - 'A';
		
		*t++ = l | (h << 4);
	}
	return out;
}

String HashHex(hash_t h) {
	String s;
	s.Reserve(sizeof(hash_t)*2);
	union {
		hash_t in;
		byte b[sizeof(hash_t)];
	};
	in = h;
	int count = sizeof(hash_t);
	byte *t = b;
	for(int i = 0; i < count; i++) {
		byte l = b[i] & 0xF;
		byte h = (b[i] & 0xF0) >> 4;
		
		if (l >= 0 && l <= 9) s.Cat('0' + l);
		else s.Cat('a' + l - 10);
		
		if (h >= 0 && h <= 9) s.Cat('0' + h);
		else s.Cat('a' + h - 10);
	}
	return s;
}

int FindNonEscaped(const String& s, const String& search) {
	int a = 0;
	while (true) {
		a = s.Find(search, a);
		if (a < 0)
			return -1;
		else if (a == 0) {
			return a;
		}
		else {
			char prev = s[a-1];
			if (prev == '\\') {
				if (a >= 2 && s[a-2] == '\\')
					return a;
				a++;
				continue;
			}
			else
				return a;
		}
	}
	return -1;
}

int FindNonEscaped(const String& s, const String& search, int begin) {
	int a = begin;
	while (true) {
		a = s.Find(search, a);
		if (a < 0)
			return -1;
		else if (a == 0) {
			return a;
		}
		else {
			char prev = s[a-1];
			if (prev == '\\') {
				if (a >= 2 && s[a-2] == '\\')
					return a;
				a++;
				continue;
			}
			else
				return a;
		}
	}
	return -1;
}

int FindNonEscaped(const WString& s, const WString& search, int begin) {
	int a = begin;
	while (true) {
		a = s.Find(search, a);
		if (a < 0)
			return -1;
		else if (a == 0) {
			return a;
		}
		else {
			char prev = s[a-1];
			if (prev == '\\') {
				if (a >= 2 && s[a-2] == '\\')
					return a;
				a++;
				continue;
			}
			else
				return a;
		}
	}
	return -1;
}





void SetIndexCursor(ArrayCtrl& arr, int cur) {
	for(int i = 0; i < arr.GetCount(); i++) {
		int idx = arr.Get(i, "IDX");
		if (idx == cur) {
			arr.SetCursor(i);
			break;
		}
	}
}

void FixOffensiveWords(String& s) {
	s.Replace(" nigga ", " brother ");
	s.Replace(" niggas ", " brothers ");
	s.Replace(" nigga's ", " brother's ");
}



MetaPtrs::MetaPtrs() {
	
}




const char* GetLeadWebsiteKey(int leadsite_idx) {
	switch (leadsite_idx) {
		case LEADSITE_TAXI:			return "Taxi";
		case LEADSITE_MUSICXRAY:	return "MusicXray";
		case LEADSITE_SONICBIDS:	return "SonicBids";
		default: return "<error>";
	}
}




String DeHtml(String html, Vector<String>& links) {
	String out;
	int depth = 0;
	String deep;
	for(int i = 0; i < html.GetCount(); i++) {
		int chr = html[i];
		if (chr == '<') {
			if (depth == 0)
				deep.Clear();
			depth++;
		}
		else if (chr == '>') {
			depth--;
			if (depth == 0) {
				int href = deep.Find(" href=\"");
				if (href >= 0) {
					href += 7;
					int end = deep.Find("\"", href);
					if (end >= 0) {
						String addr = deep.Mid(href, end-href);
						links << addr;
					}
				}
			}
		}
		else if (depth == 0) {
			out.Cat(chr);
		}
		else {
			deep.Cat(chr);
		}
	}
	out.Replace("&amp;", "&");
	out.Replace("&quot;", "\"");
	out.Replace("&#39;", "'");
	
	out = TrimBoth(out);
	
	/*for(int i = 0; i < out.GetCount()-1; i++) {
		int chr0 = out[i];
		int chr1 = out[i+1];
		if (chr0 >= 'a' && chr0 <= 'z' &&
			chr1 >= 'A' && chr1 <= 'Z') {
			out.Insert(i+1, '\n');
		}
	}*/
	
	return out;
}

bool IsAllUpper(const String& s) {
	for(int i = 0; i < s.GetCount(); i++) {
		int chr = s[i];
		if (chr >= 'A' && chr <= 'Z')
			continue;
		if (chr == '\'' || chr == '-' || chr == '/' || chr == ',' || chr == '&')
			continue;
		return false;
	}
	return !s.IsEmpty();
}



String __global_proxy;
void SetGlobalProxy(String uri) {
	__global_proxy = uri;
}

String GetGlobalProxy() {
	return __global_proxy;
}












const Vector<String>& GetElements() {
	static Vector<String> v;
	ONCELOCK {
		v.Add("allegory");
		v.Add("bittersweet ending");
		v.Add("call to action");
		v.Add("character development");
		v.Add("climax");
		v.Add("conclusion");
		v.Add("conflict");
		v.Add("crisis");
		v.Add("emotional impact");
		v.Add("exposition");
		v.Add("falling action");
		v.Add("foils");
		v.Add("fourth wall");
		v.Add("happy ending");
		v.Add("high stakes obstacle");
		v.Add("intensity");
		v.Add("irony");
		v.Add("iteration");
		v.Add("journey/quest");
		v.Add("metaphor");
		v.Add("moral dilemma");
		v.Add("notion of self");
		v.Add("pacing");
		v.Add("plot twist");
		v.Add("repetition");
		v.Add("resolution");
		v.Add("rising action");
		v.Add("rock bottom");
		v.Add("setting");
		v.Add("structure");
		v.Add("suspense");
		v.Add("symbolism");
		v.Add("tension");
		v.Add("theme");
		v.Add("tone");
		v.Add("tragedy");
	}
	return v;
}


String AppendUnixFileName(String a, String b) {
	if (a.GetCount() && a[a.GetCount()-1] == '/')
		a = a.Left(a.GetCount()-1);
	if (b.GetCount() && b[0] == '/')
		b = b.Mid(1);
	return a + "/" + b;
}




ValueMap& ValueToMap(Value& val) {
	dword type = val.GetType();
	if (type != VALUEMAP_V)
		val = ValueMap();
	return *(ValueMap*)&val; // Illegal, but works -> better than crash in release mode
}

ValueArray& ValueToArray(Value& val) {
	dword type = val.GetType();
	if (type != VALUEARRAY_V)
		val = ValueArray();
	return *(ValueArray*)&val; // Illegal, but works -> better than crash in release mode
}



String KeyToName(String s) {
	s = ToLower(s);
	String o;
	bool upper = true;
	for(int i = 0; i < s.GetCount(); i++) {
		int chr = s[i];
		if (chr == '_') {
			upper = true;
			o.Cat(' ');
			continue;
		}
		if (upper && chr >= 'a' && chr <= 'z')
			chr = ToUpper(chr);
		upper = false;
		o.Cat(chr);
	}
	return o;
}

String StringToName(String s) {
	s = ToLower(s);
	String o;
	bool upper = true;
	for(int i = 0; i < s.GetCount(); i++) {
		int chr = s[i];
		if (chr == ' ') {
			upper = true;
			continue;
		}
		if (upper && chr >= 'a' && chr <= 'z')
			chr = ToUpper(chr);
		upper = false;
		o.Cat(chr);
	}
	return o;
}


END_TEXTLIB_NAMESPACE

