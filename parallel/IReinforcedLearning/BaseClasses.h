// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IReinforcedLearning_BaseClasses_h_
#define _IReinforcedLearning_BaseClasses_h_

NAMESPACE_PARALLEL_BEGIN

struct RlSystem : public Atom {
	RTTI_DECL1(RlSystem, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~RlSystem() {}

};

NAMESPACE_PARALLEL_END



#endif

