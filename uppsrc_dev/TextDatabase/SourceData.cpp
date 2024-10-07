#include "TextDatabase.h"



BEGIN_TEXTLIB_NAMESPACE


SourceData::SourceData() {
	
}



void SourceDataAnalysis::Store() {
	StoreToFile(*this, ConfigFile("CompData_Analysis.bin"));
	StoreJson();
}

void SourceDataAnalysis::Load() {
	LoadFromFile(*this, ConfigFile("CompData_Analysis.bin"));
	LoadJson();
	
	SourceData& sd = GetAppModeDatabase().src_data;

	auto& ds = sd.a.dataset;
	ds.Load();
}

void SourceDataAnalysis::StoreJson() {
	String& dir = MetaDatabase::Single().dir;
	StoreAsJsonFileStandard(*this, ConfigFile("CompData.json"), false);
}

void SourceDataAnalysis::LoadJson() {
	#if 0
	DatasetAnalysis da;
	LoadFromJsonFileStandard(da, ConfigFile(__Comp + "Data.json"));
	
	SourceData& sd = GetAppModeDatabase().src_data;
	{
		DatasetAnalysis& tgt = datasets.GetAdd(sd.GetKey(j));
		
		for(int k = 0; k < da.entities.GetCount(); k++) {
			String name0 = da.entities.GetKey(k);
			if (name0.IsEmpty()) continue;
			
			for(int i = 0; i < sd.entities.GetCount(); i++) {
				String name1 = sd.entities[i].name;
				if (name0 == name1) {
					Swap(da.entities[k], tgt.entities.Add(name0));
					break;
				}
			}
		}
	}
	#else
	String& dir = MetaDatabase::Single().dir;
	LoadFromJsonFileStandard(*this, ConfigFile("CompData.json"));
	#endif
}


#if 0

String ScriptAnalysis::AsString() const {
	String s;
	s << "Phrase:\n";
	for (const ScriptAnalysis::Phrase& p : phrases) {
		s << "\"" << p.phrase << "\": " << p.group << ": " << p.value << ": RGB(" << p.clr.GetR() << ", " << p.clr.GetG() << ", " << p.clr.GetB() << ")\n";
	}
	s << "\n\n";
	
	s << "Positive roles:\n";
	for (const Vector<ScriptAnalysis::Role>& v : positive_roles) {
		s << "- ";
		int j = 0;
		for (const ScriptAnalysis::Role& r : v) {
			if (j++) s << ", ";
			s << r.group << "/" << r.value << ": " << r.percent << "\%";
		}
		s << "\n";
	}
	s << "\n\n";
	
	s << "Negative roles:\n";
	for (const Vector<ScriptAnalysis::Role>& v : negative_roles) {
		s << "- ";
		int j = 0;
		for (const ScriptAnalysis::Role& r : v) {
			if (j++) s << ", ";
			s << r.group << "/" << r.value << ": " << r.percent << "\%";
		}
		s << "\n";
	}
	s << "\n\n";
	
	s << "Word groups:\n";
	for(int i = 0; i < word_groups.GetCount(); i++) {
		String key = word_groups.GetKey(i);
		s << "- " << key << ": ";
		const auto& v = word_groups[i];
		for(int j = 0; j < v.GetCount(); j++) {
			if (j) s << ", ";
			s << v[j];
		}
		s << "\n";
	}
	s << "\n\n";
	
	s << "Rhyme locations:\n";
	for(int i = 0; i < rhyme_locations.GetCount(); i++) {
		const RhymeLocationLine& l = rhyme_locations[i];
		for(int j = 0; j < l.words.GetCount(); j++) {
			if (j) s << " ";
			bool b = j < l.rhyming.GetCount() ? l.rhyming[j] : false;
			if (b) s << "(";
			s << l.words[j];
			if (b) s << ")";
		}
		s << "\n";
	}
	
	return s;
}

String TemplatePhrase::GetText() const {
	String s;
	for (const String& p : parts) {
		if (p == ",")
			s << ",";
		else {
			if (s.GetCount())
				s << " ";
			s << p;
		}
	}
	return s;
}

String ActionPhrase::GetActionText() const {
	String l;
	for (const auto& arg : actions) {
		if (!l.IsEmpty()) l << " + ";
		l << arg.action << "(" << arg.arg << ")";
	}
	return l;
}

double GetActionMatching(const Vector<ActionHeader>& a, const Vector<ActionHeader>& b) {
	if (!a.GetCount()) return 0;
	int partial_matches = 0, full_matches = 0;
	for (const ActionHeader& aa : a) {
		for (const ActionHeader& bb : b) {
			if (aa.action == bb.action) {
				partial_matches++;
				if (aa.arg == bb.arg) {
					full_matches++;
				}
			}
		}
	}
	//int max_matches = min(a.GetCount(), b.GetCount());
	int max_matches = a.GetCount();
	/*double perc0 = (double)partial_matches / (double)max_matches;
	double perc1 = (double)full_matches / (double)max_matches;
	double perc = (perc0 + perc1) * 0.5;
	*/
	double perc = (double)full_matches / (double)max_matches;
	return perc;
}




