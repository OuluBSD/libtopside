#include "TextDatabase.h"


BEGIN_TEXTLIB_NAMESPACE


DatabaseBrowser::DatabaseBrowser() {
	Load();
}
	
#define ITEM(x) case x: return KeyToName(#x);
String DatabaseBrowser::GetTypeString(ColumnType t) {
	switch (t) {
		ITEM(ATTR_GROUP)
		ITEM(ATTR_VALUE)
		ITEM(COLOR)
		ITEM(ACTION)
		ITEM(ACTION_ARG)
		ITEM(ELEMENT)
		ITEM(TYPECLASS)
		ITEM(CONTENT)
		default: return "ERROR";
	}
}
#undef ITEM

String DatabaseBrowser::GetModeKey(int i) {
	switch (i) {
		#define MODE(x) case x: return #x;
		DBROWSER_MODE_LIST
		#undef MODE
		default: return "";
	}
}

String DatabaseBrowser::GetModeString(int i) {
	switch (i) {
		#define MODE(x) case x: return KeyToName(#x);
		DBROWSER_MODE_LIST
		#undef MODE
		default: return "ERROR";
	}
}



int DatabaseBrowser::FindMode(hash_t h) {
	for(int i = 0; i < MODE_COUNT; i++) {
		if (GetModeHash(i) == h)
			return i;
	}
	return -1;
}

hash_t DatabaseBrowser::GetModeHash(int mode) {
	if (mode < 0 || mode >= MODE_COUNT) return 0;
	return GetModeString(mode).GetHashValue();
}

void DatabaseBrowser::SetMode(int i) {
	if (i == mode)
		return;
	mode = i;
	for(int i = 0; i < TYPE_COUNT; i++)
		items[i].Clear();
	phrase_parts.Clear();
	for(int i = 0; i < TYPE_COUNT; i++)
		order[i] = INVALID;
	int o = 0;
	Vector<String> parts = Split(GetModeKey(mode), "_");
	for (String& part : parts) {
		if      (part == "ELEMENT")		{order[o++] = ELEMENT;}
		else if (part == "ATTR")		{order[o++] = ATTR_GROUP; order[o++] = ATTR_VALUE;}
		else if (part == "COLOR")		{order[o++] = COLOR;}
		else if (part == "ACTION")		{order[o++] = ACTION; order[o++] = ACTION_ARG;}
		else if (part == "CONTENT")		{order[o++] = CONTENT;}
		else if (part == "TYPECLASS")	{order[o++] = TYPECLASS;}
		else TODO;
	}
	
	Init();
}

DatabaseBrowser::ColumnType DatabaseBrowser::GetCur(int cursor_i) const {
	ASSERT(cursor_i >= 0 && cursor_i < TYPE_COUNT);
	return order[cursor_i];
}

bool DatabaseBrowser::IsSub(int cur, int cursor_i) const {
	return GetCur(cursor_i) > cur;
}

void DatabaseBrowser::Init() {
	uniq_acts.Clear();
	color_counts.Clear();
	for(int i = 0; i < TYPE_COUNT; i++)
		cursor[i] = 0;
	
	ResetCursor();
}

void DatabaseBrowser::ResetCursor() {
	ResetCursor(-1, INVALID);
}

void DatabaseBrowser::SetAll(hash_t sorter, const String& element, const AttrHeader& attr, int clr, const ActionHeader& act, int tc_i, int con_i) {
	SetInitialData();
	
	if (sorter) {
		int m = FindMode(sorter);
		if (m >= 0)
			SetMode(m);
	}
	
	for(int i = 0; i < TYPE_COUNT; i++) {
		auto t = order[i];
		if (t == INVALID)
			break;
		
		FillItems(t);
		
		int& tgt = history.GetAdd(GetHash(i), 0);
		tgt = 0;
		
		switch (t) {
			case ATTR_GROUP: {
				const auto& attr_groups = Get(ATTR_GROUP);
				String attr_group = attr.IsEmpty() ? "All" : attr.group;
				for(int i = 0; i < attr_groups.GetCount(); i++) {
					const auto& at = attr_groups[i];
					if (at.str == attr_group) {
						tgt = i;
						break;
					}
				}
				break;
			}
			case ATTR_VALUE: {
				const auto& attr_values = Get(ATTR_VALUE);
				String attr_value = attr.IsEmpty() ? "All" : attr.value;
				for(int i = 0; i < attr_values.GetCount(); i++) {
					const auto& at = attr_values[i];
					if (at.str == attr_value) {
						tgt = i;
						break;
					}
				}
				break;
			}
			case COLOR: {
				const auto& colors = Get(COLOR);
				for(int i = 0; i < colors.GetCount(); i++) {
					if (colors[i].idx == clr) {
						tgt = i;
						break;
					}
				}
				break;
			}
			case ACTION: {
				const auto& actions = Get(ACTION);
				String action = act.IsEmpty() ? "All" : act.action;
				for(int i = 0; i < actions.GetCount(); i++) {
					if (actions[i].str == action) {
						tgt = i;
						break;
					}
				}
				break;
			}
			case ACTION_ARG: {
				const auto& args = Get(ACTION_ARG);
				String arg = act.IsEmpty() ? "All" : act.arg;
				for(int i = 0; i < args.GetCount(); i++) {
					if (args[i].str == arg) {
						tgt = i;
						break;
					}
				}
				break;
			}
			case ELEMENT: {
				const auto& args = Get(ELEMENT);
				String str = element.IsEmpty() ? "All" : element;
				for(int i = 0; i < args.GetCount(); i++) {
					if (args[i].str == str) {
						tgt = i;
						break;
					}
				}
				break;
			}
			case TYPECLASS: {
				const auto& args = Get(TYPECLASS);
				for(int i = 0; i < args.GetCount(); i++) {
					if (args[i].idx == tc_i) {
						tgt = i;
						break;
					}
				}
				break;
			}
			case CONTENT: {
				const auto& args = Get(CONTENT);
				for(int i = 0; i < args.GetCount(); i++) {
					if (args[i].idx == con_i) {
						tgt = i;
						break;
					}
				}
				break;
			}
			default: break;
		}
		
		cursor[i] = tgt;
		
		FilterData(t);
	}
}

