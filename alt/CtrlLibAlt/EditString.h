#ifndef _CtrlLib_EditString_h_
#define _CtrlLib_EditString_h_



#define STB_TEXTEDIT_CHARTYPE				wchar_t
#define STB_TEXTEDIT_POSITIONTYPE			int
#define STB_TEXTEDIT_UNDOSTATECOUNT			99
#define STB_TEXTEDIT_UNDOCHARCOUNT			999

#define STB_TEXTEDIT_STRING					UPP::TextCtrl
#define STB_TEXTEDIT_STRINGLEN(obj)			(obj->GetCount())
#define STB_TEXTEDIT_LAYOUTROW(r,obj,n)		UPP::EditString::LayoutRowStatic(r, obj, n)
#define STB_TEXTEDIT_GETWIDTH(obj,n,i)		UPP::EditString::GetWidthStatic(obj, n, i)
#define STB_TEXTEDIT_KEYTOTEXT(k)			UPP::EditString::KeyToText(k)
#define STB_TEXTEDIT_GETCHAR(obj,i)			(obj->Get(i))
#define STB_TEXTEDIT_NEWLINE				'\n'
#define STB_TEXTEDIT_DELETECHARS(obj,i,n)	(obj->Remove(i, n))
#define STB_TEXTEDIT_INSERTCHARS(obj,i,c,n)	(obj->Insert(i, c, n))
#define STB_TEXTEDIT_K_SHIFT				(UPP::K_SHIFT)
#define STB_TEXTEDIT_K_LEFT					(UPP::K_LEFT)
#define STB_TEXTEDIT_K_RIGHT				(UPP::K_RIGHT)
#define STB_TEXTEDIT_K_UP					(UPP::K_UP)
#define STB_TEXTEDIT_K_DOWN					(UPP::K_DOWN)
#define STB_TEXTEDIT_K_LINESTART			(UPP::K_HOME)
#define STB_TEXTEDIT_K_LINEEND				(UPP::K_END)
#define STB_TEXTEDIT_K_TEXTSTART			(UPP::K_CTRL|UPP::K_HOME)
#define STB_TEXTEDIT_K_TEXTEND				(UPP::K_CTRL|UPP::K_END)
#define STB_TEXTEDIT_K_DELETE				(UPP::K_DELETE)
#define STB_TEXTEDIT_K_BACKSPACE			(UPP::K_BACKSPACE)
#define STB_TEXTEDIT_K_UNDO					(UPP::K_CTRL|UPP::K_Z)
#define STB_TEXTEDIT_K_REDO					(UPP::K_CTRL|UPP::K_SHIFT|UPP::K_Z)
#define STB_TEXTEDIT_K_INSERT				(UPP::K_INSERT)
#define STB_TEXTEDIT_IS_SPACE(ch)			UPP::IsSpace(ch)
#define STB_TEXTEDIT_K_WORDLEFT				(UPP::K_CTRL|UPP::K_LEFT)
#define STB_TEXTEDIT_K_WORDRIGHT			(UPP::K_CTRL|UPP::K_RIGHT)
#define STB_TEXTEDIT_K_PGUP					UPP::K_PAGEUP
#define STB_TEXTEDIT_K_PGDOWN				UPP::K_PAGEDOWN


#include "stb_textedit.h"


NAMESPACE_UPP


class TextCtrl : public Ctrl {
	STB_TexteditState state;
	WString data;
	Vector<int> rows;
	int lineh = 14;
	Font fnt;
	
	void RefreshRowBegins();
	
	static bool Intersects(int b0, int e0, int b1, int e1);
	
public:
	typedef TextCtrl CLASSNAME;
	TextCtrl(bool multiline=false);
	
	virtual bool Key(dword key, int count);
	virtual void Paint(Draw& d);
	virtual void MouseMove(Point p, dword keyflags);
	virtual void MouseWheel(Point p, int zdelta, dword keyflags);
	virtual void MouseLeave() {Refresh();}
	virtual void LeftDown(Point p, dword keyflags);
	
	int GetCount() const {return data.GetCount();}
	int Get(int pos) const {return data.Get(pos);}
	void Remove(int i, int n);
	bool Insert(int i, const wchar_t* c, int n);
	
	
	static void LayoutRowStatic(StbTexteditRow* r, TextCtrl* obj, int n) {obj->LayoutRow(r, n);}
	static float GetWidthStatic(TextCtrl* obj, int n, int i) {return obj->GetWidth(n, i);}
	static int KeyToText(int k);
	
	void LayoutRow(StbTexteditRow* r, int n);
	float GetWidth(int n, int i);
	
};

class EditString : public TextCtrl {
	
public:
	EditString() : TextCtrl(false) {}
};

class DocEdit : public TextCtrl {
	
public:
	DocEdit() : TextCtrl(true) {}
};


END_UPP_NAMESPACE


#endif
