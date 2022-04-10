// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IMath_BaseClasses_h_
#define _IMath_BaseClasses_h_

NAMESPACE_PARALLEL_BEGIN

struct MathSystem : public Atom {
	RTTI_DECL1(MathSystem, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~MathSystem() {}

};

NAMESPACE_PARALLEL_END



#endif