bool DatasetAnalysis::RealizeAttribute(const char* group, const char* value, int& attr_group, int& attr_value) {
	attr_group = Attr::FindAttrGroup(group);
	if (attr_group < 0) {
		attr_group = Attr::FindAttrGroupByValue(value);
		if (attr_group < 0) {
			attr_group = dynamic_attrs.Find(group);
			if (attr_group < 0) {
				attr_group = Attr::ATTR_COUNT + dynamic_attrs.GetCount();
				attr_value = 0;
				dynamic_attrs.Add(group).Add(value);
			}
			else {
				attr_value = dynamic_attrs[attr_group].FindAdd(value);
			}
		}
		else {
			attr_value = Attr::FindAttrValue(attr_group, value);
			return true; // this value can be backported (it was semi-error)
		}
	}
	else
		attr_value = Attr::FindAttrValue(attr_group, value);
	return false;
}

void DatasetAnalysis::RealizeAction(const char* action, const char* arg, int16& action_i, int16& arg_i) {
	action_i = dynamic_actions.Find(action);
	if (action_i < 0) {
		action_i = dynamic_actions.GetCount();
		arg_i = 0;
		auto& idx = dynamic_actions.Add(action);
		idx.Add(arg);
	}
	else {
		auto& idx = dynamic_actions[action_i];
		arg_i = idx.FindAdd(arg);
	}
}

#endif






DatasetAnalysis::DatasetAnalysis() {
	
}

void DatasetAnalysis::Load() {
	TextDatabase& db = GetAppModeDatabase();
	SourceData& sd = db.src_data;
	SourceDataAnalysis& sda = db.src_data.a;
	
	String dir =
		AppendFileName(MetaDatabase::Single().dir,
		MetaDatabase::Single().share + DIR_SEPS +
		"data");
	
	RealizeDirectory(dir);
	
	String ds_dir = dir;
	RealizeDirectory(ds_dir);
	
	
	for(int i = 1; i < LNG_COUNT; i++) {
		String trans_ds_key = String(GetLanguageKey(i)).Left(2);
	}
	
	tokens.Load(ds_dir, "tokens");
	token_texts.Load(ds_dir, "tokenized texts");
	word_classes.Load(ds_dir, "word classes");
	words.Load(ds_dir, "words");
	struct_part_types.Load(ds_dir, "structure part types");
	struct_types.Load(ds_dir, "structure types");
	element_keys.Load(ds_dir, "element keys");
	phrase_parts.Load(ds_dir, "phrase parts");
	attrs.Load(ds_dir, "attributes");
	actions.Load(ds_dir, "action");
	diagnostics.Load(ds_dir, "diagnostics");
	
	
	String comp_dir = AppendFileName(ds_dir, "component");
	RealizeDirectory(comp_dir);
	
}

String DatasetAnalysis::GetTokenTextString(const TokenText& txt) const {
	String o;
	for(int tk_i : txt.tokens) {
		//const Token& tk = tokens[tk_i];
		const String& key = tokens.GetKey(tk_i);
		
		if (key.GetCount() == 1 && NaturalTokenizer::IsToken(key[0])) {
			o << key;
		}
		else {
			if (!o.IsEmpty())
				o << " ";
			o << key;
		}
	}
	return o;
}

String DatasetAnalysis::GetTokenTypeString(const TokenText& txt) const {
	String o;
	for(int tk_i : txt.tokens) {
		const Token& tk = tokens[tk_i];
		int w_i = tk.word_;
		if (w_i < 0) {
			String key = ToLower(tokens.GetKey(tk_i));
			w_i = words.Find(key);
			tk.word_ = w_i;
		}
		if (w_i < 0) {
			o << "{error}";
		}
		else {
			const ExportWord& ew = words[w_i];
			o << "{";
			for(int i = 0; i < ew.class_count; i++) {
				if (i) o << "|";
				int class_i = ew.classes[i];
				const String& wc = word_classes[class_i];
				o << wc;
			}
			o << "}";
			/*if (key.GetCount() == 1 && NaturalTokenizer::IsToken(key[0])) {
				o << key;
			}
			else {
				if (!o.IsEmpty())
					o << " ";
				o << key;
			}*/
		}
	}
	return o;
}

String DatasetAnalysis::GetWordString(const Vector<int>& words) const {
	String o;
	for(int w_i : words) {
		if (w_i < 0) continue;
		const String& key = this->words.GetKey(w_i);
		
		if (key.GetCount() == 1 && NaturalTokenizer::IsToken(key[0])) {
			o << key;
		}
		else {
			if (!o.IsEmpty())
				o << " ";
			o << key;
		}
	}
	return o;
}

String DatasetAnalysis::GetTypeString(const Vector<int>& word_classes) const {
	String o;
	for(int wc_i : word_classes) {
		if (wc_i < 0)
			o << "{error}";
		else {
			const String& wc = this->word_classes[wc_i];
			o << "{" << wc << "}";
		}
	}
	return o;
}

