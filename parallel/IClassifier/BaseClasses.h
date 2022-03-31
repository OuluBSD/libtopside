// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.3.31 14:22:11

#ifndef _IClassifier_BaseClasses_h_
#define _IClassifier_BaseClasses_h_

NAMESPACE_PARALLEL_BEGIN

struct ClsSystem : public Atom {
	RTTI_DECL1(ClsSystem, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~ClsSystem() {}

};

NAMESPACE_PARALLEL_END



#endif

