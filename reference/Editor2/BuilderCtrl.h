#ifndef _Editor_BuilderCtrl_h_
#define _Editor_BuilderCtrl_h_

#include <CtrlLib/CtrlLib.h>
using namespace UPP;

#include "Builder.h"

class MethodList : public ArrayCtrl {
public:
	typedef MethodList CLASSNAME;
	void LocalMenu(Bar& bar) {
		bar.Add("New method", Proxy(NewMethod));
		bar.Add("Remove method", Proxy(RemoveMethod));
		bar.Add("Set default", Proxy(SetDefault));
	}

	void RightDown(Point p, dword dw) {
		ArrayCtrl::LeftDown(p, dw);
		MenuBar::Execute(THISBACK(LocalMenu));
	}
	
	Callback NewMethod, RemoveMethod, SetDefault;
};

class BuilderCtrl : public TopWindow {
	Builder* builder;
	
	MethodList methodlist;
	Splitter mainsplit;
	ParentCtrl main;
	
	Label lname;
	EditString name;
	
	Label ltype;
	DropList type;
	
	Label lcompiler;
	EditString compiler;
	
	Label ldebugger;
	EditString debugger;
	
	Label ldbgcflags;
	EditString dbgcflags;
	
	Label ldbglinkflags;
	EditString dbglinkflags;
	
	Label lcflags;
	EditString cflags;
	
	Label llinkflags;
	EditString linkflags;
	
	TabCtrl paths;
	ArrayCtrl bins, libs, incs;
	
public:
	typedef BuilderCtrl CLASSNAME;
	BuilderCtrl();
	
	void SetBuilder(Builder& b);
	void SelectMethod();
	void EditMethod();
	void EditMethodName();
	void RefreshMethods();
	
	void NewMethod();
	void RemoveMethod();
	void SetDefault();
};


#endif