String DatasetAnalysis::GetActionString(const Vector<int>& actions) const {
	String o;
	for(int act_i : actions) {
		if (!o.IsEmpty()) o << ", ";
		if (act_i < 0)
			o << "error";
		else {
			const ActionHeader& ah = this->actions.GetKey(act_i);
			o << ah.action;
			if (!ah.arg.IsEmpty())
				o << "(" << ah.arg << ")";
		}
	}
	return o;
}

#if 0
String DatasetAnalysis::GetScriptDump(int i) const {
	String s;
	const ScriptStruct& ss = scripts[i];
	for(int i = 0; i < ss.parts.GetCount(); i++) {
		const auto& part = ss.parts[i];
		//if (s.GetCount()) s << "\n";
		s << Format("[%d: %s]\n", i, GetTextTypeString(part.type) + " " + IntStr(part.num+1));
		
		for(int j = 0; j < part.sub.GetCount(); j++) {
			const auto& sub = part.sub[j];
			//if (s.GetCount()) s << "\n";
			s << Format("\t[%d.%d: repeat %.2!m]\n", i,j, sub.repeat);
			
			bool show_subsub = sub.sub.GetCount() > 1;
			for(int k = 0; k < sub.sub.GetCount(); k++) {
				const auto& ssub = sub.sub[k];
				if (show_subsub)
					s << Format("\t\t[%d.%d.%d]\n", i,j,k);
				for(int l = 0; l < ssub.token_texts.GetCount(); l++) {
					int tt_i = ssub.token_texts[l];
					if (tt_i < 0) continue;
					const TokenText& tt = this->token_texts[tt_i];
					if (show_subsub) s.Cat('\t');
					s << "\t\t" << GetTokenTextString(tt) << "\n";
				}
			}
		}
	}
	return s;
}

String DatasetAnalysis::GetScriptDump(DatasetAnalysis& da, int i) const {
	String s;
	String extra;
	const ScriptStruct& ss = scripts[i];
	for(int i = 0; i < ss.parts.GetCount(); i++) {
		const auto& part = ss.parts[i];
		//if (s.GetCount()) s << "\n";
		
		extra = part.cls >= 0 ? da.element_keys[part.cls] : String();
		s << Format("[%d: %s] (%s)\n", i, GetTextTypeString(part.type) + " " + IntStr(part.num+1), extra);
		
		for(int j = 0; j < part.sub.GetCount(); j++) {
			const auto& sub = part.sub[j];
			//if (s.GetCount()) s << "\n";
			extra = sub.cls >= 0 ? da.element_keys[sub.cls] : String();
			s << Format("\t[%d.%d: repeat %.2!m] (%s)\n", i,j, sub.repeat, extra);
			
			bool show_subsub = sub.sub.GetCount() > 1;
			for(int k = 0; k < sub.sub.GetCount(); k++) {
				const auto& ssub = sub.sub[k];
				extra = ssub.cls >= 0 ? da.element_keys[ssub.cls] : String();
				if (show_subsub)
					s << Format("\t\t[%d.%d.%d] (%s)\n", i,j,k, extra);
				for(int l = 0; l < ssub.token_texts.GetCount(); l++) {
					int tt_i = ssub.token_texts[l];
					if (tt_i < 0) continue;
					const TokenText& tt = this->token_texts[tt_i];
					if (show_subsub) s.Cat('\t');
					s << "\t\t" << GetTokenTextString(tt) << "\n";
				}
			}
		}
	}
	return s;
}

VectorMap<int,int> DatasetAnalysis::GetSortedElements() {
	VectorMap<int,int> vmap;
	for(const ScriptStruct& ss : scripts.GetValues()) {
		for(const auto& part : ss.parts) {
			if (part.cls >= 0)
				vmap.GetAdd(part.cls,0)++;
			for(const auto& sub : part.sub) {
				if (sub.cls >= 0)
					vmap.GetAdd(sub.cls,0)++;
				for(const auto& ssub : sub.sub) {
					if (sub.cls >= 0)
						vmap.GetAdd(sub.cls,0)++;
				}
			}
		}
	}
	SortByValue(vmap, StdGreater<int>());
	return vmap;
}
#endif

VectorMap<int,int> DatasetAnalysis::GetSortedElementsOfPhraseParts() {
	VectorMap<int,int> vmap;
	for (const auto& pp : phrase_parts.GetValues()) {
		if (pp.el_i >= 0)
			vmap.GetAdd(pp.el_i,0)++;
	}
	SortByValue(vmap, StdGreater<int>());
	return vmap;
}

#if 0
String ScriptSuggestion::GetText() const {
	String content;
	for(int j = 0; j < parts.GetCount(); j++) {
		const auto& v = parts[j];
		String part = v.name;
		if (part.IsEmpty() || v.lines.IsEmpty()) continue;
		content << "[" << part << "]\n";
		
		for(int k = 0; k < v.lines.GetCount(); k++) {
			content << v.lines[k] << "\n";
		}
		content << "\n";
	}
	return content;
}
#endif



END_TEXTLIB_NAMESPACE