void DatabaseBrowser::Update() {
	
}

hash_t DatabaseBrowser::GetHash(int columns) const {
	CombineHash ch;
	ch.Do(mode);
	for(int i = 0; i < TYPE_COUNT; i++)
		ch.Do(i < columns ? cursor[i] : -1);
	return ch;
}

void DatabaseBrowser::Store() {
	String file = ConfigFile("DatabaseBrowser.bin");
	StoreToFile(*this, file);
}

void DatabaseBrowser::Load() {
	String file = ConfigFile("DatabaseBrowser.bin");
	LoadFromFile(*this, file);
}

void DatabaseBrowser::SortBy(int i) {
	TextDatabase& db = GetDatabase();
	SourceData& sd = db.src_data;
	SourceDataAnalysis& sda = db.src_data.a;
	DatasetAnalysis& da = sda.dataset;
	
	if (i == 0) {
		struct Sorter {
			MapFile<hash_t, PhrasePart>* phrase_parts;
			bool operator()(int a, int b) const {
				int at = 0, bt = 0;
				PhrasePart& pa = (*phrase_parts)[a];
				PhrasePart& pb = (*phrase_parts)[b];
				for(int i = 0; i < SCORE_COUNT; i++) {
					at += pa.scores[i];
					bt += pb.scores[i];
				}
				return at > bt;
			}
		} s;
		s.phrase_parts = &da.phrase_parts;
		Sort(phrase_parts, s);
	}
	else if (i >= 1 && i < SCORE_COUNT+1) {
		i--;
		struct Sorter {
			MapFile<hash_t, PhrasePart>* phrase_parts;
			int i;
			bool operator()(int a, int b) const {
				return (*phrase_parts)[a].scores[i] > (*phrase_parts)[b].scores[i];
			}
		} s;
		s.i = i;
		s.phrase_parts = &da.phrase_parts;
		Sort(phrase_parts, s);
	}
	
	sorting = i;
}

TextDatabase& DatabaseBrowser::GetDatabase() {
	return ctrl->GetDatabase();
}

DatabaseBrowser& DatabaseBrowser::Single() {
	static DatabaseBrowser db;
	return db;
}

int DatabaseBrowser::FindAction(const String& s) {
	const auto& actions = Get(ACTION);
	for(int i = 0; i < actions.GetCount(); i++) {
		if (actions[i].str == s)
			return i;
	}
	return 0; // return "All", which is first
}

int DatabaseBrowser::FindArg(const String& s) {
	const auto& args = Get(ACTION_ARG);
	for(int i = 0; i < args.GetCount(); i++) {
		if (args[i].str == s)
			return i;
	}
	return 0; // return "All", which is first
}

Vector<DatabaseBrowser::Item>& DatabaseBrowser::Get(ColumnType t) {
	for(int i = 0; i < TYPE_COUNT; i++) {
		if (order[i] == t)
			return items[i];
	}
	static Vector<DatabaseBrowser::Item> empty;
	return empty;
}

const Vector<DatabaseBrowser::Item>& DatabaseBrowser::Get(ColumnType t) const {
	for(int i = 0; i < TYPE_COUNT; i++) {
		if (order[i] == t)
			return items[i];
	}
	ASSERT_(0, "Invalid ColumnType");
	return items[0];
}

bool DatabaseBrowser::IsFirstInOrder(ColumnType t) const {
	return order[0] == t;
}

int DatabaseBrowser::GetColumnCursor(ColumnType t) const {
	for(int i = 0; i < TYPE_COUNT; i++) {
		if (order[i] == t)
			return cursor[i];
	}
	return -1;
}

int DatabaseBrowser::GetColumnOrder(ColumnType t) const {
	for(int i = 0; i < TYPE_COUNT; i++)
		if (order[i] == t)
			return i;
	return -1;
}


END_TEXTLIB_NAMESPACE

