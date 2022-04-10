// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IAudio_BaseClasses_h_
#define _IAudio_BaseClasses_h_

NAMESPACE_PARALLEL_BEGIN

struct AudSinkDevice : public Atom {
	RTTI_DECL1(AudSinkDevice, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~AudSinkDevice() {}

};

struct AudSourceDevice : public Atom {
	RTTI_DECL1(AudSourceDevice, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~AudSourceDevice() {}

};

NAMESPACE_PARALLEL_END



#endif

