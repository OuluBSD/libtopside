// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _ICamera_BaseClasses_h_
#define _ICamera_BaseClasses_h_

NAMESPACE_PARALLEL_BEGIN

struct CamCamera : public Atom {
	RTTI_DECL1(CamCamera, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~CamCamera() {}

};

NAMESPACE_PARALLEL_END



#endif

