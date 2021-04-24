#ifndef _Language_HieroLang_h_
#define _Language_HieroLang_h_

NAMESPACE_LANGUAGE_BEGIN

struct HieroSignTransliteration : Moveable<HieroSignTransliteration> {
	String transliteration;
	byte type;
	byte use;
	
	void Set(String tl, byte type, byte use) {transliteration = tl; this->type = type; this->use = use;}
	
	void Serialize(Stream& s) {s % transliteration % type % use;}
};

struct HieroSignVariant : Moveable<HieroSignVariant> {
	int base_sign;
	bool is_similar;
	byte linguistic;
	
	void Set(int bs, bool is_similar, byte linguistic) {base_sign = bs; this->is_similar = is_similar; this->linguistic = linguistic;}
	
	void Serialize(Stream& s) {s % base_sign % is_similar % linguistic;}
};

struct HieroSign : Moveable<HieroSign> {
	String name;
	String description;
	Vector<int> tags;
	Vector<HieroSignTransliteration> transliterations;
	Vector<int> contains;
	Vector<String> contains_str;
	Vector<HieroSignVariant> variant_of;
	
	
	HieroSign& Tag(int i) {tags.Add(i); return *this;}
	HieroSign& TransLit(String tl, byte type, byte use) {transliterations.Add().Set(tl, type, use); return *this;}
	HieroSign& Desc(String s) {description = s; return *this;}
	HieroSign& Contains(int sign_id) {contains.Add(sign_id); return *this;}
	HieroSign& Contains(String sign) {contains_str.Add(sign); return *this;}
	HieroSign& Variant(int bs, bool is_similar, byte linguistic) {variant_of.Add().Set(bs, is_similar, linguistic); return *this;}
	
	void Serialize(Stream& s) {s % name % description % tags % transliterations % contains % contains_str % variant_of;}
};

struct HieroLangDictItem : Moveable<HieroLangDictItem> {
	static const int max_code_len = 15;
	
	Vector<uint16> code;
	String pronon;
	String desc;
	
	void Serialize(Stream& s) {s % code % pronon % desc;}
};

class HieroLang : public Lang {
	Dictionary sign_dict, translit_dict, pronon_dict, proto_dict, en_dict;
	Array<HieroSign> signs;
	Vector<HieroLangDictItem> dict;
	Index<String> tags, types, linguistics, uses;
	
	VectorMap<int, int> chr_ascii;
	VectorMap<int, WString> chr_pronon;
	
	void AddCharToAscii(WString chr, WString ascii) {chr_ascii.Add(chr[0], ascii[0]);}
	void AddPronounciation(int i, WString pron) {chr_pronon.Add(i, pron);}
	void ParseSigns(String xml_path);
	void ParseDictionary(String raw_path);
public:
	HieroLang();
	
	const HieroSign& GetSign(int i) {return signs[i];}
	const HieroLangDictItem& GetDictionary(int i) {return dict[i];}
	Dictionary& GetSignDictionary() {return sign_dict;}
	Dictionary& GetTransliterationDictionary() {return translit_dict;}
	Dictionary& GetPronouncingDictionary() {return pronon_dict;}
	Dictionary& GetHieroDictionary() {return proto_dict;}
	Dictionary& GetEnglishDictionary() {return en_dict;}
	Node* GetAlpha(int chr);
	
	WString Pronounce(WString str);
	
	
	void LoadThis() {LoadFromFile(*this, ConfigFile("protolang.bin"));}
	void StoreThis() {StoreToFile(*this, ConfigFile("protolang.bin"));}
	void Serialize(Stream& s) {
		s % sign_dict % translit_dict % pronon_dict % proto_dict % en_dict
		  % signs % dict % tags % types % linguistics % uses
		  % chr_ascii % chr_pronon;
	}
};

inline HieroLang& GetHieroLang() {return Single<HieroLang>();}


NAMESPACE_LANGUAGE_END

#endif
