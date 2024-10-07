#ifndef _TextDatabase_Entity_h_
#define _TextDatabase_Entity_h_


BEGIN_TEXTLIB_NAMESPACE


#define USE_IMPROVED_ELEMENTS 0

#if USE_IMPROVED_ELEMENTS
	#define ELEMENTS_VAR	improved_elements
#else
	#define ELEMENTS_VAR	elements
#endif

struct ConceptStory : Moveable<ConceptStory> {
	struct Element : Moveable<Element> {
		String key, value;
		Color clr;
		byte scores[SCORE_COUNT] = {0,0,0,0,0, 0,0,0,0,0};
		void Serialize(Stream& s) {s % key % value % clr; for(int i = 0; i < SCORE_COUNT; i++) s % scores[i];}
		void Jsonize(JsonIO& json) {json("k",key)("v",value)("clr",clr); for(int i = 0; i < SCORE_COUNT; i++) json("s" + IntStr(i),scores[i]);}
		void ResetScore() {memset(scores, 0, sizeof(scores));}
		double GetAverageScore() const;
	};
	
	hash_t hash = 0;
	String desc;
	Vector<Element> elements;
	#if USE_IMPROVED_ELEMENTS
	Vector<Element> improved_elements;
	#endif
	int src = 0;
	int typeclass = -1;
	int content = -1;
	
	int FindElement(const String& key) const;
	int FindImprovedElement(const String& key) const;
	void Serialize(Stream& s) {
		s % hash % desc % elements % src;
		#if USE_IMPROVED_ELEMENTS
		s % improved_elements;
		#endif
	}
	void Jsonize(JsonIO& json) {
		json
			("hash", (int64&)hash)
			("desc", desc)
			("elements", elements)
			("src", src)
			("typeclass", typeclass)
			("content", content)
			;
		#if USE_IMPROVED_ELEMENTS
		json("improved_elements", improved_elements);
		#endif
	}
	
	double AvSingleScore(int i) const;
	Color GetAverageColor() const;
	double GetAverageScore() const;
	bool operator()(const ConceptStory& a, const ConceptStory& b) const;
	
};

struct Concept {
	int64 belief_uniq = 0;
	String name;
	int snap_rev = -1;
	Time created;
	Vector<ConceptStory> stories;
	
	int FindStory(hash_t h) const;
	ConceptStory& GetAddStory(hash_t h);
	void Serialize(Stream& s) {
		s % belief_uniq % name % snap_rev % created % stories;
	}
	void Jsonize(JsonIO& json) {
		json
			("belief_uniq", belief_uniq)
			("name", name)
			("snap_rev", snap_rev)
			("created", created)
			("stories", stories)
			;
	}
};


struct Entity :
	DataFile
{
	Profile* profile = 0;
	
	// Public
	String name;
	VectorMap<String,String>	data;
	
	// Public (separate files)
	Array<Script>		scripts;
	Array<Snapshot>		snaps;
	
	void Clear() {
		name.Clear();
		data.Clear();
	}
	void Store();
	void StoreScript();
	void LoadScript();
	void LoadTitle(String title);
	String GetScriptDir() const;
	Snapshot& GetAddSnapshot(String name);
	Array<Snapshot>& GetSub() {return snaps;}
	const Array<Snapshot>& GetSub() const {return snaps;}
	void Serialize(Stream& s) {
		s	% name
			% snaps
			% data
			;
	}
	void Jsonize(JsonIO& json);
	
	bool operator()(const Entity& a, const Entity& b) const {
		return a.name < b.name;
	}
	
	int FindScript(const String& scripts_file_title) const;
	Script& GetAddScript(String name);
	
	static bool FileExists(const String& title);
};


END_TEXTLIB_NAMESPACE


#endif
