// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.4.7 0:44:33

#ifndef _IScreen_BaseClasses_h_
#define _IScreen_BaseClasses_h_

NAMESPACE_PARALLEL_BEGIN

struct ScrSinkDevice : public Atom {
	RTTI_DECL1(ScrSinkDevice, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~ScrSinkDevice() {}

};

NAMESPACE_PARALLEL_END



#endif

