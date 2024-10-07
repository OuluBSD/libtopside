#ifndef _TextDatabase_SourceData_h_
#define _TextDatabase_SourceData_h_


BEGIN_TEXTLIB_NAMESPACE


struct ScriptDataset : Moveable<ScriptDataset> {
	String name;
	String text;
};

struct EntityDataset : Moveable<EntityDataset> {
	String name;
	Vector<ScriptDataset> scripts;
};

struct EntityAnalysis : Moveable<EntityAnalysis> {
	Vector<String> genres;
	
	void Serialize(Stream& s) {s % genres;}
	void Jsonize(JsonIO& json) {
		json
			("genres", genres)
			;
	}
};



struct Token : Moveable<Token> {
	mutable int word_ = -1;
	
	String StoreToString() {
		StringDumper d;
		d % word_;
		return d;
	}
	void LoadFromString(const String& s) {
		StringParser p(s);
		p % word_;
	}
};

struct TokenText : Moveable<TokenText> {
	Vector<int> tokens;
	int virtual_phrase = -1;
	
	String StoreToString() {
		StringDumper d;
		d % tokens.GetCount();
		for (int t : tokens)
			d % t;
		d % virtual_phrase;
		return d;
	}
	void LoadFromString(const String& s) {
		StringParser p(s);
		int tc = 0;
		p % tc;
		tokens.SetCount(tc);
		for (int& t : tokens)
			p % t;
		p % virtual_phrase;
	}
};

struct ExportWord : Moveable<ExportWord> {
	static const int MAX_CLASS_COUNT = 8;
	
	String txt;
	int count = 0;
	Color clr;
	int class_count = 0;
	int classes[MAX_CLASS_COUNT];
	int link = -1;
	
	String StoreToString() {
		StringDumper d;
		d % txt % count % clr % class_count;
		for(int i = 0; i < class_count; i++)
			d % classes[i];
		d % link;
		return d;
	}
	void LoadFromString(const String& s) {
		StringParser p(s);
		p % txt % count % clr % class_count;
		for(int i = 0; i < class_count; i++)
			p % classes[i];
		p % link;
	}
	void CopyFrom(const ExportWord& wa, bool reset) {
		txt.Clear();
		clr = wa.clr;
		class_count = wa.class_count;
		for(int i = 0; i < class_count; i++)
			classes[i] = wa.classes[i];
		if (reset) {
			count = 0;
			link = -1;
		}
	}
	
};

struct PhrasePart : Moveable<PhrasePart> {
	Vector<int> words;
	int tt_i = -1;
	int virtual_phrase_part = -1;
	int attr = -1;
	int el_i = -1;
	Color clr = Black();
	Vector<int> actions;
	Vector<int> typecasts;
	Vector<int> contrasts;
	int scores[SCORE_COUNT] = {0,0,0,0,0,0,0,0,0,0};
	
	bool HasScores() const {
		for(int i = 0; i < SCORE_COUNT; i++)
			if (scores[i] != 0)
				return true;
		return false;
	}
	String StoreToString() {
		StringDumper d;
		d % words.GetCount();
		for (int w_i : words)
			d % w_i;
		d % tt_i % virtual_phrase_part % attr % clr;
		d % actions.GetCount();
		for (int ah_i : actions)
			d % ah_i;
		for(int i = 0; i < SCORE_COUNT; i++)
			d % scores[i];
		d % typecasts.GetCount();
		for (int tc_i : typecasts)
			d % tc_i;
		d % contrasts.GetCount();
		for (int i : contrasts)
			d % i;
		d % el_i;
		return d;
	}
	void LoadFromString(const String& s) {
		StringParser p(s);
		int tc = 0;
		p % tc;
		words.SetCount(tc);
		for (int& w_i : words)
			p % w_i;
		p % tt_i % virtual_phrase_part;
		p % attr % clr;
		int ac = 0;
		p % ac;
		actions.SetCount(ac);
		for (int& ah_i : actions)
			p % ah_i;
		for(int i = 0; i < SCORE_COUNT; i++)
			p % scores[i];
		p % tc;
		if (tc < 0 || tc > 60) return;
		typecasts.SetCount(tc);
		for (int& tc_i : typecasts)
			p % tc_i;
		p % tc;
		if (tc < 0 || tc > 60) return;
		contrasts.SetCount(tc);
		for (int& tc_i : contrasts)
			p % tc_i;
		p % el_i;
	}
	
