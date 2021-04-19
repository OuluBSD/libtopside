#ifndef _DrawAlt_Font_h_
#define _DrawAlt_Font_h_


NAMESPACE_UPP


class Font {
	struct FontRef {
		SysFont font;
		int refs = 1;
		
		String dir;
		String name;
		int ptsize = 0;
		int weight = 1;
		bool italic = false;
		
		FontRef() {}
		FontRef(RawSysFont* f) : font(f) {}
		void Inc() {refs++;}
		void Dec() {refs--; if (refs <= 0) delete this;}
	};
	
	FontRef* ref = NULL;
	
public:
	typedef Font CLASSNAME;
	Font() {}
	Font(const Font& fnt) {*this = fnt;}
	Font(Font&& fnt) {ref = fnt.ref; fnt.ref = NULL;}
	Font(RawSysFont* f) {if (f) {ref = new FontRef(f);}}
	Font(FontRef* r) {if (r) {ref = r;}}
	~Font() {Clear();}
	void operator=(const Font& fnt) {Clear(); ref = fnt.ref; if (ref) ref->Inc();}
	void Clear() {if (ref) ref->Dec(); ref = NULL;}
	bool IsEmpty() const {return ref == NULL;}
	SysFont* GetSysFont() {if (!ref) return NULL; return &ref->font;}
	
	static Font LoadFont(String dir, String name, int ptsize=16, int weight=1, bool italic=false);
};


Size GetStdFontSize();
Font GetStdFont(int size=-1);
void SetStdFont(Font fnt);

inline Font StdFont(int size=-1) {return GetStdFont();}

Size GetTextSize(String s, Font fnt);

RawSysFont* LoadSysFont(String path, int size);
Size GetSysFontTextSize(RawSysFont* fnt, String s);

END_UPP_NAMESPACE


#endif
