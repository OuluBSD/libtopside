// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.4.3 11:11:55

#ifndef _IScript_BaseClasses_h_
#define _IScript_BaseClasses_h_

NAMESPACE_PARALLEL_BEGIN

struct ScrRunner : public Atom {
	RTTI_DECL1(ScrRunner, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~ScrRunner() {}

};

struct ScrThread : public Atom {
	RTTI_DECL1(ScrThread, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~ScrThread() {}

};

NAMESPACE_PARALLEL_END



#endif

