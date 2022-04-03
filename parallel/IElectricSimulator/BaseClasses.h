// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.4.3 22:44:00

#ifndef _IElectricSimulator_BaseClasses_h_
#define _IElectricSimulator_BaseClasses_h_

NAMESPACE_PARALLEL_BEGIN

struct EsimSystem : public Atom {
	RTTI_DECL1(EsimSystem, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~EsimSystem() {}

};

NAMESPACE_PARALLEL_END



#endif

