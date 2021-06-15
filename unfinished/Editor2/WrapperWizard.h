#ifndef _Editor_WrapperWizard_h_
#define _Editor_WrapperWizard_h_

#include <CtrlLib/CtrlLib.h>
using namespace UPP;

#define LAYOUTFILE <Editor/WrapperWizard.lay>
#include <CtrlCore/lay.h>

#include "NodeCache.h"

class IDE;

// Shows recent files, output directory path and "browse" button
class Frame1 : public WithWrapFrame1<ParentCtrl> {
	
public:
	Frame1();
	
};

// Shows files, classes and functions, methods and field-declarations
class Frame2 : public ParentCtrl {
	
public:
	Frame2();
	
	Splitter split;
	ArrayCtrl files, contents, cls_contents;
	Button next, prev;
	
};


// Asks output file
class Frame3 : public WithWrapFrame3<ParentCtrl> {
	
public:
	Frame3();
	
	
};

// Shows progress, results and errors
class Frame4 : public ParentCtrl {
	
public:
	Frame4();
	
	DocEdit output;
	Button prev, restart, ok;
	
};


class WrapperWizard : public TopWindow {
	IDE* ide;
	
	Frame1 f1;
	Frame2 f2;
	Frame3 f3;
	Frame4 f4;
	int view;
	
	VectorMap<String, String> recent_wraps;
	String wrap_path;
	FileAppend file;
	
	ClangNode basic;
	
	void HideAll();
	void SetView(int i);
public:
	typedef WrapperWizard CLASSNAME;
	WrapperWizard(IDE* ide);
	
	void Serialize(Stream& s) {
		s % recent_wraps % wrap_path;
	}
	void StoreThis() {StoreToFile(*this, ConfigFile("WrapperWizard.bin"));}
	void LoadThis() {LoadFromFile(*this, ConfigFile("WrapperWizard.bin"));}
	
	void Phase1();
	void Phase2();
	void Phase3();
	void Phase4();
	
	void Ok() {Close();}
	
	virtual bool Key(dword key, int count);
	
	void SetF1Recent();
	void F1Browse();
	
	void SetF2File();
	void SetF2Class();
	
};




#endif
