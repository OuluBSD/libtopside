#ifndef _CtrlLib_CtrlLib_h_
#define _CtrlLib_CtrlLib_h_

#include <CtrlCore/CtrlCore.h>


NAMESPACE_UPP_BEGIN

struct FileSel {
	void ActiveDir(String path) {}
};
class Button: public Ctrl {};
class DocEdit: public Ctrl {};
class EditString: public Ctrl {};
class ArrayCtrl: public Ctrl {
public:
	void Set(int i, int c, UPP::Value v) {}
	void AddColumn(String) {}
	void ColumnWidths(String) {}
	void NoHeader() {}
	void SetLineCy(int) {}
	void SetCount(int) {}
	void SetCursor(int) {}
	void GoEnd(){}
	void AddIndex(){}
	int GetCount() const {return 0;}
	UPP::Value Get(int i, int j) {return UPP::Value();}
	void Add(UPP::Value v) {}
	Event<> WhenCursor;
};
class ButtonOption: public Ctrl {};
class TreeCtrl: public Ctrl {
public:
	void SetRoot(Image i , int j, String s ="") {}
	void SetRoot(Image i , String s ="") {}
	void OpenDeep(int) {}
	void SetCursor(int) {}
	void Clear() {}
	int Add(int i, Image j, int k, String s="") {return 0;}
	int Add(int i, Image j, String s="") {return 0;}
	int Get(int) const {return 0;}
	Event<> WhenCursor;
};
class Splitter: public Ctrl {
public:
	Splitter& Vert() {return *this;}
	Splitter& SetPos(int pos) {return *this;}
	Splitter& SetPos(int i, int pos) {return *this;}
	Splitter& operator << (Ctrl& c) {return *this;}
};
class ParentCtrl: public Ctrl {
public:
	void Add(Ctrl& c) {}
};
class ScrollBar: public CtrlFrame {
public:
	Event<> WhenScroll;
	void SetLine(int i) {}
	void SetTotal(int i) {}
	void Wheel(int zdelta) {}
	void SetPage(int zdelta) {}
	ScrollBar& Vert() {return *this;}
	ScrollBar& Horz() {return *this;}
	bool VertKey(dword key) {return false;}
	bool HorzKey(dword key) {return false;}
	operator int() const {return 0;}
	void ScrollInto(int i) {}
	void Set(int i) {}
	int GetTotal() const {return 0;}
	int GetPage() const {return 0;}
	int Get() const {return 0;}
};
class TabCtrl: public Ctrl {
public:
	void Add(Ctrl& c, String title) {}
};

inline void LoadFromGlobal(FileSel& fs, String) {}
inline void StoreToGlobal(FileSel& fs, String) {}

struct MenuBar : Bar {
	void Execute() {}
};

inline CtrlFrame& InsetFrame() {return Single<CtrlFrame>();}

NAMESPACE_UPP_END

#endif