	hash_t GetHashValue() const {
		CombineHash c;
		for (int w_i : words)
			c.Do(w_i).Put(1);
		return c;
	}
};

struct ExportAttr : Moveable<ExportAttr> {
	int simple_attr = -1, unused = -1;
	int positive = -1, link = -1;
	int count = 0;
	
	String StoreToString() {
		StringDumper d;
		d % simple_attr % unused % positive % link % count;
		return d;
	}
	void LoadFromString(const String& s) {
		StringParser p(s);
		p % simple_attr % unused % positive % link % count;
		positive = min(1, max(0, positive));
	}
	
};

struct ExportAction : Moveable<ExportAction> {
	int attr = -1;
	Color clr;
	int count = 0;
	
	String StoreToString() {
		StringDumper d;
		d % attr % clr % count;
		return d;
	}
	void LoadFromString(const String& s) {
		StringParser p(s);
		p % attr % clr % count;
	}
	
};

struct DatasetAnalysis;

struct DatasetAnalysis {
	MapFile<String,Token> tokens;
	MapFile<hash_t,TokenText> token_texts;
	IndexFile word_classes;
	MapFile<String,ExportWord> words;
	MapFile<hash_t,PhrasePart> phrase_parts;
	IndexFile struct_part_types;
	IndexFile struct_types;
	IndexFile element_keys;
	MapFile<AttrHeader,ExportAttr> attrs;
	MapFile<ActionHeader,ExportAction> actions;
	MapFile<String,String> diagnostics;
	
	
	DatasetAnalysis();
	DatasetAnalysis(DatasetAnalysis&) {}
	DatasetAnalysis(DatasetAnalysis&& o) {LOG("warning: TODO: DatasetAnalysis(DatasetAnalysis&& o)");}
	void Load();
	String GetTokenTextString(const TokenText& txt) const;
	String GetTokenTypeString(const TokenText& txt) const;
	String GetWordString(const Vector<int>& words) const;
	WString GetWordPronounciation(const Vector<int>& words) const;
	String GetTypeString(const Vector<int>& word_classes) const;
	String GetActionString(const Vector<int>& actions) const;
	String GetScriptDump(int i) const;
	String GetScriptDump(DatasetAnalysis& da, int i) const;
	VectorMap<int,int> GetSortedElements();
	VectorMap<int,int> GetSortedElementsOfPhraseParts();
	
	void Jsonize(JsonIO& json) {}
	void Serialize(Stream& s) {}
	
};

struct SourceDataAnalysis {
	DatasetAnalysis dataset;
	VectorMap<String, EntityAnalysis> entities;
	
	void Jsonize(JsonIO& json) {
		if (json.IsLoading()) {
			ArrayMap<String, DatasetAnalysis> datasets;
			json
				("datasets", datasets)
				("entities", entities)
			;
			int i = datasets.Find("en");
			if (i >= 0) {
				byte tmp[sizeof(dataset)];
				memcpy(tmp, &datasets[i], sizeof(dataset));
				memcpy(&datasets[i], &dataset, sizeof(dataset));
				memcpy(&dataset, tmp, sizeof(dataset));
			}
			else {
				json("dataset", dataset);
			}
		}
		else {
			json("dataset", dataset)
				("entities", entities);
		}
	}
	
	
	void Serialize(Stream& s) {
		s % dataset % entities;
	}
	void StoreJson();
	void LoadJson();
	void Store();
	void Load();
};

struct SourceData {
	// Binary data
	Vector<EntityDataset> entities;
	
	SourceDataAnalysis a;
	
	
	SourceData();
	bool IsEmpty() const {return entities.IsEmpty();}
	
};


END_TEXTLIB_NAMESPACE


#endif
