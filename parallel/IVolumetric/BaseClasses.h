// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IVolumetric_BaseClasses_h_
#define _IVolumetric_BaseClasses_h_

NAMESPACE_PARALLEL_BEGIN

struct VolStaticSource : public Atom {
	RTTI_DECL1(VolStaticSource, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~VolStaticSource() {}

};

NAMESPACE_PARALLEL_END



#endif

