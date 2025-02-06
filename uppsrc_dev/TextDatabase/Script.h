#ifndef _TextDatabase_Script_h_
#define _TextDatabase_Script_h_


BEGIN_TEXTLIB_NAMESPACE




// In use
struct ScriptStruct : Moveable<ScriptStruct> {
	ScriptStruct() {}
	ScriptStruct(const ScriptStruct& s) {*this = s;}
	ScriptStruct(ScriptStruct&& s) {*this = s;}
	void operator=(const ScriptStruct& s) {
		parts <<= s.parts;
	}
	
	struct SubSubPart : Moveable<SubSubPart> {
		Vector<int> token_texts;
		int cls = -1;
		
		SubSubPart() {}
		SubSubPart(const SubSubPart& s) {*this = s;}
		void Serialize(Stream& s) {s % token_texts % cls;}
		void Jsonize(JsonIO& json) {json("token_texts", token_texts)("cls", cls);}
		void operator=(const SubSubPart& s) {
			token_texts <<= s.token_texts;
			cls = s.cls;
		}
	};
	struct SubPart : Moveable<SubPart> {
		Vector<SubSubPart> sub;
		int cls = -1;
		int repeat = 0;
		
		SubPart() {}
		SubPart(const SubPart& s) {*this = s;}
		void Serialize(Stream& s) {s % sub % cls % repeat;}
		void Jsonize(JsonIO& json) {json("sub", sub)("cls", cls)("repeat", repeat);}
		void operator=(const SubPart& s) {
			sub <<= s.sub;
			cls = s.cls;
			repeat = s.repeat;
		}
	};
	struct Part : Moveable<Part> {
		Vector<SubPart> sub;
		int type = -1;
		int num = -1;
		int cls = -1, typeclass = -1, content = -1;
		
		Part() {}
		Part(const Part& p) {*this = p;}
		void Serialize(Stream& s) {s % sub % type % num % cls % typeclass % content;}
		void Jsonize(JsonIO& json) {json("sub", sub)("type", type)("num", num)("cls", cls)("tc", typeclass)("c", content);}
		void operator=(const Part& s) {
			sub <<= s.sub;
			type = s.type;
			num = s.num;
			cls = s.cls;
			typeclass = s.typeclass;
			content = s.content;
		}
	};
	Vector<Part> parts;
	
	void Serialize(Stream& s) {s % parts;}
	
	void Jsonize(JsonIO& json) {
		json
			("parts", parts)
			;
	}
	bool HasAnyClasses() const {
		for (const auto& p : parts) {
			if (p.cls >= 0) return true;
			for (const auto& s : p.sub) {
				if (s.cls >= 0) return true;
				for (const auto& ss : s.sub) {
					if (ss.cls >= 0) return true;
				}
			}
		}
		return false;
	}
	
};


struct Script : DataFile {
	String						native_title;
	String						copyright;
	String						content_vision;
	String						lead;
	int64						belief_uniq = 0;
	int							lng_i = 0;
	int							typeclass = 0;
	int							content = 0;
	bool						is_unsafe = false;
	bool						is_story = false;
	bool						is_self_centered = false;
	
	Vector<bool>				simple_attrs;
	Vector<int>					clr_list;
	Vector<String>				post_analysis;
	ScriptStruct				ref_struct;
	
	Vector<bool>				actions_enabled;
	Vector<int>					phrase_parts[ContentType::PART_COUNT];
	
	
	int GetFirstPartPosition() const;
	String GetAnyTitle() const;
	String GetText() const;
	void LoadStructuredText(const String& s);
	void LoadStructuredTextExt(const String& s);
	void SetEditText(const String& s);
	
	//Script() {post_analysis.SetCount(POSTSCRIPT_COUNT);}
	Script() {post_analysis.SetCount(SCORE_COUNT);}
	~Script();
	void Store(Entity& a);
	void LoadTitle(Entity& a, String title);
	void Jsonize(JsonIO& json) {
		json
			("title", native_title)
			("copyright", copyright)
			("content_vision", content_vision)
			("lead", lead)
			("belief_uniq", belief_uniq)
			("lng_i", lng_i)
			("typeclass", typeclass)
			("content", content)
			("is_unsafe", is_unsafe)
			("is_story", is_story)
			("is_self_centered", is_self_centered)
			("clr_list", clr_list)
			("post_analysis", post_analysis)
			("ref_struct", ref_struct)
			;
		
		for(int i = 0; i < ContentType::PART_COUNT; i++)
			JsonCompressedStream(json, "phrase_parts" + IntStr(i), phrase_parts[i]);
		JsonCompressedStream(json, "actions_enabled", actions_enabled);
		JsonCompressedStream(json, "simple_attrs", simple_attrs);
		
		if (json.IsLoading()) {
			if (post_analysis.GetCount() < SCORE_COUNT)
				post_analysis.SetCount(SCORE_COUNT);
		}
	}
	
};


END_TEXTLIB_NAMESPACE


#endif

