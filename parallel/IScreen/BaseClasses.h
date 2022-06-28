// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IScreen_BaseClasses_h_
#define _IScreen_BaseClasses_h_

NAMESPACE_PARALLEL_BEGIN

struct ScrSinkDevice : public Atom {
	RTTI_DECL1(ScrSinkDevice, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~ScrSinkDevice() {}

};

struct ScrEventsBase : public Atom {
	RTTI_DECL1(ScrEventsBase, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~ScrEventsBase() {}

};

struct ScrContext : public Atom {
	RTTI_DECL1(ScrContext, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~ScrContext() {}

};

NAMESPACE_PARALLEL_END



#endif

