// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.3.31 14:22:11

#ifndef _IEvent_BaseClasses_h_
#define _IEvent_BaseClasses_h_

NAMESPACE_PARALLEL_BEGIN

struct EvSourceDevice : public Atom {
	RTTI_DECL1(EvSourceDevice, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~EvSourceDevice() {}

};

NAMESPACE_PARALLEL_END



#endif

