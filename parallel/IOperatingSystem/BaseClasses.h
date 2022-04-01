// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.4.1 19:22:00

#ifndef _IOperatingSystem_BaseClasses_h_
#define _IOperatingSystem_BaseClasses_h_

NAMESPACE_PARALLEL_BEGIN

struct OsMessageBus : public Atom {
	RTTI_DECL1(OsMessageBus, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~OsMessageBus() {}

};

struct OsProcessManager : public Atom {
	RTTI_DECL1(OsProcessManager, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~OsProcessManager() {}

};

struct OsDesktopManager : public Atom {
	RTTI_DECL1(OsDesktopManager, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~OsDesktopManager() {}

};

NAMESPACE_PARALLEL_END



#endif

