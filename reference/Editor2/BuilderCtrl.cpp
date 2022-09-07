#include "BuilderCtrl.h"



BuilderCtrl::BuilderCtrl() {
	Title("Build methods");
	Add(mainsplit.VSizePos().HSizePos());
	mainsplit.Set(methodlist, main);
	mainsplit.SetPos(2000);
	SetRect(0,0,640,480);
	Sizeable();
	int bh = 30, o = 5, y = 5, lw = 150;
	main.Add(lname			.TopPos(y,bh).LeftPos(o,lw)); 
	main.Add(name			.TopPos(y,bh).HSizePos(lw+o)); y += bh + o;
	main.Add(ltype			.TopPos(y,bh).LeftPos(o,lw)); 
	main.Add(type			.TopPos(y,bh).LeftPos(o+lw,lw)); y += bh + o;
	main.Add(lcompiler		.TopPos(y,bh).LeftPos(o,lw)); 
	main.Add(compiler		.TopPos(y,bh).HSizePos(lw+o)); y += bh + o;
	main.Add(ldebugger		.TopPos(y,bh).LeftPos(o,lw)); 
	main.Add(debugger		.TopPos(y,bh).HSizePos(lw+o)); y += bh + o;
	main.Add(ldbgcflags		.TopPos(y,bh).LeftPos(o,lw)); 
	main.Add(dbgcflags		.TopPos(y,bh).HSizePos(lw+o)); y += bh + o;
	main.Add(ldbglinkflags	.TopPos(y,bh).LeftPos(o,lw));
	main.Add(dbglinkflags	.TopPos(y,bh).HSizePos(lw+o)); y += bh + o;
	main.Add(lcflags		.TopPos(y,bh).LeftPos(o,lw));
	main.Add(cflags			.TopPos(y,bh).HSizePos(lw+o)); y += bh + o;
	main.Add(llinkflags		.TopPos(y,bh).LeftPos(o,lw));
	main.Add(linkflags		.TopPos(y,bh).HSizePos(lw+o)); y += bh + o;
	main.Add(paths			.VSizePos(y).HSizePos());
	paths.Add(bins, "PATH - Executable directories"); paths.Add(bins);
	paths.Add(incs, "INCLUDE directories"); paths.Add(incs);
	paths.Add(libs, "LIB directories"); paths.Add(libs);
	lname			.SetLabel("Name:");
	ltype			.SetLabel("Builder:");
	lcompiler		.SetLabel("Compiler:");
	ldebugger		.SetLabel("Debugger:");
	ldbgcflags		.SetLabel("Debug C/C++ flags:");
	ldbglinkflags	.SetLabel("Debug link flags:");
	lcflags			.SetLabel("C/C++ flags:");
	llinkflags		.SetLabel("Link flags:");
	methodlist.AddColumn("Method");
	bins.AddColumn("Directory");
	libs.AddColumn("Directory");
	incs.AddColumn("Directory");
	type.Add("GCC");
	type.Add("Open Watcom");
	type.Add("Clang");
	type.Add("Ndless");
	type.SetIndex(0);
	methodlist.WhenAction = THISBACK(SelectMethod);
	name		.WhenAction = THISBACK(EditMethodName);
	type		.WhenAction = THISBACK(EditMethod);
	compiler	.WhenAction = THISBACK(EditMethod);
	debugger	.WhenAction = THISBACK(EditMethod);
	dbgcflags	.WhenAction = THISBACK(EditMethod);
	dbglinkflags.WhenAction = THISBACK(EditMethod);
	cflags		.WhenAction = THISBACK(EditMethod);
	linkflags	.WhenAction = THISBACK(EditMethod);
	methodlist.SetDefault = THISBACK(SetDefault);
	methodlist.NewMethod = THISBACK(NewMethod);
	methodlist.RemoveMethod = THISBACK(RemoveMethod);
}



void BuilderCtrl::SetBuilder(Builder& b) {
	builder = &b;
	RefreshMethods();
}

void BuilderCtrl::RefreshMethods() {
	for(int i = 0; i < builder->methods.GetCount(); i++) {
		BuilderMethod& bm = builder->methods[i];
		methodlist.Set(i, 0, bm.name);
	}
	methodlist.SetCount(builder->methods.GetCount());
}


#define CLEAR(x) x.SetData("");
#define SET(x) x.SetData(bm.x);
void BuilderCtrl::SelectMethod() {
	incs.Clear();
	bins.Clear();
	libs.Clear();
	
	int c = methodlist.GetCursor();
	if (c < 0 || c >= builder->methods.GetCount())  {
		type.SetData("");
		CLEAR(compiler);
		CLEAR(debugger);
		CLEAR(cflags);
		CLEAR(linkflags);
		CLEAR(dbgcflags);
		CLEAR(dbglinkflags);
		
		return;
	}
	
	BuilderMethod& bm = builder->methods[c];
	
	if (bm.type < 0 || bm.type >= type.GetCount()) bm.type = 0;
	type.SetIndex(bm.type);
	
	SET(name);
	SET(compiler);
	SET(debugger);
	SET(cflags);
	SET(linkflags);
	SET(dbgcflags);
	SET(dbglinkflags);
	
	for(int i = 0; i < bm.bins.GetCount(); i++)
		bins.Add(bm.bins[i]);
	
	for(int i = 0; i < bm.libs.GetCount(); i++)
		libs.Add(bm.libs[i]);
	
	for(int i = 0; i < bm.incs.GetCount(); i++)
		incs.Add(bm.incs[i]);
	
}
#undef CLEAR
#undef SET

#define SET(x) bm.x = x.GetData();
void BuilderCtrl::EditMethod() {
	int c = methodlist.GetCursor();
	if (c < 0 || c >= builder->methods.GetCount()) return;
	BuilderMethod& bm = builder->methods[c];
	
	bm.type = type.GetIndex();
	
	SET(compiler);
	SET(debugger);
	SET(cflags);
	SET(linkflags);
	SET(dbgcflags);
	SET(dbglinkflags);
}
#undef SET

void BuilderCtrl::EditMethodName() {
	int c = methodlist.GetCursor();
	if (c < 0 || c >= builder->methods.GetCount()) return;
	BuilderMethod& bm = builder->methods[c];
	
	bm.name = name.GetData();
	RefreshMethods();
}

void BuilderCtrl::NewMethod() {
	builder->methods.Add().SetId(builder->builder_counter);
	builder->builder_counter++;
	RefreshMethods();
	methodlist.SetCursor(methodlist.GetCount()-1);
}

void BuilderCtrl::RemoveMethod() {
	int c = methodlist.GetCursor();
	if (c < 0 || c >= builder->methods.GetCount()) return;
	builder->methods.Remove(c);
	RefreshMethods();
}

void BuilderCtrl::SetDefault() {
	int c = methodlist.GetCursor();
	if (c < 0 || c >= builder->methods.GetCount()) return;
	for(int i = 0; i < builder->methods.GetCount(); i++) {
		BuilderMethod& bm = builder->methods[i];
		bm.SetDefault(i==c);
	}
}


