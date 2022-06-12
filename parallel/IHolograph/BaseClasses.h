// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IHolograph_BaseClasses_h_
#define _IHolograph_BaseClasses_h_

NAMESPACE_PARALLEL_BEGIN

struct HoloSinkDevice : public Atom {
	RTTI_DECL1(HoloSinkDevice, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~HoloSinkDevice() {}

};

NAMESPACE_PARALLEL_END



#endif

