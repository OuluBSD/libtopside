#ifndef _TextDatabase_Snapshot_h_
#define _TextDatabase_Snapshot_h_


BEGIN_TEXTLIB_NAMESPACE


enum {
	SNAPANAL_LYRICS_SUMMARY,
	SNAPANAL_LYRICS_PSYCHOANALYSIS,
	SNAPANAL_LYRICS_SOCIAL_PSYCHOLOGY_ANALYSIS,
	SNAPANAL_MARKET_VALUE_ANALYSIS,
	SNAPANAL_MARKETING_SUGGESTION,
	SNAPANAL_ART_SUGGESTION,
	SNAPANAL_COVER_SUGGESTION,
	
	SNAPANAL_COUNT,
};

inline String GetSnapshotAnalysisKey(int i) {
	switch (i) {
		case SNAPANAL_LYRICS_SUMMARY: return "Lyrics summary";
		case SNAPANAL_LYRICS_PSYCHOANALYSIS: return "Lyrics psychoanalysis";
		case SNAPANAL_LYRICS_SOCIAL_PSYCHOLOGY_ANALYSIS: return "Lyrics social psychology analysis";
		case SNAPANAL_MARKET_VALUE_ANALYSIS: return "Market value analysis";
		case SNAPANAL_MARKETING_SUGGESTION: return "Marketing suggestion";
		case SNAPANAL_ART_SUGGESTION: return "Art suggestion";
		case SNAPANAL_COVER_SUGGESTION: return "Cover image suggestion";
		default: return "<error>";
	}
}

struct Snapshot :
	DataFile
{
	// Public
	String						title;
	Date						date;
	VectorMap<String,String>	data;
	
	// Public (separate files)
	Array<Component>			components;
	
	Entity*						entity = 0;
	
	
	void Store(Entity& e);
	void LoadTitle(Entity& e, String title);
	Component& GetAddComponent(String name);
	//Component& RealizeReversed(Component& s);
	void Serialize(Stream& s) {
		s	% title
			% date
			% data
			% components;
	}
	void Jsonize(JsonIO& json) {
		json
			("title", title)
			("date", date)
			("data", data)
			;
		if (json.IsStoring()) {
			{
				Vector<String> names;
				for (Component& s : components) {s.Store(*this); names.Add(s.file_title);}
				json("comps", names);
			}
		}
		if (json.IsLoading()) {
			{
				components.Clear();
				Vector<String> names;
				json("comps", names);
				for (String n : names) components.Add().LoadTitle(*this, n);
			}
		}
	}
	
	Array<Component>& GetSub() {return components;}
	const Array<Component>& GetSub() const {return components;}
	bool operator()(const Snapshot& a, const Snapshot& b) const {
		if (a.date != b.date) return a.date < b.date;
		return a.title < b.title;
	}
	
	
	
};


END_TEXTLIB_NAMESPACE


#endif
