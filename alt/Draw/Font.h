#ifndef _DrawAlt_Font_h_
#define _DrawAlt_Font_h_


NAMESPACE_UPP


class Font {
	struct FontRef {
		SysFont font;
		int refs = 1;
		
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
	Font(int type, int n) {TODO}
	~Font() {Clear();}
	
	void operator=(const Font& fnt) {Clear(); ref = fnt.ref; if (ref) ref->Inc();}
	bool operator==(const Font& fnt) const;
	
	void		Clear() {if (ref) ref->Dec(); ref = NULL;}
	bool		IsEmpty() const {return ref == NULL;}
	bool		IsNullInstance() const {return ref == NULL;}
	SysFont*	GetSysFont() {if (!ref) return NULL; return &ref->font;}
	void		Face(int i);
	void		Height(int i);
	void		Italic(bool b=true);
	void		Bold(bool b=true);
	void		Strikeout(bool b=true);
	void		Underline(bool b=true);
	int			GetAscent() const;
	int			GetDescent() const;
	int			GetHeight() const;
	
	static Font		LoadFont(String dir, String name, int ptsize=16, int weight=1, bool italic=false);
	static int		GetFaceCount();
	static String	GetFaceName(int i);
	
	FontRef*	GetNative() {return ref;}
	
	
public:
	enum {
		STDFONT,
		SERIF,
		SANSSERIF,
		MONOSPACE,
	#ifdef PLATFORM_WIN32
		SYMBOL, // deprecated
		WINGDINGS, // deprecated
		TAHOMA, // deprecated
	#endif
		OTHER, // deprecated

	// Backward compatibility:
		ROMAN = SERIF,
		ARIAL = SANSSERIF,
		COURIER = MONOSPACE,
		SCREEN_SERIF = SERIF,
		SCREEN_SANS = SANSSERIF,
		SCREEN_FIXED = MONOSPACE,
	};
	
};


Size GetStdFontSize();
Font GetStdFont(int size=-1);
void SetStdFont(Font fnt);
Font Arial(int size=-1);
Font Monospace(int size=-1);
Font Serif(int size=-1);
Font SansSerif(int size=-1);

Font StdFont(int size=-1);

Font ScreenSerif(int n = -32000);
Font ScreenSans(int n = -32000);
Font ScreenFixed(int n = -32000);

Size GetTextSize(String s, Font fnt);
Size GetTextSize(WString ws, Font fnt);

inline int GetStdFontCy()                          { return GetStdFontSize().cy; }

END_UPP_NAMESPACE


#endif
