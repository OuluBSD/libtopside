// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IEffect_BaseClasses_h_
#define _IEffect_BaseClasses_h_

NAMESPACE_PARALLEL_BEGIN

struct FxEffect : public Atom {
	RTTI_DECL1(FxEffect, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~FxEffect() {}

};

NAMESPACE_PARALLEL_END



#endif

