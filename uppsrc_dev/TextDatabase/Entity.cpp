#include "TextDatabase.h"


BEGIN_TEXTLIB_NAMESPACE


void Entity::Jsonize(JsonIO& json) {
	json
		("name", name)
		("data", data)
		;
	if (json.IsStoring()) {
		Vector<String> names;
		for (Snapshot& r : snaps) {r.Store(*this); names.Add(r.file_title);}
		json("snaps", names);
		
	}
	if (json.IsLoading()) {
		snaps.Clear();
		Vector<String> names;
		json("snaps", names);
		for (String n : names) snaps.Add().LoadTitle(*this, n);
	}
}

void Entity::Store() {
	String dir = AppendFileName(GetAppModeDatabase().GetEntitiesDir(), file_title);
	RealizeDirectory(dir);
	String json_path = dir + DIR_SEPS + "db.json";
	StoreAsJsonFileStandard(*this, json_path, true);
	
	StoreScript();
}

bool Entity::FileExists(const String& title) {
	String dir = AppendFileName(GetAppModeDatabase().GetEntitiesDir(), title);
	String json_path = dir + DIR_SEPS + "db.json";
	return UPP::FileExists(json_path);
}

void Entity::LoadTitle(String title) {
	String dir = AppendFileName(GetAppModeDatabase().GetEntitiesDir(), title);
	file_title = title;
	String json_path = dir + DIR_SEPS + "db.json";
	LoadFromJsonFileStandard(*this, json_path);
	
	LoadScript();
}

Snapshot& Entity::GetAddSnapshot(String name) {
	String file_title = MakeTitle(name);
	for(Snapshot& snap : snaps) {
		if (snap.file_title == file_title)
			return snap;
	}
	Snapshot& snap = snaps.Add();
	snap.file_title = file_title;
	snap.title = name;
	return snap;
}

void Entity::StoreScript() {
	for (auto& l : scripts) {
		l.Store(*this);
	}
}

void Entity::LoadScript() {
	TextDatabase& db = GetAppModeDatabase();
	FindFile ff(AppendFileName(GetScriptDir(), "*.json"));
	do {
		if (!ff.IsFile())
			continue;
		String path = ff.GetPath();
		String title = GetFileTitle(path);
		String name = GetFileName(path);
		if (GetFileExt(name) != ".json")
			continue;
		
		{
			scripts.Add()
				.LoadTitle(*this, title); // TODO avoid duplicate loading
		}
	}
	while (ff.Next());
	
}

String Entity::GetScriptDir() const {
	ASSERT(!file_title.IsEmpty());
	return
		MetaDatabase::GetDirectory() + DIR_SEPS +
		MetaDatabase::Single().share + DIR_SEPS +
		"code" + DIR_SEPS + "scripts" + DIR_SEPS + file_title + DIR_SEPS;
}

int Entity::FindScript(const String& scripts_file_title) const {
	for(int i = 0; i < scripts.GetCount(); i++) {
		const Script& lyr = scripts[i];
		if (lyr.file_title == scripts_file_title) {
			return i;
		}
	}
	return -1;
}

Script& Entity::GetAddScript(String name) {
	String file_title = MakeTitle(name);
	for(Script& s : scripts) {
		if (s.file_title == file_title)
			return s;
	}
	Script& s = scripts.Add();
	s.file_title = file_title;
	return s;
}

int Concept::FindStory(hash_t h) const {
	for(int i = 0; i < stories.GetCount(); i++)
		if (stories[i].hash == h)
			return i;
	return -1;
}

ConceptStory& Concept::GetAddStory(hash_t h) {
	ASSERT(h != 0);
	for(auto& s : stories)
		if (s.hash == h)
			return s;
	auto& s = stories.Add();
	s.hash = h;
	return s;
}

int ConceptStory::FindElement(const String& key) const {
	int i = 0;
	for (const auto& e : elements) {
		if (e.key == key)
			return i;
		i++;
	}
	return -1;
}

int ConceptStory::FindImprovedElement(const String& key) const {
	int i = 0;
	for (const auto& e : ELEMENTS_VAR) {
		if (e.key == key)
			return i;
		i++;
	}
	return -1;
}

double ConceptStory::Element::GetAverageScore() const {
	double score_sum = 0;
	int score_count = 0;
	for(int i = 0; i < SCORE_COUNT; i++) {
		int score = scores[i];
		score_sum += score;
		score_count++;
	}
	double score = score_sum / score_count;
	return score;
}

double ConceptStory::AvSingleScore(int i) const {
	ASSERT(i >= 0 && i < SCORE_COUNT);
	if (ELEMENTS_VAR.IsEmpty()) return 0;
	int sum = 0;
	for (const auto& el : ELEMENTS_VAR)
		sum += el.scores[i];
	return sum / (double)ELEMENTS_VAR.GetCount();
}

Color ConceptStory::GetAverageColor() const {
	if (ELEMENTS_VAR.IsEmpty()) return Color(128,128,128);
	int clr[3] = {0,0,0};
	for (const auto& el : ELEMENTS_VAR) {
		clr[0] += el.clr.GetR();
		clr[1] += el.clr.GetG();
		clr[2] += el.clr.GetB();
	}
	int c = ELEMENTS_VAR.GetCount();
	return Color(clr[0] / c, clr[1] / c, clr[2] / c);
}

double ConceptStory::GetAverageScore() const {
	if (ELEMENTS_VAR.IsEmpty()) return 0;
	int sum = 0;
	for (const auto& el : ELEMENTS_VAR)
		sum += el.GetAverageScore();
	return sum / (double)ELEMENTS_VAR.GetCount();
}
bool ConceptStory::operator()(const ConceptStory& a, const ConceptStory& b) const {
	return a.GetAverageScore() > b.GetAverageScore();
}

END_TEXTLIB_NAMESPACE

