// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.4.8 19:22:44

#ifndef _IThree_BaseClasses_h_
#define _IThree_BaseClasses_h_

NAMESPACE_PARALLEL_BEGIN

struct ThrModel : public Atom {
	RTTI_DECL1(ThrModel, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~ThrModel() {}

};

NAMESPACE_PARALLEL_END



#endif

