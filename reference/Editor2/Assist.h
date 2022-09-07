#ifndef _Editor_Assist_h_
#define _Editor_Assist_h_

#include <CtrlLib/CtrlLib.h>
using namespace UPP;

class IDE;

class Assist : public ParentCtrl {
	IDE* ide;
	TabCtrl tabs;
	ArrayCtrl completions, diagnostics, misc;
	ArrayCtrl nice_completions, nice_diagnostics, nice_misc;
	
	Splitter split, nice_split;
	Translation::Cursor cursor;
	String path;
	int line, column;
public:
	Assist(IDE* ide);
	
	void RefreshNiceData();
	void RefreshData();
	void SetCursor(const String& path, int line, int column, Translation::Cursor cursor);
	
	virtual bool   Key(dword key, int count);
	
};


#endif
