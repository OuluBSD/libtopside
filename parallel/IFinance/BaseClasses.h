// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.4.6 12:22:22

#ifndef _IFinance_BaseClasses_h_
#define _IFinance_BaseClasses_h_

NAMESPACE_PARALLEL_BEGIN

struct FinSystem : public Atom {
	RTTI_DECL1(FinSystem, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~FinSystem() {}

};

NAMESPACE_PARALLEL_END



#endif

